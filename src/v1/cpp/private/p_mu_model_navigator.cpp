#include "./p_mu_model_navigator.h"

MUModelNavigatorPvt::MUModelNavigatorPvt(MUModelNavigator *parent) : QObject(parent), link(parent), request(parent), model(parent)
{
    QObject::connect(this, &MUModelNavigatorPvt::requestResponse, this, &MUModelNavigatorPvt::onRequestResponse);
    this->parent=parent;
}

MUModelNavigatorPvt::~MUModelNavigatorPvt()
{
    QObject::disconnect(this, &MUModelNavigatorPvt::requestResponse, this, &MUModelNavigatorPvt::onRequestResponse);
}

bool MUModelNavigatorPvt::loadCache()
{
    this->reloadLink();
    auto url=this->link.url();
    if(!this->cacheAutoLoad)
        return false;

    if(url.isEmpty())
        return false;

    this->cacheFileName=this->variantUtil.toMd5(url);
    if(this->cacheFileName.trimmed().isEmpty())
        return false;

    auto file=this->cacheUtil.cacheDir(this->cacheFileName);
    auto body=this->cacheUtil.loadFile(file).trimmed();

    if(body.isEmpty())
        return false;

    emit this->parent->searchStarted();
    this->model.setJson(body);
    emit this->parent->searchResponse(body);
    emit this->parent->searchFinished();
    return true;
}

void MUModelNavigatorPvt::reloadLink()
{
    if (this->linkCached!=nullptr)
        this->link=*linkCached;
}

bool MUModelNavigatorPvt::saveCache()
{
    auto url=this->link.url();
    if(!this->cacheAutoSave)
        return false;
    if(url.isEmpty())
        return false;

    this->cacheFileName=this->variantUtil.toMd5(url);
    auto file=this->cacheUtil.cacheDir(this->cacheFileName);
    if(this->cacheFileName.trimmed().isEmpty()){
        mWarning()<<"cacheFileName is empty";
        return false;
    }

    if(!this->model.saveFile(file)){
        mWarning()<<"error on save cacheFileName";
        return false;
    }
    return true;
}

bool MUModelNavigatorPvt::clearCursor()
{
    this->reloadLink();
    this->model.clear();
    this->request.cancel();
    this->cachePage=QVariantList();
    this->searchRowCount=-1;
    this->searchOffset=-1;
    this->searchRevision=QVariant();
    return true;
}

bool MUModelNavigatorPvt::clear()
{
    this->searchFilter=QVariant();
    this->clearCursor();
    this->searchPageCount=-1;
    return true;
}

bool MUModelNavigatorPvt::search(const QVariant &searchFilter)
{
    this->clearCursor();
    this->searchFilter=variantUtil.toVar(searchFilter);
    return this->call();
}

bool MUModelNavigatorPvt::reload(const QVariant &v)
{
    auto vSearch=v.isValid()?v:variantUtil.toVar(this->searchFilter);
    return this->search(vSearch);
}

bool MUModelNavigatorPvt::first(const QVariant &v)
{
    Q_UNUSED(v)
    this->clearCursor();
    return this->call();
}

bool MUModelNavigatorPvt::prior(const QVariant &v)
{
    Q_UNUSED(v)
    if(this->request.canStart()){
        return this->call();
    }
    emit parent->searchDiscarted();
    return false;
}

bool MUModelNavigatorPvt::next(const QVariant &v)
{
    Q_UNUSED(v)
    if(this->request.canStart()){
        this->searchRowCount=this->model.count();
        return this->call();
    }
    emit parent->searchDiscarted();
    return false;
}

bool MUModelNavigatorPvt::last(const QVariant &v)
{
    Q_UNUSED(v)
    if(this->request.canStart()){
        return this->call();
    }
    emit parent->searchDiscarted();
    return false;
}

bool MUModelNavigatorPvt::cancel(const QVariant &v)
{
    Q_UNUSED(v)
    if(this->request.canStart()){
        return this->call();
    }
    emit parent->searchDiscarted();
    return false;
}

QVariant MUModelNavigatorPvt::bodyMount()
{
    if(!searchActiveNavigator)
        return this->searchFilter;

    auto vHash=qvh{
        {qsl("version"), this->searchVersion},
        {qsl("page"), this->searchPageCount},
        {qsl("rows"), this->searchRowCount},
        {qsl("filter"), this->searchFilter},
        {qsl("offset"), this->searchOffset}
    };
    if(this->searchRevision.isValid())
        vHash[qsl("revision")]=this->searchRevision;
    return vHash;
}

bool MUModelNavigatorPvt::call()
{
    auto vBody = this->bodyMount();

    auto onOK=[this](const MURequest*r){
#if Q_MU_LOG_VERBOSE
        mWarning()<<"success:"<<r->stateCodeQt()<<","<<r->stateCode();
#endif
        auto v=r->responseBody();
        emit this->requestResponse(v);
    };

    auto onErr=[this](const MURequest*r){
#if Q_MU_LOG_SUPER_VERBOSE
        mWarning()<<qsl("error:")<<r->stateCodeQt()<<","<<r->stateCode()<<","<<r->statePhrase();
#elif Q_MU_LOG_VERBOSE
        mWarning()<<qsl("error:")<<r->stateCodeQt()<<","<<r->stateCode()<<","<<r->statePhrase();
#endif
        QString msg;
        if(r->isUnAuthorized()){
            msg=r->statePhrase().toString().trimmed();
            if(msg.isEmpty())
                msg=tr("Não autorizado");
                      notification.notifyPayload(MUNotificationType::nt_Security, MUNotificationEspecificationSecurity::nse_SessionUnauthorized, msg);
        }
        else if(r->isNetworkFail()){
            msg=r->statePhrase().toString().trimmed();
            msg=msg.isEmpty()?tr("Problemas com a internet"):msg;
            notification.notifyPayload(MUNotificationType::nt_Network, MUNotificationEspecificationNetwork::nsn_Error, msg);
        }
        else{
            msg=r->statePhrase().toString();
            msg=msg.isEmpty()?tr("Problemas com o servidor"):msg;
            notification.notifyPayload(MUNotificationType::nt_Network, MUNotificationEspecificationNetwork::nsn_Fail, msg);
        }
        if(r->isUnAuthorized())
            emit this->parent->searchUnauthorized(msg);
        else if(r->isNetworkError())
            emit this->parent->searchError(msg);
        else
            emit this->parent->searchFail(msg);

    };

    emit this->parent->searchStarted();

    this->reloadLink();
    this->request.setHeader(this->link.headers());
    this->request.setMethod(this->link.method());
    this->request.setBody(vBody);
    return this->request.start( this->link.url(), onOK, onErr);
}

void MUModelNavigatorPvt::onRequestResponse(QVariant v)
{
    auto endMethod=[this,&v](){
        this->saveCache();
        this->searchRevision = this->model.rowRevisionLast();
        emit this->parent->searchResponse(v);
        emit this->parent->searchFinished();
    };

    if(!searchActiveNavigator){
        this->model.clear();
        this->model.setJson(v);
        endMethod();
        return;
    }

    QVariant info;
    switch (this->searchVersion) {
    case 2:
    {
        auto localHash = v.toHash();
        this->searchOffset = localHash.value(qsl("offset")).toInt();
        this->searchPageCount = localHash.value(qsl("page")).toInt();
        info = localHash.value(qsl("result")).toList();
        break;
    }
    case 1:
        info = v;
        break;
    default:
        break;
    }
    this->model.append(info);
    endMethod();
    return;

}

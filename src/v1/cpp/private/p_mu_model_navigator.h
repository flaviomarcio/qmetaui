#pragma once

#include "../mu_const.h"
#include "../mu_login_session.h"
#include "../mu_model_navigator.h"
#include "../mu_register.h"
#include "../mu_request.h"
#include "../mu_model_table.h"
#include "../mu_model_navigator.h"
#include "../mu_notification.h"
#include "../mu_cache_util.h"

class Q_MU_EXPORT MUModelNavigatorPvt : public QObject
{
    Q_OBJECT
public:
    const int searchVersion=2;
    MUModelNavigator*parent=nullptr;
    MUVariantUtil&variantUtil=MUVariantUtil::i();
    MUCacheUtil&cacheUtil=MUCacheUtil::i();
    MUNotification&notification=MUNotification::i();
    MUServerLink *linkCached = nullptr;
    MUServerLink link;
    MURequest request;
    MUModelTable model;
    QString cacheFileName;
    QVariantList cachePage;
    QVariant searchFilter;
    QVariant searchRevision;
    bool searchActiveNavigator=false;
    int searchRowCount =-1;
    int searchPageCount =-1;
    int searchOffset =-1;
    bool cacheAutoLoad=false;
    bool cacheAutoSave=false;

    explicit MUModelNavigatorPvt(MUModelNavigator *parent = nullptr) : QObject{parent}, link(parent), request(parent), model(parent)
    {
        QObject::connect(this, &MUModelNavigatorPvt::requestResponse, this, &MUModelNavigatorPvt::onRequestResponse);
        this->parent=parent;
    }

    ~MUModelNavigatorPvt()
    {
        QObject::disconnect(this, &MUModelNavigatorPvt::requestResponse, this, &MUModelNavigatorPvt::onRequestResponse);
    }

    bool loadCache()
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

        this->parent->searchStarted();
        this->model.setJson(body);
        emit this->parent->searchResponse(body);
        emit this->parent->searchFinished();
        return true;
    }

    void reloadLink()
    {
        if (this->linkCached!=nullptr)
            this->link=*linkCached;
    }

    bool saveCache()
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

    bool clearCursor()
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

    bool clear()
    {
        this->searchFilter=QVariant();
        this->clearCursor();
        this->searchPageCount=-1;
        return true;
    }

    bool search(const QVariant&searchFilter)
    {
        this->clearCursor();
        this->searchFilter=variantUtil.toVar(searchFilter);
        return this->call();
    }

    bool reload(const QVariant&v=QVariant())
    {
        auto vSearch=v.isValid()?v:variantUtil.toVar(this->searchFilter);
        return this->search(vSearch);
    }

    bool first(const QVariant &v=QVariant())
    {
        Q_UNUSED(v)
        this->clearCursor();
        return this->call();
    }

    bool prior(const QVariant &v=QVariant())
    {
        Q_UNUSED(v)
        if(this->request.canStart()){
            return this->call();
        }
        emit parent->searchDiscarted();
        return false;
    }

    bool next(const QVariant &v=QVariant())
    {
        Q_UNUSED(v)
        if(this->request.canStart()){
            this->searchRowCount=this->model.count();
            return this->call();
        }
        emit parent->searchDiscarted();
        return false;
    }

    bool last(const QVariant &v=QVariant())
    {
        Q_UNUSED(v)
        if(this->request.canStart()){
            return this->call();
        }
        emit parent->searchDiscarted();
        return false;
    }

    bool cancel(const QVariant &v=QVariant())
    {
        Q_UNUSED(v)
        if(this->request.canStart()){
            return this->call();
        }
        emit parent->searchDiscarted();
        return false;
    }

    QVariant bodyMount()
    {
        if(!searchActiveNavigator)
            return this->searchFilter;

        QVariantHash vHash;
        vHash[QStringLiteral("version")]=this->searchVersion;
        vHash[QStringLiteral("page")]=this->searchPageCount;
        vHash[QStringLiteral("rows")]=this->searchRowCount;
        vHash[QStringLiteral("filter")]=this->searchFilter;
        vHash[QStringLiteral("offset")]=this->searchOffset;
        if(this->searchRevision.isValid())
            vHash[QStringLiteral("revision")]=this->searchRevision;
        return vHash;
    }

    bool call()
    {
        QVariant vBody = this->bodyMount();
        {
            auto onOK=[this](const MURequest*r){
#if Q_MU_LOG_VERBOSE
                mWarning()<<"success:"<<r->stateCodeQt()<<","<<r->stateCode();
#endif
                auto v=r->responseBody();
                emit this->requestResponse(v);
            };

            auto onErr=[this](const MURequest*r){
#if Q_MU_LOG_SUPER_VERBOSE
                mWarning()<<QStringLiteral("error:")<<r->stateCodeQt()<<","<<r->stateCode()<<","<<r->statePhrase();
#elif Q_MU_LOG_VERBOSE
                mWarning()<<QStringLiteral("error:")<<r->stateCodeQt()<<","<<r->stateCode()<<","<<r->statePhrase();
#endif
                QString msg;
                if(r->isUnAuthorized()){
                    msg=r->statePhrase().toString().trimmed();
                    msg=msg.isEmpty()?tr("Não autorizado"):msg;
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
    }

private slots:
    void onRequestResponse(QVariant v)
    {
        if(!searchActiveNavigator){
            this->model.clear();
            this->model.setJson(v);
        }
        else {
            QVariant info;
            switch (this->searchVersion) {
            case 2:
            {
                QVariantMap localMap = v.toMap();
                this->searchOffset    = localMap.value(QStringLiteral("offset")).toInt();
                this->searchPageCount = localMap.value(QStringLiteral("page")).toInt();
                info = localMap.value(QStringLiteral("result")).toList();
                break;
            }
            case 1:
                info = v;
                break;
            default:
                break;
            }
            this->model.append(info);
        }
        this->saveCache();
        this->searchRevision = this->model.rowRevisionLast();
        emit this->parent->searchResponse(v);
        emit this->parent->searchFinished();
    }
signals:
    void requestResponse(QVariant v);
};

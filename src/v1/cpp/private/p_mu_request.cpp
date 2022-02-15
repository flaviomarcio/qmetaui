#include "./p_mu_request.h"

MURequestPvt::MURequestPvt(MURequest *parent):QObject(parent), link(this)
{
    this->request=parent;
    QObject::connect(this, &MURequestPvt::requestResponse, this, &MURequestPvt::onRequestResponse);
    QObject::connect(this, &MURequestPvt::requestQueue, &MURequestQueue::instance(), &MURequestQueue::requestQueue   );
    QObject::connect(this, &MURequestPvt::requestImediate, &MURequestQueue::instance(), &MURequestQueue::requestImediate);
}

MURequestPvt::~MURequestPvt()
{
    QObject::disconnect(this, &MURequestPvt::requestResponse, this, &MURequestPvt::onRequestResponse);
    QObject::disconnect(this, &MURequestPvt::requestQueue, &MURequestQueue::instance(), &MURequestQueue::requestQueue   );
    QObject::disconnect(this, &MURequestPvt::requestImediate, &MURequestQueue::instance(), &MURequestQueue::requestImediate);
}

QVariantHash MURequestPvt::toMap()
{
    QVariantHash hash;
    for(auto&v:this->header){
        auto m=v.toHash();
        auto key=m.value(qsl("key")).toString();
        auto value=m.value(qsl("value"));
        if(!key.trimmed().isEmpty())
            hash.insert(key, value);
    }
    return hash;
}

bool MURequestPvt::start(const QUrl &url, MURequestCallback response, MURequestCallback fail)
{
    this->callbackResponse=response;
    this->callbackFail=fail;
    this->uuid=QUuid::createUuid();
    this->url=(url.isValid())?url:this->url;
    if(this->modeSynchronous==MUEnumRequest::Mode::mdSync)
        emit requestImediate(this->request);
    else
        emit requestQueue(this->request);
    emit this->request->requestStart();
    return true;
}

void MURequestPvt::finish()
{
    this->uuid=QUuid();
}

void MURequestPvt::cancel()
{
    this->finish();
}

void MURequestPvt::onRequestResponse(const QVariantMap &vResponse)
{
    MURequestResponse response(vResponse);
    this->uuid=QUuid();
    this->response = response;
    if(this->response.isOk()){
        callbackResponse(this->request);
        emit this->request->requestSuccess();
        emit this->request->requestResponse(vResponse);
        emit this->request->requestFinished();
        return;
    }

    auto putMsg=[this](MURequest*r){
        QString msg;

        auto doEmit=[r, &msg](){
            if(r->isUnAuthorized())
                emit r->requestUnauthorized(msg);
            else if(r->isNetworkError())
                emit r->requestError(msg);
            else
                emit r->requestFail(tr("Erro interno no servidor"));
        };

        if(r->isUnAuthorized()){
            msg=r->statePhrase().toString().trimmed();
            msg=msg.isEmpty()?tr("Não autorizado"):msg;
            notification.notifyPayload(MUNotificationType::nt_Security, MUNotificationEspecificationSecurity::nse_SessionUnauthorized,msg);
            doEmit();
            return;
        }

        if(r->isNetworkFail()){
            msg=r->statePhrase().toString().trimmed();
            msg=msg.isEmpty()?tr("Problemas com a internet"):msg;
            notification.notifyPayload(MUNotificationType::nt_Network, MUNotificationEspecificationNetwork::nsn_Error,msg);
            doEmit();
            return;
        }

        msg=r->statePhrase().toString();
        msg=msg.isEmpty()?tr("Problemas com o servidor"):msg;
        notification.notifyPayload(MUNotificationType::nt_Network, MUNotificationEspecificationNetwork::nsn_Fail,msg);
        doEmit();
        return;
    };

    putMsg(this->request);
    callbackFail(this->request);
    emit this->request->requestResponse(vResponse);
    emit this->request->requestFinished();
}

#include "p_mu_request.h"

MURequestPvt::MURequestPvt(MURequest *parent):QObject{parent}, link(this)
{
    this->request=parent;
    connect(this, &MURequestPvt::requestResponse, this, &MURequestPvt::onRequestResponse);
    connect(this, &MURequestPvt::requestQueue   , &MURequestQueue::instance(), &MURequestQueue::requestQueue   );
    connect(this, &MURequestPvt::requestImediate, &MURequestQueue::instance(), &MURequestQueue::requestImediate);
}

MURequestPvt::~MURequestPvt(){
    disconnect(this, &MURequestPvt::requestResponse, this, &MURequestPvt::onRequestResponse);
    disconnect(this, &MURequestPvt::requestQueue   , &MURequestQueue::instance(), &MURequestQueue::requestQueue   );
    disconnect(this, &MURequestPvt::requestImediate, &MURequestQueue::instance(), &MURequestQueue::requestImediate);
}

QVariantMap MURequestPvt::toMap()
{
    QVariantMap map;
    for(auto&v:this->header){
        auto m=v.toHash();
        auto key=m.value(QStringLiteral("key")).toString();
        auto value=m.value(QStringLiteral("value"));
        if(!key.trimmed().isEmpty())
            map.insert(key, value);
    }
    return map;
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

void MURequestPvt::onRequestResponse(const QVariantHash &vResponse)
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
        if(r->isUnAuthorized()){
            msg=r->statePhrase().toString().trimmed();
            msg=msg.isEmpty()?tr("Não autorizado"):msg;
            notification.notifyPayload(MUNotificationType::nt_Security, MUNotificationEspecificationSecurity::nse_SessionUnauthorized,msg);
        }
        else if(r->isNetworkFail()){
            msg=r->statePhrase().toString().trimmed();
            msg=msg.isEmpty()?tr("Problemas com a internet"):msg;
            notification.notifyPayload(MUNotificationType::nt_Network, MUNotificationEspecificationNetwork::nsn_Error,msg);
        }
        else{
            msg=r->statePhrase().toString();
            msg=msg.isEmpty()?tr("Problemas com o servidor"):msg;
            notification.notifyPayload(MUNotificationType::nt_Network, MUNotificationEspecificationNetwork::nsn_Fail,msg);
        }
        if(r->isUnAuthorized())
            emit r->requestUnauthorized(msg);
        else if(r->isNetworkError())
            emit r->requestError(msg);
        else
            emit r->requestFail(tr("Erro interno no servidor"));

    };
    putMsg(this->request);
    callbackFail(this->request);
    emit this->request->requestResponse(vResponse);
    emit this->request->requestFinished();
}

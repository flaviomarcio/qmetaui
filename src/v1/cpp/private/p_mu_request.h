#pragma once

#include "./p_mu_request_response.h"
#include "./p_mu_request_queue.h"
#include "../mu_notification.h"
#include <QUuid>

//static QByteArray baseUuid=QUuid::createUuid().toString().toUtf8();
//static int baseUuidInc=0;

class Q_MU_EXPORT MURequestPvt:public QObject{
    Q_OBJECT
public:
    MUServerLink link;
    MUNotification&notification=MUNotification::i();
    MURequestCallback callbackResponse;
    MURequestCallback callbackFail;
    MUStringUtil&stringUtil=MUStringUtil::i();
    MUVariantUtil&variantUtil=MUVariantUtil::i();
    MURequestResponse response;
    QUrl url;
    MUEnumRequest::Method method=MUEnumRequest::Method::rmPost;
    MUEnumRequest::Mode modeSynchronous=MUEnumRequest::Mode::mdASync;
    MUEnumRequest::AppType requestAppType=MUEnumRequest::AppType::atJson;
    QUuid uuid;
    QVariantMap header;
    QVariant body;
    MURequest*request=nullptr;
    Q_INVOKABLE explicit MURequestPvt(MURequest*parent):QObject{parent}, link(this)
    {
        this->request=parent;
        connect(this, &MURequestPvt::requestResponse, this, &MURequestPvt::onRequestResponse);
        connect(this, &MURequestPvt::requestQueue   , &MURequestQueue::instance(), &MURequestQueue::requestQueue   );
        connect(this, &MURequestPvt::requestImediate, &MURequestQueue::instance(), &MURequestQueue::requestImediate);
    }

    ~MURequestPvt(){
        disconnect(this, &MURequestPvt::requestResponse, this, &MURequestPvt::onRequestResponse);
        disconnect(this, &MURequestPvt::requestQueue   , &MURequestQueue::instance(), &MURequestQueue::requestQueue   );
        disconnect(this, &MURequestPvt::requestImediate, &MURequestQueue::instance(), &MURequestQueue::requestImediate);
    }

    QVariantMap toMap()
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

    bool start(const QUrl&url, MURequestCallback response, MURequestCallback fail)
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

    void finish()
    {
        this->uuid=QUuid();
    }

    void cancel()
    {
        this->finish();
    }
public slots:
    void onRequestResponse(const QVariantMap&vResponse)
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
signals:
    void requestQueue(MURequest*request);
    void requestImediate(MURequest*request);
    void requestResponse(const QVariantMap&vResponse);

};

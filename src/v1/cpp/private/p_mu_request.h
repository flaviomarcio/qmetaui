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
    QVariantHash header;
    QVariant body;
    MURequest*request=nullptr;

    Q_INVOKABLE explicit MURequestPvt(MURequest*parent);

    ~MURequestPvt();

    QVariantMap toMap();

    bool start(const QUrl&url, MURequestCallback response, MURequestCallback fail);

    void finish();

    void cancel();
public slots:
    void onRequestResponse(const QVariantHash &vResponse);
signals:
    void requestQueue(MURequest*request);
    void requestImediate(MURequest*request);
    void requestResponse(const QVariantHash&vResponse);

};

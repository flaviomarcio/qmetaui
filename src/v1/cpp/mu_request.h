#pragma once

#include "./mu_global.h"
#include <QNetworkReply>
#include "./mu_register.h"
#include "./mu_variant_util.h"
#include "./mu_string_util.h"
#include "./mu_server_link.h"

class Q_MU_EXPORT MURequest;
typedef std::function<void(const MURequest*request)> MURequestCallback;
class Q_MU_EXPORT MURequest : public QObject
{
    Q_OBJECT
    friend class Q_MU_EXPORT MURequestQueuePvt;
public:

    Q_PROPERTY(MUServerLink*link READ link WRITE setLink NOTIFY linkChanged)

    Q_INVOKABLE explicit MURequest(QObject *parent = nullptr);
    ~MURequest();

    virtual MUServerLink *link();
    virtual void setLink(const MUServerLink *link);

    Q_INVOKABLE virtual void clear();
    Q_INVOKABLE virtual bool start();
    Q_INVOKABLE virtual bool start(const QUrl &url, MURequestCallback response, MURequestCallback fail);
    Q_INVOKABLE virtual bool canStart();
    Q_INVOKABLE virtual void finish();
    Q_INVOKABLE virtual void cancel();
    Q_INVOKABLE virtual bool isRunning();

    Q_INVOKABLE virtual QVariantHash header() const;
    Q_INVOKABLE virtual bool setHeader(const QString &key, const QVariant&value) const;
    Q_INVOKABLE virtual void setHeader(const QVariant &header);
    Q_INVOKABLE virtual bool setAuthoBearer(const QString &credentials) const;

    Q_INVOKABLE virtual QVariant uuid() const;
    Q_INVOKABLE virtual QByteArray body() const;
    Q_INVOKABLE virtual QVariantHash bodyMap() const;
    Q_INVOKABLE virtual QVariantHash bodyHash() const;

    Q_INVOKABLE virtual void setBody(const QVariant &body);
    Q_INVOKABLE virtual QVariant stateCode() const;
    Q_INVOKABLE virtual QNetworkReply::NetworkError stateCodeQt() const;
    Q_INVOKABLE virtual QVariant statePhrase() const;
    Q_INVOKABLE virtual QVariant responseBody() const;
    Q_INVOKABLE virtual QVariantHash responseBodyMap() const;
    Q_INVOKABLE virtual QVariantList responseBodyList() const;
    Q_INVOKABLE virtual QString responseBodyString() const;
    Q_INVOKABLE virtual bool isOk() const;
    Q_INVOKABLE virtual bool isUnAuthorized() const;
    Q_INVOKABLE virtual bool isNetworkFail() const;
    Q_INVOKABLE virtual bool isNetworkError() const;

    Q_INVOKABLE virtual MUEnumRequest::Mode modeSynchronous() const;
    Q_INVOKABLE virtual void setModeSynchronous(const MUEnumRequest::Mode &mode);

    Q_INVOKABLE virtual QUrl url() const;
    Q_INVOKABLE virtual void setUrl(const QString &url);

    Q_INVOKABLE virtual MUEnumRequest::Method method() const;
    Q_INVOKABLE virtual MURequest &setMethod(const QVariant &value);
    Q_INVOKABLE virtual MURequest &setMethodHead();
    Q_INVOKABLE virtual MURequest &setMethodGET();
    Q_INVOKABLE virtual MURequest &setMethodPOST();
    Q_INVOKABLE virtual MURequest &setMethodPUT();
    Q_INVOKABLE virtual MURequest &setMethodDELETE();

    Q_INVOKABLE virtual MUEnumRequest::AppType requestAppType() const;
    Q_INVOKABLE virtual MURequest &setRequestAppType(const MUEnumRequest::AppType &value);

    Q_INVOKABLE virtual MUStringUtil&u();
    Q_INVOKABLE virtual MUVariantUtil&v();

private:
    void*p=nullptr;
signals:
    void requestStart();
    void requestSuccess();
    void requestFinished();
    void requestUnauthorized(const QVariant&message);
    void requestError(const QVariant&message);
    void requestFail(const QVariant&message);
    void requestResponse(const QVariantMap&response);
    void linkChanged();
};

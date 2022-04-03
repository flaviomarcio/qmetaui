#pragma once

#include "./mu_global.h"
#include <QNetworkReply>
#include "./mu_register.h"
#include "./mu_variant_util.h"
#include "./mu_string_util.h"
#include "./mu_server_link.h"

class Q_MU_EXPORT MURequest;
typedef std::function<void(const MURequest*request)> MURequestCallback;

//!
//! \brief The MURequest class
//!
class Q_MU_EXPORT MURequest : public QObject
{
    Q_OBJECT
    friend class Q_MU_EXPORT MURequestQueuePvt;
public:

    Q_PROPERTY(MUServerLink*link READ link WRITE setLink NOTIFY linkChanged)

    //!
    //! \brief MURequest
    //! \param parent
    //!
    Q_INVOKABLE explicit MURequest(QObject *parent = nullptr);
    ~MURequest();

    //!
    //! \brief link
    //! \return
    //!
    virtual MUServerLink *link();
    virtual void setLink(const MUServerLink *link);

    //!
    //! \brief clear
    //!
    Q_INVOKABLE virtual void clear();

    //!
    //! \brief start
    //! \return
    //!
    Q_INVOKABLE virtual bool start();

    //!
    //! \brief start
    //! \param url
    //! \param response
    //! \param fail
    //! \return
    //!
    Q_INVOKABLE virtual bool start(const QUrl &url, MURequestCallback response, MURequestCallback fail);

    //!
    //! \brief canStart
    //! \return
    //!
    Q_INVOKABLE virtual bool canStart();

    //!
    //! \brief finish
    //!
    Q_INVOKABLE virtual void finish();

    //!
    //! \brief cancel
    //!
    Q_INVOKABLE virtual void cancel();

    //!
    //! \brief isRunning
    //! \return
    //!
    Q_INVOKABLE virtual bool isRunning();

    //!
    //! \brief header
    //! \return
    //!
    Q_INVOKABLE virtual QVariantHash header() const;

    //!
    //! \brief setHeader
    //! \param key
    //! \param value
    //! \return
    //!
    Q_INVOKABLE virtual bool setHeader(const QString &key, const QVariant&value) const;

    //!
    //! \brief setHeader
    //! \param header
    //!
    Q_INVOKABLE virtual void setHeader(const QVariant &header);

    //!
    //! \brief setAuthoBearer
    //! \param credentials
    //! \return
    //!
    Q_INVOKABLE virtual bool setAuthoBearer(const QString &credentials) const;

    //!
    //! \brief uuid
    //! \return
    //!
    Q_INVOKABLE virtual QVariant uuid() const;

    //!
    //! \brief body
    //! \return
    //!
    Q_INVOKABLE virtual QByteArray body() const;

    //!
    //! \brief bodyMap
    //! \return
    //!
    Q_INVOKABLE virtual QVariantHash bodyMap() const;

    //!
    //! \brief bodyHash
    //! \return
    //!
    Q_INVOKABLE virtual QVariantHash bodyHash() const;

    //!
    //! \brief bodyList
    //! \return
    //!
    Q_INVOKABLE virtual QVariantList bodyList() const;

    //!
    //! \brief setBody
    //! \param body
    //!
    Q_INVOKABLE virtual void setBody(const QVariant &body);

    //!
    //! \brief stateCode
    //! \return
    //!
    Q_INVOKABLE virtual QVariant stateCode() const;

    //!
    //! \brief stateCodeQt
    //! \return
    //!
    Q_INVOKABLE virtual QNetworkReply::NetworkError stateCodeQt() const;

    //!
    //! \brief statePhrase
    //! \return
    //!
    Q_INVOKABLE virtual QVariant statePhrase() const;

    //!
    //! \brief responseBody
    //! \return
    //!
    Q_INVOKABLE virtual QVariant responseBody() const;

    //!
    //! \brief responseBodyHash
    //! \return
    //!
    Q_INVOKABLE virtual QVariantHash responseBodyHash() const;

    //!
    //! \brief responseBodyMap
    //! \return
    //!
    Q_INVOKABLE virtual QVariantMap responseBodyMap() const;

    //!
    //! \brief responseBodyList
    //! \return
    //!
    Q_INVOKABLE virtual QVariantList responseBodyList() const;

    //!
    //! \brief responseBodyBytes
    //! \return
    //!
    Q_INVOKABLE virtual QString responseBodyBytes() const;

    //!
    //! \brief isOk
    //! \return
    //!
    Q_INVOKABLE virtual bool isOk() const;

    //!
    //! \brief isUnAuthorized
    //! \return
    //!
    Q_INVOKABLE virtual bool isUnAuthorized() const;

    //!
    //! \brief isNetworkFail
    //! \return
    //!
    Q_INVOKABLE virtual bool isNetworkFail() const;

    //!
    //! \brief isNetworkError
    //! \return
    //!
    Q_INVOKABLE virtual bool isNetworkError() const;

    //!
    //! \brief modeSynchronous
    //! \return
    //!
    Q_INVOKABLE virtual MUEnumRequest::Mode modeSynchronous() const;

    //!
    //! \brief setModeSynchronous
    //! \param mode
    //!
    Q_INVOKABLE virtual void setModeSynchronous(const MUEnumRequest::Mode &mode);

    //!
    //! \brief url
    //! \return
    //!
    Q_INVOKABLE virtual QUrl url() const;

    //!
    //! \brief setUrl
    //! \param url
    //!
    Q_INVOKABLE virtual void setUrl(const QString &url);

    //!
    //! \brief method
    //! \return
    //!
    Q_INVOKABLE virtual MUEnumRequest::Method method() const;

    //!
    //! \brief setMethod
    //! \param value
    //! \return
    //!
    Q_INVOKABLE virtual MURequest &setMethod(const QVariant &value);

    //!
    //! \brief setMethodHEAD
    //! \return
    //!
    Q_INVOKABLE virtual MURequest &setMethodHEAD();

    //!
    //! \brief setMethodGET
    //! \return
    //!
    Q_INVOKABLE virtual MURequest &setMethodGET();

    //!
    //! \brief setMethodPOST
    //! \return
    //!
    Q_INVOKABLE virtual MURequest &setMethodPOST();

    //!
    //! \brief setMethodPUT
    //! \return
    //!
    Q_INVOKABLE virtual MURequest &setMethodPUT();

    //!
    //! \brief setMethodDELETE
    //! \return
    //!
    Q_INVOKABLE virtual MURequest &setMethodDELETE();

    //!
    //! \brief requestAppType
    //! \return
    //!
    Q_INVOKABLE virtual MUEnumRequest::AppType requestAppType() const;

    //!
    //! \brief setRequestAppType
    //! \param value
    //! \return
    //!
    Q_INVOKABLE virtual MURequest &setRequestAppType(const MUEnumRequest::AppType &value);

private:
    void*p=nullptr;
signals:
    void requestStart();
    void requestSuccess();
    void requestFinished();
    void requestUnauthorized(const QVariant&message);
    void requestError(const QVariant&message);
    void requestFail(const QVariant&message);
    void requestResponse(const QVariantHash&response);
    void linkChanged();
};

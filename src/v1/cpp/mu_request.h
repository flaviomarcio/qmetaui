#pragma once

#include "./mu_global.h"
#include <QNetworkReply>
#include "./mu_register.h"
#include "./mu_variant_util.h"
#include "./mu_string_util.h"
#include "./mu_server_link.h"

class Q_MU_EXPORT MURequest;

//!
//! \brief MURequestCallback
//!
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

    //!
    //!
    ~MURequest();

    //!
    //! \brief link
    //! \return
    //!
    virtual MUServerLink *link();

    //!
    //! \brief setLink
    //! \param link
    //!
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
    virtual bool start(const QUrl &url, MURequestCallback response, MURequestCallback fail);
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
    //! \brief uuid
    //! \return
    //!
    Q_INVOKABLE virtual QUuid uuid() const;

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
    Q_INVOKABLE virtual void setHeader(const QVariant &header);

    //!
    //! \brief setAuthBearer
    //! \param credentials
    //! \return
    //!
    Q_INVOKABLE virtual bool setAuthBearer(const QString &credentials) const;



    //!
    //! \brief body
    //! \return
    //!
    Q_INVOKABLE virtual QByteArray body() const;

    //!
    //! \brief bodyMap
    //! \return
    //!
    Q_INVOKABLE virtual QVariantMap bodyMap() const;

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
    //! \brief bodyStringList
    //! \return
    //!
    Q_INVOKABLE virtual QStringList bodyStringList() const;

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
    //! \brief responseBodyMap
    //! \return
    //!
    Q_INVOKABLE virtual QVariantHash responseBodyMap() const;

    //!
    //! \brief responseBodyHash
    //! \return
    //!
    Q_INVOKABLE virtual QVariantHash responseBodyHash() const;

    //!
    //! \brief responseBodyList
    //! \return
    //!
    Q_INVOKABLE virtual QVariantList responseBodyList() const;

    //!
    //! \brief responseBodyStringList
    //! \return
    //!
    Q_INVOKABLE virtual QStringList responseBodyStringList() const;

    //!
    //! \brief responseBodyString
    //! \return
    //!
    Q_INVOKABLE virtual QString responseBodyString() const;

    //!
    //! \brief responseBodyByteArray
    //! \return
    //!
    Q_INVOKABLE virtual QByteArray responseBodyByteArray() const;

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
    Q_INVOKABLE virtual void setUrl(const QString &url);

    //!
    //! \brief method
    //! \return
    //!
    Q_INVOKABLE virtual MUEnumRequest::Method method() const;

    //!
    //! \brief setMethod
    //! \param value
    //!
    Q_INVOKABLE virtual void setMethod(const QVariant &value);

    //!
    //! \brief setMethodHead
    //!
    Q_INVOKABLE virtual void setMethodHead();

    //!
    //! \brief setMethodGET
    //!
    Q_INVOKABLE virtual void setMethodGET();

    //!
    //! \brief setMethodPOST
    //!
    Q_INVOKABLE virtual void setMethodPOST();

    //!
    //! \brief setMethodPUT
    //!
    Q_INVOKABLE virtual void setMethodPUT();

    //!
    //! \brief setMethodDELETE
    //!
    Q_INVOKABLE virtual void setMethodDELETE();

    //!
    //! \brief requestAppType
    //! \return
    //!
    Q_INVOKABLE virtual MUEnumRequest::AppType requestAppType() const;
    Q_INVOKABLE virtual void setRequestAppType(const MUEnumRequest::AppType &value);

    //!
    //! \brief u
    //! \return
    //!
    Q_INVOKABLE virtual MUStringUtil&u();

    //!
    //! \brief v
    //! \return
    //!
    Q_INVOKABLE virtual MUVariantUtil&v();

private:
    void*p=nullptr;
signals:
    //!
    //! \brief requestStart
    //!
    void requestStart();

    //!
    //! \brief requestSuccess
    //!
    void requestSuccess();

    //!
    //! \brief requestFinished
    //!
    void requestFinished();

    //!
    //! \brief requestUnauthorized
    //! \param message
    //!
    void requestUnauthorized(const QVariant&message);

    //!
    //! \brief requestError
    //! \param message
    //!
    void requestError(const QVariant&message);

    //!
    //! \brief requestFail
    //! \param message
    //!
    void requestFail(const QVariant&message);

    //!
    //! \brief requestResponse
    //! \param response
    //!
    void requestResponse(const QVariantMap&response);

    //!
    //! \brief linkChanged
    //!
    void linkChanged();
};

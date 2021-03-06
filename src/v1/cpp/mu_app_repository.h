#pragma once

#include "./mu_global.h"
#include "./mu_object.h"

#include <QVariantMap>

class Q_MU_EXPORT MUAppRepository : public MUObject
{
    Q_OBJECT
public:

    Q_PROPERTY(QVariantMap  headers  READ headers   WRITE setHeaders  NOTIFY headersChanged )
    Q_PROPERTY(QString      hostName READ hostName  WRITE setHostName NOTIFY urlChanged     )
    Q_PROPERTY(QString      method   READ method    WRITE setMethod   NOTIFY urlChanged     )
    Q_PROPERTY(QVariant     protocol READ protocol  WRITE setProtocol NOTIFY urlChanged     )
    Q_PROPERTY(int          port     READ port      WRITE setPort     NOTIFY urlChanged     )
    Q_PROPERTY(QString      route    READ route     WRITE setRoute    NOTIFY urlChanged     )
    Q_PROPERTY(QString      url      READ url                         NOTIFY urlChanged     )

    /**
     * @brief MUAppRepository
     * @param parent
     */
    Q_INVOKABLE explicit MUAppRepository(QObject *parent = nullptr);
    ~MUAppRepository();

    MUAppRepository&operator=(const MUAppRepository&v);
    MUAppRepository&operator=(const QVariant&v);

    /**
     * @brief isValid
     * @return
     */
    Q_INVOKABLE virtual bool isValid();

    /**
     * @brief headers
     * @return
     */
    Q_INVOKABLE virtual QVariantMap headers() const;
    Q_INVOKABLE virtual void setHeaders(const QVariantMap &v);


    /**
     * @brief hostName
     * @return
     */
    Q_INVOKABLE virtual QString hostName() const;
    Q_INVOKABLE virtual void setHostName(const QString &hostName);

    /**
     * @brief method
     * @return
     */
    Q_INVOKABLE virtual QString method() const;
    Q_INVOKABLE virtual void setMethod(const QString &method);

    /**
     * @brief protocol
     * @return
     */
    Q_INVOKABLE virtual QVariant protocol() const;
    Q_INVOKABLE virtual void setProtocol(const QVariant &protocol);

    /**
     * @brief port
     * @return
     */
    Q_INVOKABLE virtual int port() const;
    Q_INVOKABLE virtual void setPort(int port);

    /**
     * @brief route
     * @return
     */
    Q_INVOKABLE virtual QString route() const;
    Q_INVOKABLE virtual void setRoute(const QString &route);

    /**
     * @brief url
     * @return
     */
    Q_INVOKABLE virtual QString url() const;

    /**
     * @brief parserUrl
     * @param v
     * @return
     */
    Q_INVOKABLE virtual QVariant parserUrl(const QVariant&v) const;

private:
    void*p=nullptr;

signals:
    void headersChanged();
    void urlChanged();
};

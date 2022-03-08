#pragma once

#include "./mu_global.h"
#include <QObject>
#include "./mu_login_session.h"

class Q_MU_EXPORT MURoutes:public QObject{
    Q_OBJECT
public:

    Q_PROPERTY(QVariantHash headers     READ headers    WRITE setHeaders    )
    Q_PROPERTY(QString      server      READ server     WRITE setServer     )
    Q_PROPERTY(QString      protocol    READ protocol   WRITE setProtocol   )
    Q_PROPERTY(QString      hostName    READ hostName   WRITE setHostName   )
    Q_PROPERTY(int          port        READ port       WRITE setPort       )
    Q_PROPERTY(QVariantMap  route       READ route      WRITE setRoute      )

    Q_INVOKABLE explicit MURoutes(QObject *parent = nullptr);
    ~MURoutes();

    /**
     * @brief fileNameLoaded
     * @return
     */
    virtual QString fileNameLoaded();

    /**
     * @brief load
     */
    Q_INVOKABLE virtual void load();
    Q_INVOKABLE virtual void load(const QString &fileName);

    /**
     * @brief settingsMap
     * @return
     */
    Q_INVOKABLE virtual QVariantHash&settingsMap();

    /**
     * @brief clear
     */
    Q_INVOKABLE virtual void clear();

    /**
     * @brief server
     * @return
     */
    Q_INVOKABLE virtual QString server() const;
    Q_INVOKABLE virtual void setServer(const QString &value);


    /**
     * @brief headers
     * @return
     */
    Q_INVOKABLE virtual QVariantHash headers() const;
    Q_INVOKABLE virtual void setHeaders(const QVariantHash &value);

    /**
     * @brief protocol
     * @return
     */
    Q_INVOKABLE virtual QString protocol() const;
    Q_INVOKABLE virtual void setProtocol(const QString &value);

    /**
     * @brief hostName
     * @return
     */
    Q_INVOKABLE virtual QString hostName() const;
    Q_INVOKABLE virtual void setHostName(const QString &value);

    /**
     * @brief port
     * @return
     */
    Q_INVOKABLE virtual int port() const;
    Q_INVOKABLE virtual void setPort(const QVariant &value);

    /**
     * @brief route
     * @return
     */
    Q_INVOKABLE virtual QVariantMap route() const;
    Q_INVOKABLE virtual void setRoute(const QVariantMap &value);
private:
    void*p=nullptr;
};

#ifndef MUServerLink_H
#define MUServerLink_H

#include "./mu_global.h"
#include <QObject>
#include <QVariantMap>
#include <QUrl>

class Q_MU_EXPORT MUServerLink : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(QString      url         READ url                            )
    Q_PROPERTY(QString      hash        READ hash                           )
    Q_PROPERTY(QVariantHash headers     READ headers    WRITE setHeaders    )
    Q_PROPERTY(QString      protocol    READ protocol   WRITE setProtocol   )
    Q_PROPERTY(QString      host        READ host       WRITE setHost       )
    Q_PROPERTY(int          port        READ port       WRITE setPort       )
    Q_PROPERTY(QString      route       READ route      WRITE setRoute      )
    Q_PROPERTY(QString      endpoint    READ endpoint   WRITE setEndpoint   )
    Q_PROPERTY(QString      method      READ method     WRITE setMethod     )
public:

    Q_INVOKABLE explicit MUServerLink(QObject *parent = nullptr);
    ///Q_INVOKABLE explicit MUServerLink(MUServerLink&link, QObject *parent = nullptr);
    ~MUServerLink();

    Q_INVOKABLE virtual QVariant toMap()const;

    virtual QString url() const;

    Q_INVOKABLE virtual bool read(const QVariant&link);

    virtual QVariantHash &headers();
    virtual void setHeaders(const QVariantHash &value);

    virtual QString hash();

    virtual QString protocol() const;
    virtual void setProtocol(const QString &value);

    virtual QString host() const;
    virtual void setHost(const QString &value);

    virtual int port() const;
    virtual void setPort(const QVariant &value);

    virtual QString route() const;
    virtual void setRoute(const QString &value);

    virtual QString endpoint() const;
    virtual void setEndpoint(const QString &value);

    virtual QString method() const;
    virtual void setMethod(const QString &method);

    virtual MUServerLink&setValues(const QVariant&protocol, const QVariant&host, const QVariant &port, const QVariant&route, const QVariant&method);
    virtual MUServerLink&setValues(MUServerLink*value);

    MUServerLink&operator=(const MUServerLink&link);

signals:
    void changedHeaders();

public slots:
    virtual void changeHeaders(const QVariantHash &value);

private:
    void*p=nullptr;
};

#endif // MUServerLink_H

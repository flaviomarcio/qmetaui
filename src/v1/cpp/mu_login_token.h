#pragma once

#include "./mu_global.h"
#include "./mu_object.h"
#include <QVariant>
#include <QDate>
#include <QVariantList>
#include <QVariantMap>

class Q_MU_EXPORT MULoginToken : public MUObject{
    Q_OBJECT
public:
    Q_PROPERTY(QDateTime    iat     READ iat     WRITE setIat      NOTIFY tokenChanged )
    Q_PROPERTY(QDateTime    exp     READ exp     WRITE setExp      NOTIFY tokenChanged )
    Q_PROPERTY(QString      md5     READ md5     WRITE setMd5      NOTIFY tokenChanged )
    Q_PROPERTY(QByteArray   payload READ payload WRITE setPayload  NOTIFY tokenChanged )
    Q_PROPERTY(QByteArray   token   READ token   WRITE setToken    NOTIFY tokenChanged )

    Q_INVOKABLE explicit MULoginToken(QObject *parent = nullptr);
    ~MULoginToken();

    QDateTime exp() const;
    void setExp(const QDateTime &value);

    QDateTime iat() const;
    void setIat(const QDateTime &value);

    QString md5() const;
    void setMd5(const QString &value);

    QByteArray payload() const;
    void setPayload(const QByteArray &value);

    QByteArray token() const;
    void setToken(const QByteArray &value);

    Q_INVOKABLE bool isRecent();

    MULoginToken&operator=(const QVariantHash&v);

    void clear();

private:
    void*p=nullptr;
signals:
    void tokenChanged();
};

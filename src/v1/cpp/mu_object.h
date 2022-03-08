#pragma once
#include "./mu_global.h"
#include <QObject>
#include <QVariant>
#include <QVariantList>
#include <QVariantMap>

class Q_MU_EXPORT MUObject : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit MUObject(QObject *parent = nullptr);

    Q_INVOKABLE QVariantHash toHash()const;
    Q_INVOKABLE QByteArray toJson()const;
    Q_INVOKABLE bool fromMap(const QVariantMap &v);
    Q_INVOKABLE bool fromHash(const QVariantHash &v);
};

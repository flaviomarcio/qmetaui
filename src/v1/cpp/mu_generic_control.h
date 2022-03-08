#pragma once

#include "./mu_global.h"

#include <QObject>
#include <QVariant>
#include <QMutex>


class Q_MU_EXPORT MUGenericControl : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit MUGenericControl(QObject *parent = nullptr);
    ~MUGenericControl();

    Q_INVOKABLE bool contains(const QVariant &key);
    Q_INVOKABLE bool remove(const QVariant &key);
    Q_INVOKABLE bool add(const QVariant &key, const QVariant &value);
    Q_INVOKABLE bool replace(const QVariant &key, const QVariant &value);

    Q_INVOKABLE QVariant take(const QVariant &key);
    Q_INVOKABLE QVariantMap takeFist();

    Q_INVOKABLE QVariantList values();

    Q_INVOKABLE bool isEmpty();

    Q_INVOKABLE void addOrReplace(const QVariant &key, const QVariant &value);
signals:
    void dataChanged();
private:
    mutable QMutex mutex;
    QHash<QVariant, QVariant> p;
};

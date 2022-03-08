#pragma once

#include "./mu_global.h"
#include <QObject>
#include <QVariant>
#include <QDateTime>
#include <QVariantMap>
#include <QVariantList>
#include <QDateTime>
#include <QJsonDocument>
#include <QJsonObject>
#include <QCborValue>
#include <QCborMap>
#include <QCborArray>
#include <QColor>
#include <QObject>
#include <QQuickItem>
#include <QCborParserError>


class Q_MU_EXPORT MUVariantUtil : public QObject
{
    Q_OBJECT
public:

    Q_INVOKABLE explicit MUVariantUtil(QObject *parent = nullptr);
    ~MUVariantUtil();

    static Q_INVOKABLE MUVariantUtil&i();

    Q_INVOKABLE static bool isDebug();

    Q_INVOKABLE static const QVariant ifThen(const QVariant &vThen, const QVariant &vElse);
    Q_INVOKABLE static bool isDefined(const QVariant &v);
    Q_INVOKABLE static bool isUndefined(const QVariant &v);

    Q_INVOKABLE static const QVariantMap toMap(const QVariant&v);
    Q_INVOKABLE static const QByteArray toMd5(const QVariant &v);
    Q_INVOKABLE static const QString toStr(const QVariant &v, const QVariant &defaultValue=QString());
    Q_INVOKABLE static const QString toBytes(const QVariant &v, const QVariant &defaultValue=QString());
    Q_INVOKABLE static const QString toStrNumber(const QVariant &v);
    Q_INVOKABLE static const QString toStrDouble(const QVariant &v);
    Q_INVOKABLE static const QVariant toVar(const QVariant &v);
    Q_INVOKABLE static bool toBoo(const QVariant &v);
    Q_INVOKABLE static const QByteArray toJson(const QVariant &v);
    Q_INVOKABLE static const QVariant toJsonVariant(const QVariant &v);
    Q_INVOKABLE static const QByteArray toCBor(const QVariant &v);
    Q_INVOKABLE static const QColor toColor(const QVariant &v, const QColor &defaultValue=Qt::transparent);
    Q_INVOKABLE static qlonglong toInt(const QVariant &v, QVariant defaultValue=0);
    Q_INVOKABLE static double toDouble(const QVariant &v, QVariant defaultValue=0);
    Q_INVOKABLE static const QVariant convertVar(const QVariant &v, const QVariant::Type&type);
    Q_INVOKABLE static const QVariant toAlignment(const QVariant&v, Qt::Alignment alignment=Qt::AlignCenter);
    Q_INVOKABLE static int toVariantType(const QVariant&v);
    Q_INVOKABLE static const QByteArray toVariantTypeName(int v);

    Q_INVOKABLE static bool isEqual(const QVariant&v1, const QVariant&v2);
    Q_INVOKABLE static bool isDiff(const QVariant&v1, const QVariant&v2);

signals:

};

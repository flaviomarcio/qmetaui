#ifndef MUObjectUtil_H
#define MUObjectUtil_H

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

class Q_MU_EXPORT MUObjectUtil : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit MUObjectUtil(QObject *parent = nullptr);

    ~MUObjectUtil();

    static Q_INVOKABLE MUObjectUtil&i();

    Q_INVOKABLE static bool isDebug();
    Q_INVOKABLE static bool isIOS();
    Q_INVOKABLE static bool isAndroid();
    Q_INVOKABLE static bool isDesktop();

    Q_INVOKABLE static const QVariant ifThen(const QVariant &vThen, const QVariant &vElse);
    Q_INVOKABLE static bool isDefined(const QVariant &v);
    Q_INVOKABLE static bool isUndefined(const QVariant &v);

    Q_INVOKABLE static QString makeObjectName(const QVariant &v=QVariant());

    Q_INVOKABLE static QVariantMap objectToMap(const QObject *object);
    Q_INVOKABLE static bool objectFromMap(QObject*object, const QVariant&v);

    Q_INVOKABLE static QVariantHash objectToHash(const QObject *object);
    Q_INVOKABLE static bool objectFromHash(QObject*object, const QVariant&v);

signals:

};

#endif // MUObjectUtil_H

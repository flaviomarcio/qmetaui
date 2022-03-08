#pragma once

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
#include "./mu_global.h"

class Q_MU_EXPORT MUGeometryUtil : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit MUGeometryUtil(QObject *parent = nullptr);
    ~MUGeometryUtil();

    static Q_INVOKABLE MUGeometryUtil&i();

    Q_INVOKABLE static const QVariant ifThen(const QVariant &vThen, const QVariant &vElse);
    Q_INVOKABLE static bool isDefined(const QVariant &v);
    Q_INVOKABLE static bool isUndefined(const QVariant &v);

    Q_INVOKABLE static int desktopAvailableWidth();
    Q_INVOKABLE static void setDesktopAvailableWidth(int value);

    Q_INVOKABLE static int desktopAvailableHeight();
    Q_INVOKABLE static void setDesktopAvailableHeight(int value);

    Q_INVOKABLE static double toDoubleSize(const QVariant &v, QVariant defaultValue=0);
    Q_INVOKABLE static qlonglong toIntSize(const QVariant &v, QVariant defaultValue=0);
    Q_INVOKABLE static const QString toProportion(const QVariant &v);
    Q_INVOKABLE static double calcProportion(const QVariant &vSize, const QVariant &vSizeMax=0);

    Q_INVOKABLE static double proportion();
    Q_INVOKABLE static double proportionFont();

    Q_INVOKABLE static double heightBase();
    Q_INVOKABLE static double widthBase();

    Q_INVOKABLE static void hideSplashScreen();
private:
        void init();
};

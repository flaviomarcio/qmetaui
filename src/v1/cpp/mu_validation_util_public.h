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

class Q_MU_EXPORT MUValidationUtilPublic : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    Q_INVOKABLE explicit MUValidationUtilPublic(QObject *parent = nullptr);
    ~MUValidationUtilPublic();

    Q_INVOKABLE static bool isEmail(const QVariant&v);
    Q_INVOKABLE static bool isPhoneNumber(const QVariant&v);

    static MUValidationUtilPublic &i();
};

//Q_DECLARE_METATYPE(MUValidationUtilPublic)

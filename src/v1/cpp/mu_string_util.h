#ifndef MUStringUtil_H
#define MUStringUtil_H

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

#define V_MUStringUtil()\
    auto&u=MUStringUtil::i();

#define MU_DECLARE_MUStringUtil()\
public:\
    static MUStringUtil&u(){\
        return MUStringUtil::i();\
    }

class Q_MU_EXPORT MUStringUtil : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit MUStringUtil(QObject *parent = nullptr);

    ~MUStringUtil();

    Q_INVOKABLE static MUStringUtil&i();

    Q_INVOKABLE static bool isDebug();

    Q_INVOKABLE static const QVariant getEnv(const QVariant &env, const QVariant &defaultValue=QVariant());

    Q_INVOKABLE static const QVariant ifThen(const QVariant &vThen, const QVariant &vElse);
    Q_INVOKABLE static bool isDefined(const QVariant &v);
    Q_INVOKABLE static bool isUndefined(const QVariant &v);
    Q_INVOKABLE static bool isEmpty(const QVariant &v);
    Q_INVOKABLE static QVariant isEmptySet(const QVariant &vThen, const QVariant &vElse);

    Q_INVOKABLE static const QVariantMap toMap(const QVariant&v);

    Q_INVOKABLE static const QByteArray toMd5(const QVariant &v);
    Q_INVOKABLE static const QString toStr(const QVariant &v, QString defaultValue=QString());
    Q_INVOKABLE static const QString toStrNumber(const QVariant &v);
    Q_INVOKABLE static const QString toStrPhone(const QVariant &v);
    Q_INVOKABLE static const QString toStrDouble(const QVariant &v);
    Q_INVOKABLE static const QString toStrAlignLeft(int width, const QVariant &fill, const QVariant &v);
    Q_INVOKABLE static const QString toStrAlignRight(int width, const QVariant &fill, const QVariant &v);
    Q_INVOKABLE static const QVariant toVar(const QVariant &v);
    Q_INVOKABLE static bool toBoo(const QVariant &v);
    Q_INVOKABLE static const QByteArray toJson(const QVariant &v);
    Q_INVOKABLE static const QByteArray toCBor(const QVariant &v);
    Q_INVOKABLE static const QColor toColor(const QVariant &v, const QColor &defaultValue=Qt::transparent);
    Q_INVOKABLE static qlonglong toInt(const QVariant &v, QVariant defaultValue=0);

    Q_INVOKABLE static double toDouble(const QVariant &v, QVariant defaultValue=0);

    Q_INVOKABLE static const QVariant convertVar(const QVariant &v, const QVariant::Type&type);

    Q_INVOKABLE static const QVariant toAlignment(const QVariant&v, Qt::Alignment alignment=Qt::AlignCenter);

    Q_INVOKABLE static int toVariantType(const QVariant&v);
    Q_INVOKABLE static const QByteArray toVariantTypeName(int v);

    Q_INVOKABLE static const QByteArray loadFile(const QString&file);
    Q_INVOKABLE static const QVariant loadFileMap(const QString&file);
    Q_INVOKABLE static const QVariant loadJsonFile(const QString&file);
    Q_INVOKABLE static const QVariant loadCBorFile(const QString&file);

    Q_INVOKABLE static const QString inputText(const QString&value);
    Q_INVOKABLE static const QString inputMaskClean(const QString&mask);
    Q_INVOKABLE static const QString inputMaskFormat(const QString&mask, const QString&value);
    Q_INVOKABLE static int inputMaskLength(const QString&mask, const QString&value);
    Q_INVOKABLE static int inputMaskCursorPosition(const QString&mask, const QString&value);

    Q_INVOKABLE static QString isUuidString( const QString&value );

};

//Q_DECLARE_METATYPE(MUStringUtil             )

#endif // MUStringUtil_H

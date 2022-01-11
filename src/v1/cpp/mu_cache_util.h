#ifndef MUCacheUtil_H
#define MUCacheUtil_H

#include <QObject>
#include <QVariant>
#include <QDateTime>
#include <QVariantMap>
#include <QVariantList>
#include <QVariant>
#include <QDateTime>
#include <QJsonObject>
#include <QJsonDocument>
#include <QStandardPaths>
#include <QQuickItem>
#include <QCborParserError>
#include "./mu_global.h"

class Q_MU_EXPORT MUCacheUtil : public QObject
{
    Q_OBJECT
public:

    Q_INVOKABLE explicit MUCacheUtil(QObject *parent = nullptr);
    ~MUCacheUtil();

    Q_INVOKABLE static MUCacheUtil&i();

    Q_INVOKABLE static const QVariant ifThen(const QVariant &vThen, const QVariant &vElse);
    Q_INVOKABLE static bool isDefined(const QVariant &v);
    Q_INVOKABLE static bool isUndefined(const QVariant &v);

    Q_INVOKABLE static QString sessionDir();
    Q_INVOKABLE static QString sessionDir(const QString&fileName);
    Q_INVOKABLE static QString tempDir();
    Q_INVOKABLE static QString tempDir(const QString&fileName);
    Q_INVOKABLE static QString cacheDir();
    Q_INVOKABLE static QString cacheDir(const QString&fileName);
    Q_INVOKABLE static QString appDataDir();
    Q_INVOKABLE static QString appDataDir(const QString&fileName);

    Q_INVOKABLE static void tempDirClear();
    Q_INVOKABLE static void cacheDirClear();
    Q_INVOKABLE static void appDataDirClear();
    Q_INVOKABLE static void sessionDirClear();
    Q_INVOKABLE static void dirClear();

    Q_INVOKABLE static bool fileExists(const QString&fileName);

    Q_INVOKABLE static QString sessionFileName();
    Q_INVOKABLE static bool sessionSaveFile(const QVariant &bytes);
    Q_INVOKABLE static const QByteArray sessionLoadFile();
    Q_INVOKABLE static bool sessionRemoveFile();

    Q_INVOKABLE static QString appFileName();
    Q_INVOKABLE static bool appSaveFile(const QVariant &bytes);
    Q_INVOKABLE static const QByteArray appLoadFile();
    Q_INVOKABLE static bool appRemoveFile();

    Q_INVOKABLE static bool saveFile(const QString&file, const QVariant&vBytes);
    Q_INVOKABLE static const QByteArray loadFile(const QString&file);

    Q_INVOKABLE static const QVariantMap loadFileMap(const QString&file);
    Q_INVOKABLE static const QVariantList loadFileList(const QString&file);

    Q_INVOKABLE static bool saveJsonFile(const QString&file, const QVariant&vBytes);
    Q_INVOKABLE static const QVariant loadJsonFile(const QString&file);

    Q_INVOKABLE static bool saveCBorFile(const QString&file, const QVariant&vBytes);
    Q_INVOKABLE static const QVariant loadCBorFile(const QString&file);

    Q_INVOKABLE static bool saveCryptoFile(const QString&file, const QVariant &vBytes);
    Q_INVOKABLE static const QByteArray loadCryptoFile(const QString&fileName);

    static void init();

};

#endif // MUCacheUtil_H

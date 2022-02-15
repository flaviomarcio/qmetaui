#pragma once

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
#include <QtQml>
#include "./mu_global.h"

//!
//! \brief The MUCacheUtil class
//!
class Q_MU_EXPORT MUCacheUtil : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:

    //!
    //! \brief MUCacheUtil
    //! \param parent
    //!
    Q_INVOKABLE explicit MUCacheUtil(QObject *parent = nullptr);
    ~MUCacheUtil();

    //!
    //! \brief i
    //! \return
    //!
    Q_INVOKABLE static MUCacheUtil&i();

    //!
    //! \brief ifThen
    //! \param vThen
    //! \param vElse
    //! \return
    //!
    Q_INVOKABLE static const QVariant ifThen(const QVariant &vThen, const QVariant &vElse);

    //!
    //! \brief isDefined
    //! \param v
    //! \return
    //!
    Q_INVOKABLE static bool isDefined(const QVariant &v);

    //!
    //! \brief isUndefined
    //! \param v
    //! \return
    //!
    Q_INVOKABLE static bool isUndefined(const QVariant &v);

    //!
    //! \brief sessionDir
    //! \return
    //!
    Q_INVOKABLE static QString sessionDir();
    Q_INVOKABLE static QString sessionDir(const QString&fileName);

    //!
    //! \brief tempDir
    //! \return
    //!
    Q_INVOKABLE static QString tempDir();
    Q_INVOKABLE static QString tempDir(const QString&fileName);

    //!
    //! \brief cacheDir
    //! \return
    //!
    Q_INVOKABLE static QString cacheDir();
    Q_INVOKABLE static QString cacheDir(const QString&fileName);

    //!
    //! \brief appDataDir
    //! \return
    //!
    Q_INVOKABLE static QString appDataDir();
    Q_INVOKABLE static QString appDataDir(const QString&fileName);

    //!
    //! \brief tempDirClear
    //!
    Q_INVOKABLE static void tempDirClear();

    //!
    //! \brief cacheDirClear
    //!
    Q_INVOKABLE static void cacheDirClear();

    //!
    //! \brief appDataDirClear
    //!
    Q_INVOKABLE static void appDataDirClear();

    //!
    //! \brief sessionDirClear
    //!
    Q_INVOKABLE static void sessionDirClear();

    //!
    //! \brief dirClear
    //!
    Q_INVOKABLE static void dirClear();

    //!
    //! \brief fileExists
    //! \param fileName
    //! \return
    //!
    Q_INVOKABLE static bool fileExists(const QString&fileName);

    //!
    //! \brief sessionFileName
    //! \return
    //!
    Q_INVOKABLE static QString sessionFileName();
    Q_INVOKABLE static bool sessionSaveFile(const QVariant &bytes);

    //!
    //! \brief sessionLoadFile
    //! \return
    //!
    Q_INVOKABLE static const QByteArray sessionLoadFile();

    //!
    //! \brief sessionRemoveFile
    //! \return
    //!
    Q_INVOKABLE static bool sessionRemoveFile();

    //!
    //! \brief appFileName
    //! \return
    //!
    Q_INVOKABLE static QString appFileName();

    //!
    //! \brief appSaveFile
    //! \param bytes
    //! \return
    //!
    Q_INVOKABLE static bool appSaveFile(const QVariant &bytes);

    //!
    //! \brief appLoadFile
    //! \return
    //!
    Q_INVOKABLE static const QByteArray appLoadFile();

    //!
    //! \brief appRemoveFile
    //! \return
    //!
    Q_INVOKABLE static bool appRemoveFile();

    //!
    //! \brief saveFile
    //! \param file
    //! \param vBytes
    //! \return
    //!
    Q_INVOKABLE static bool saveFile(const QString&file, const QVariant&vBytes);

    //!
    //! \brief loadFile
    //! \param file
    //! \return
    //!
    Q_INVOKABLE static const QByteArray loadFile(const QString&file);

    //!
    //! \brief loadFileMap
    //! \param file
    //! \return
    //!
    Q_INVOKABLE static const QVariantMap loadFileMap(const QString&file);

    //!
    //! \brief loadFileList
    //! \param file
    //! \return
    //!
    Q_INVOKABLE static const QVariantList loadFileList(const QString&file);

    //!
    //! \brief saveJsonFile
    //! \param file
    //! \param vBytes
    //! \return
    //!
    Q_INVOKABLE static bool saveJsonFile(const QString&file, const QVariant&vBytes);

    //!
    //! \brief loadJsonFile
    //! \param file
    //! \return
    //!
    Q_INVOKABLE static const QVariant loadJsonFile(const QString&file);

    //!
    //! \brief saveCBorFile
    //! \param file
    //! \param vBytes
    //! \return
    //!
    Q_INVOKABLE static bool saveCBorFile(const QString&file, const QVariant&vBytes);

    //!
    //! \brief loadCBorFile
    //! \param file
    //! \return
    //!
    Q_INVOKABLE static const QVariant loadCBorFile(const QString&file);

    //!
    //! \brief saveCryptoFile
    //! \param file
    //! \param vBytes
    //! \return
    //!
    Q_INVOKABLE static bool saveCryptoFile(const QString&file, const QVariant &vBytes);

    //!
    //! \brief loadCryptoFile
    //! \param fileName
    //! \return
    //!
    Q_INVOKABLE static const QByteArray loadCryptoFile(const QString&fileName);

    //!
    //! \brief init
    //!
    static void init();

};

#include "./mu_cache_util.h"
#include "./mu_object_util.h"
#include <QDir>
#include <QFile>
#include <QCryptographicHash>

#if (QT_VERSION >= QT_VERSION_CHECK(5, 10, 0))
#define AES_ENABLED
#endif

#ifdef AES_ENABLED
#include "./qtinyaes.h"
#endif

//https://www.allkeysgenerator.com/Random/Security-Encryption-Key-Generator.aspx
const QByteArray key_256bit("6E5A7234753778214125442A472D4B6150645367566B58703273357638792F42");
const QByteArray hash_key_256bit=QCryptographicHash::hash(key_256bit, QCryptographicHash::Sha256);

const QByteArray key_128bit("68566B59703373367639792442264529");
const QByteArray hash_key_128bit=QCryptographicHash::hash(key_128bit, QCryptographicHash::Sha256);

MUCacheUtil::MUCacheUtil(QObject *parent) : QObject{parent}
{

}

MUCacheUtil::~MUCacheUtil()
{

}

MUCacheUtil &MUCacheUtil::i()
{
    static MUCacheUtil __i;
    return __i;
}

const QVariant MUCacheUtil::ifThen(const QVariant &vThen, const QVariant &vElse)
{
    return MUObjectUtil::ifThen(vThen, vElse);
}

bool MUCacheUtil::isDefined(const QVariant &v)
{
    return MUObjectUtil::isDefined(v);
}

bool MUCacheUtil::isUndefined(const QVariant &v)
{
    return MUObjectUtil::isUndefined(v);
}

QString MUCacheUtil::sessionDir()
{
    return appDataDir();
}

QString MUCacheUtil::sessionDir(const QString &fileName)
{
    return QStringLiteral("%1/%2").arg(sessionDir(), fileName);
}

QString MUCacheUtil::tempDir()
{
    return QStandardPaths::writableLocation(QStandardPaths::TempLocation);
}

QString MUCacheUtil::tempDir(const QString &fileName)
{
    return QStringLiteral("%1/%2").arg(tempDir(), fileName);
}

QString MUCacheUtil::cacheDir()
{
    return QStringLiteral("%1/cache").arg(tempDir());
}

QString MUCacheUtil::cacheDir(const QString &fileName)
{
    return QStringLiteral("%1/%2").arg(cacheDir(), fileName);
}

QString MUCacheUtil::appDataDir()
{
    return QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
}

QString MUCacheUtil::appDataDir(const QString &fileName)
{
    return QStringLiteral("%1/%2").arg(appDataDir(), fileName);
}

void MUCacheUtil::tempDirClear()
{
    auto __dir = tempDir();
    QDir().rmpath(__dir);
}

void MUCacheUtil::cacheDirClear()
{
    auto __dir = cacheDir();
    QDir().rmpath(__dir);
}

void MUCacheUtil::appDataDirClear()
{
    auto __dir = appDataDir();
    QDir().rmpath(__dir);
}

void MUCacheUtil::sessionDirClear()
{
    auto __dir = sessionDir();
    QDir().rmpath(__dir);
}

void MUCacheUtil::dirClear()
{
    tempDirClear();
    cacheDirClear();
    appDataDirClear();
    sessionDirClear();
    init();
}

bool MUCacheUtil::fileExists(const QString &fileName)
{
    return QFile::exists(fileName);
}

QString MUCacheUtil::sessionFileName()
{
    auto sessionFile=QCryptographicHash::hash(QByteArrayLiteral("session"), QCryptographicHash::Md5).toHex();
    return sessionDir(sessionFile);
}

bool MUCacheUtil::sessionSaveFile(const QVariant &bytes)
{
    return saveCryptoFile(sessionFileName(), bytes);
}

const QByteArray MUCacheUtil::sessionLoadFile()
{
    return loadCryptoFile(sessionFileName());
}

bool MUCacheUtil::sessionRemoveFile()
{
    QFile f(sessionFileName());
    f.remove();
    return !f.exists();
}

QString MUCacheUtil::appFileName()
{
    auto appFile=QCryptographicHash::hash(QByteArrayLiteral("app"), QCryptographicHash::Md5).toHex();
    return appDataDir(appFile);
}

bool MUCacheUtil::appSaveFile(const QVariant &bytes)
{
    return saveCryptoFile(appFileName(), bytes);
}

const QByteArray MUCacheUtil::appLoadFile()
{
    return loadCryptoFile(appFileName());
}

bool MUCacheUtil::appRemoveFile()
{
    QFile f(appFileName());
    f.remove();
    return !f.exists();
}

bool MUCacheUtil::saveFile(const QString &file, const QVariant &vBytes)
{
    QFile f(file);
    if(f.open(QFile::Truncate | QFile::WriteOnly)){
        f.write(vBytes.toByteArray());
        f.flush();
        f.close();
        return true;
    }
    return false;
}

const QByteArray MUCacheUtil::loadFile(const QString &file)
{
    QByteArray r;
    QFile f(file);
    if(f.open(QFile::ReadOnly)){
        r=f.readAll();
        f.close();
    }
    return r;
}

void MUCacheUtil::init()
{
    auto mkDir=[](QString sDir){
        QDir dir(sDir);
        if(!dir.exists())
            dir.mkpath(sDir);
    };

    mkDir(appDataDir());
    mkDir(cacheDir());
    mkDir(sessionDir());
}



bool MUCacheUtil::saveJsonFile(const QString &file, const QVariant &vBytes)
{
    auto type=vBytes.type();
    QByteArray bytes;
    if(type==QVariant::Map || type==QVariant::List || type==QVariant::StringList || type==QVariant::Hash){
        bytes=QJsonDocument::fromVariant(vBytes).toJson(QJsonDocument::Compact);
    }
    else{
        bytes=vBytes.toByteArray();
    }

    QFile f(file);
    if(f.open(QFile::Truncate | QFile::WriteOnly)){
        f.write(bytes);
        f.flush();
        f.close();
        return true;
    }
    return false;
}

const QVariantMap MUCacheUtil::loadFileMap(const QString &file)
{
    auto v=loadJsonFile(file);
    if(!v.isValid() || v.isNull())
        v=loadCBorFile(file);
    return v.toMap();
}

const QVariantList MUCacheUtil::loadFileList(const QString &file)
{
    auto v=loadJsonFile(file);
    if(!v.isValid() || v.isNull())
        v=loadCBorFile(file);
    return v.toList();
}

const QVariant MUCacheUtil::loadJsonFile(const QString &file)
{
    auto bytes=loadFile(file).trimmed();
    QJsonParseError*error=nullptr;
    auto doc=QJsonDocument::fromJson(bytes, error);
    if(error!=nullptr)
        mWarning()<<error->errorString();
    else
        return doc.toVariant();
    return QVariant();
}

bool MUCacheUtil::saveCBorFile(const QString &file, const QVariant &vBytes)
{
    auto type=vBytes.type();
    QByteArray bytes;
    if(type==QVariant::Map || type==QVariant::List || type==QVariant::StringList || type==QVariant::Hash){
        bytes=QCborValue::fromVariant(vBytes).toCbor();
    } else {
        bytes=vBytes.toByteArray();
    }

    QFile f(file);
    if(f.open(QFile::Truncate | QFile::WriteOnly)){
        f.write(bytes);
        f.flush();
        f.close();
        return true;
    }
    return false;
}

const QVariant MUCacheUtil::loadCBorFile(const QString &file)
{
    auto bytes=loadFile(file).trimmed();
    QCborParserError*error=nullptr;
    auto doc=QCborValue::fromCbor(bytes, error);
    if(error!=nullptr)
        mWarning()<<error->errorString();
    else
        return doc.toVariant();
    return QVariant();
}

bool MUCacheUtil::saveCryptoFile(const QString &file, const QVariant &vBytes)
{
    auto type=vBytes.type();
    QByteArray buffer;
    if(type==QVariant::Map || type==QVariant::List || type==QVariant::StringList || type==QVariant::Hash)
        buffer=QJsonDocument::fromVariant(vBytes).toJson(QJsonDocument::Compact);
    else
        buffer=vBytes.toByteArray();
    init();
    QFile f(file);
    if(!f.open(QFile::Truncate | QFile::WriteOnly)){
        mWarning()<<f.errorString();
    }
    else{
#ifdef AES_ENABLED
        if(!buffer.isEmpty()){//necessario pois vai dar crash se for errado
            QTinyAes aes(QTinyAes::CTR, hash_key_256bit, hash_key_128bit);
            buffer=aes.encrypt(buffer);
        }
#endif
        f.write(buffer);
        f.flush();
        f.close();
        return true;
    }
    return false;
}

const QByteArray MUCacheUtil::loadCryptoFile(const QString &fileName)
{
    auto buffer = loadFile(fileName);
#ifdef AES_ENABLED
    if(!buffer.isEmpty()){//necessario pois vai dar crash se for errado
        QTinyAes aes(QTinyAes::CTR, hash_key_256bit, hash_key_128bit);
        //todo flavio entender forma de testar antes para conversao para evitar crash
        static const int AES_BLOCKLEN=16;
        static const int BlockSize(AES_BLOCKLEN);
        if(buffer.size() % BlockSize == 0)
            buffer=aes.decrypt(buffer);
        else
            return buffer;
    }
#endif
    return buffer;
}

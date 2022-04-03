#include "./mu_variant_util.h"
#include "./mu_object_util.h"
#include <QCryptographicHash>
#include <QJsonDocument>
#include <QJsonValue>
#include <QFile>
#include <QBitArray>
#include <QDateTime>
#include <QUrl>
#include <QUuid>
#include <QColor>
#include <QQuickItem>
#include <QStm>

Q_GLOBAL_STATIC(MUVariantUtil, __i)

MUVariantUtil::MUVariantUtil(QObject *parent) : QObject{parent}
{

}

MUVariantUtil::~MUVariantUtil()
{

}

MUVariantUtil &MUVariantUtil::i()
{
    return *__i;
}

bool MUVariantUtil::isDebug()
{
    return MUObjectUtil::isDebug();
}

const QVariant MUVariantUtil::ifThen(const QVariant &vThen, const QVariant &vElse)
{
    return MUObjectUtil::ifThen(vThen, vElse);
}

bool MUVariantUtil::isDefined(const QVariant &v)
{
    return MUObjectUtil::isDefined(v);
}

bool MUVariantUtil::isUndefined(const QVariant &v)
{
    return MUObjectUtil::isUndefined(v);
}


const QVariantMap MUVariantUtil::toMap(const QVariant &v)
{
    QVariant vv;
    switch (qTypeId(v)){
    case QMetaType_QString:
    case QMetaType_QByteArray:
    case QMetaType_QChar:
    case QMetaType_QBitArray:
    {
        auto v=QJsonDocument::fromJson(vv.toByteArray()).toVariant();
        if(v.isValid())
            return v.toMap();
        return QCborValue::fromCbor(v.toByteArray()).toVariant().toMap();

        break;
    }
    case QMetaType_QVariantMap:
    case QMetaType_QVariantList:
    case QMetaType_QStringList:
    case QMetaType_QVariantHash:
        return v.toMap();
    default:
        return {};
    }
}

const QByteArray MUVariantUtil::toMd5(const QVariant &v)
{
    auto bytes=MUVariantUtil::toBytes(v).toUtf8();
    return QCryptographicHash::hash(bytes, QCryptographicHash::Md5).toHex();
}

const QString MUVariantUtil::toStr(const QVariant &v, const QVariant&defaultValue)
{
    switch (qTypeId(v)){
    case QMetaType_QString:
    case QMetaType_QByteArray:
    case QMetaType_QChar:
    case QMetaType_QBitArray:
        return v.toString();
    case QMetaType_QVariantMap:
    case QMetaType_QVariantList:
    case QMetaType_QStringList:
    case QMetaType_QVariantHash:
        return (QJsonDocument::fromVariant(v).toJson(QJsonDocument::Compact));
    default:
        auto s=v.toString().trimmed();
        return s.isEmpty()?defaultValue.toString():s;
    }
}

const QString MUVariantUtil::toBytes(const QVariant &v, const QVariant &defaultValue)
{
    return toStr(v,defaultValue).toUtf8();
}

const QString MUVariantUtil::toStrNumber(const QVariant &v)
{
    auto text=v.toString();
    static auto textValid=qsl("01234567890");
    QString output;
    for(auto&c:text){
        if(textValid.contains(c))
            output+=c;
    }
    return output;
}

const QString MUVariantUtil::toStrDouble(const QVariant &v)
{
    auto text=v.toString();
    static auto textValid=qsl("01234567890%1").arg(QLocale::c().decimalPoint());
    QString output;
    for(auto&c:text){
        if(textValid.contains(c))
            output+=c;
    }
    return output;
}

const QVariant MUVariantUtil::toVar(const QVariant &v)
{
    switch (qTypeId(v)){
    case QMetaType_Int      :
        return v.toInt();
    case QMetaType_QTime     :
        return v.toTime();
    case QMetaType_QDate     :
        return v.toDate();
    case QMetaType_QDateTime :
        return v.toDateTime();
    case QMetaType_UInt     :
        return v.toInt();
    case QMetaType_Bool     :
        return v.toBool();
    case QMetaType_LongLong :
        return v.toLongLong();
    case QMetaType_ULongLong:
        return v.toULongLong();
    case QMetaType_Double   :
        return v.toDouble();
    case QMetaType_QString   :
        return v.toString();
    case QMetaType_QByteArray:
        return v.toByteArray();
    case QMetaType_QChar     :
        return v.toChar();
    case QMetaType_QBitArray :
        return v.toBitArray();
    case QMetaType_QUuid     :
        return v.toUuid();
    case QMetaType_QUrl      :
        return v.toUrl();
    case QMetaType_QObjectStar:
        return v;
    case QMetaType_QVariantHash:
    case QMetaType_QVariantMap:
        return v.toHash();
    case QMetaType_QVariantList:
    case QMetaType_QStringList:
        return v.toList();
    default:
        return {};
    }
}

bool MUVariantUtil::toBoo(const QVariant &v)
{
    return v.toBool();
}

const QByteArray MUVariantUtil::toJson(const QVariant &v)
{
    switch (qTypeId(v)){
    case QMetaType_QVariantHash:
    case QMetaType_QVariantMap:
    case QMetaType_QVariantList:
    case QMetaType_QStringList:
        return QJsonDocument::fromVariant(v).toJson(QJsonDocument::Compact);
    default:
        return {};
    }
}

const QVariant MUVariantUtil::toJsonVariant(const QVariant &v)
{
    switch (qTypeId(v)){
    case QMetaType_QVariantHash:
    case QMetaType_QVariantMap:
    case QMetaType_QVariantList:
    case QMetaType_QStringList:
        return v;
    case QMetaType_QString:
    case QMetaType_QByteArray:
        return QJsonDocument::fromJson(v.toByteArray()).toVariant();
    default:
        return {};
    }
}

const QByteArray MUVariantUtil::toCBor(const QVariant &v)
{
    switch (qTypeId(v)){
    case QMetaType_QVariantHash:
    case QMetaType_QVariantMap:
    case QMetaType_QVariantList:
    case QMetaType_QStringList:
        return QJsonDocument::fromVariant(v).toJson(QJsonDocument::Compact);
    case QMetaType_QString:
    case QMetaType_QByteArray:
        return QJsonDocument::fromJson(v.toByteArray()).toJson(QJsonDocument::Compact);
    default:
        return {};
    }
}

const QColor MUVariantUtil::toColor(const QVariant &v, const QColor&defaultValue)
{
    switch (qTypeId(v)){
    case QMetaType_QColor:
        return v.toString();
    default:
        return defaultValue;
    }
}

qlonglong MUVariantUtil::toInt(const QVariant &v, QVariant defaultValue)
{
    switch (qTypeId(v)){
    case QMetaType_Double:
    case QMetaType_Int:
    case QMetaType_UInt:
    case QMetaType_LongLong:
    case QMetaType_ULongLong:
    case QMetaType_QString:
    case QMetaType_QByteArray:
    case QMetaType_QChar:
    case QMetaType_QBitArray:{
        auto value=v.toLongLong();
        if(value>0)
            return value;
        break;
    }
    default:
        break;
    }
    return defaultValue.toLongLong();
}

double MUVariantUtil::toDouble(const QVariant &v, QVariant defaultValue)
{
    switch (qTypeId(v)){
    case QMetaType_Double:
    case QMetaType_Int:
    case QMetaType_UInt:
    case QMetaType_LongLong:
    case QMetaType_ULongLong:
    case QMetaType_QString:
    case QMetaType_QByteArray:
    case QMetaType_QChar:
    case QMetaType_QBitArray:{
        auto value=v.toLongLong();
        if(value>0)
            return value;
        break;
    }
    default:
        break;
    }
    return defaultValue.toDouble();
}

const QVariant MUVariantUtil::convertVar(const QVariant &v, const int type)
{
    if(type==qTypeId(v))
        return v;

    switch (type){
    case QMetaType_QVariantList:
        return v.toList();
    case QMetaType_QVariantMap:
        return v.toMap();
    case QMetaType_QVariantHash:
        return v.toHash();
    case QMetaType_QStringList:
        return v.toStringList();
    case QMetaType_Int:
        return v.toInt();
    case QMetaType_UInt:
        return v.toInt();
    case QMetaType_LongLong:
        return v.toLongLong();
    case QMetaType_ULongLong:
        return v.toULongLong();
    case QMetaType_Double:
        return v.toDouble();
    case QMetaType_QTime:
        return v.toTime();
    case QMetaType_QDate:
        return v.toDate();
    case QMetaType_QDateTime:
        return v.toDateTime();
    case QMetaType_QString:
        return v.toString();
    case QMetaType_QByteArray:
        return v.toByteArray();
    case QMetaType_QChar:
        return v.toChar();
    case QMetaType_QBitArray:
        return v.toBitArray();
    case QMetaType_Bool:
        return v.toBool();
    case QMetaType_QUuid:
        return v.toUuid();
    case QMetaType_QUrl:
        return v.toUrl();
    case QMetaType_QColor:
        return QColor(Qt::transparent);
    default:
        return {};
    }
}

const QVariant MUVariantUtil::toAlignment(const QVariant &v, Qt::Alignment alignment)
{
    static QHash<QString,Qt::Alignment> map;

#define addAlignment(t,v)\
    map.insert(QString(#v).toLower(), t::v);

    if(map.isEmpty()){
        addAlignment(Qt,AlignLeft             )
        addAlignment(Qt,AlignLeading          )
        addAlignment(Qt,AlignRight            )
        addAlignment(Qt,AlignTrailing         )
        addAlignment(Qt,AlignHCenter          )
        addAlignment(Qt,AlignJustify          )
        addAlignment(Qt,AlignAbsolute         )
        addAlignment(Qt,AlignHorizontal_Mask  )
        addAlignment(Qt,AlignTop              )
        addAlignment(Qt,AlignBottom           )
        addAlignment(Qt,AlignVCenter          )
        addAlignment(Qt,AlignBaseline         )
        addAlignment(Qt,AlignVertical_Mask    )
        addAlignment(Qt,AlignCenter           )
    }

    auto l = v.toString().toLower().trimmed().replace("text.","").replace(" ","").split('|');

    QHashIterator<QString, Qt::Alignment> i(map);
    while (i.hasNext()) {
        i.next();
        if(l.contains(i.key()))
            alignment = alignment | i.value();
    }
    return QVariant(alignment);
}

int MUVariantUtil::toVariantType(const QVariant &v)
{
    static QHash<QString, int> map;
#define addVariantType(t,v)\
    map.insert(qsl("%1::%2").arg(#t, #v).toLower(), t::v);\
    map.insert(qsl("%1::%2").arg(#t, #v), t::v);\
    map.insert(QString(#t).toLower(), t::v);\
    map.insert(#t, t::v);

    if(map.isEmpty()){
        addVariantType(QMetaType, QVariantList)
        addVariantType(QMetaType, QVariantMap)
        addVariantType(QMetaType, QVariantHash)
        addVariantType(QMetaType, QStringList)
        addVariantType(QMetaType, Int)
        addVariantType(QMetaType, UInt)
        addVariantType(QMetaType, LongLong)
        addVariantType(QMetaType, ULongLong)
        addVariantType(QMetaType, Double)
        addVariantType(QMetaType, QTime)
        addVariantType(QMetaType, QDate)
        addVariantType(QMetaType, QDateTime)
        addVariantType(QMetaType, QString)
        addVariantType(QMetaType, QByteArray)
        addVariantType(QMetaType, QChar)
        addVariantType(QMetaType, QBitArray)
        addVariantType(QMetaType, Bool)
        addVariantType(QMetaType, QUuid)
        addVariantType(QMetaType, QUrl)
    }


    auto s = v.toString().trimmed().toLower();
    auto type = map.contains(s) ? map.value(s) : QMetaType_UnknownType;
    return type;
}

//const QByteArray MUVariantUtil::toVariantTypeName(int v)
//{
//    return QMetaType_typeName(v);
//}

bool MUVariantUtil::isEqual(const QVariant &v1, const QVariant &v2)
{
    auto s1=toStr(v1, qsl_null);
    auto s2=toStr(v2, qsl_null);
    if(s1==s2)
        return true;
    return false;
}

bool MUVariantUtil::isDiff(const QVariant &v1, const QVariant &v2)
{
    return !isEqual(v1,v2);
}


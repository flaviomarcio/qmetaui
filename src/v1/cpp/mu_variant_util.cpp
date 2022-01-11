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


MUVariantUtil::MUVariantUtil(QObject *parent) : QObject(parent)
{

}

MUVariantUtil::~MUVariantUtil()
{

}

MUVariantUtil &MUVariantUtil::i()
{
    static MUVariantUtil __i;
    return  __i;
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
    QVariant vv=
    (v.canConvert(QVariant::Map) || v.canConvert(QVariant::Hash))
                 ?
                     v.toMap()
                 :
                     v.canConvert(QVariant::String)||v.canConvert(QVariant::ByteArray)
                     ?
                        v.toString()
                        :
                         QVariant()
                ;

    QVariantMap map;
    if(vv.canConvert(QVariant::Map) || vv.canConvert(QVariant::Hash))
        map=vv.toMap();
    else{
        QJsonParseError*parser=nullptr;
        map=QJsonDocument::fromJson(vv.toByteArray(), parser).object().toVariantMap();

        if(parser!=nullptr){
            map=QCborValue::fromCbor(v.toByteArray()).toVariant().toMap();
        }
    }

    return map;
}

const QByteArray MUVariantUtil::toMd5(const QVariant &v)
{
    auto bytes=MUVariantUtil::toBytes(v).toUtf8();
    return QCryptographicHash::hash(bytes, QCryptographicHash::Md5).toHex();
}

const QString MUVariantUtil::toStr(const QVariant &v, const QVariant&defaultValue)
{
    if(v.canConvert(QVariant::String) || v.canConvert(QVariant::ByteArray) || v.canConvert(QVariant::Char) || v.canConvert(QVariant::BitArray))
        return v.toString();
    else if(v.canConvert(QVariant::Map) || v.canConvert(QVariant::List) || v.canConvert(QVariant::StringList) || v.canConvert(QVariant::Hash))
        return (QJsonDocument::fromVariant(v).toJson(QJsonDocument::Compact));
    else{
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
    auto textValid=QString("01234567890");
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
    auto textValid=QString("01234567890%1").arg(QLocale::c().decimalPoint());
    QString output;
    for(auto&c:text){
        if(textValid.contains(c))
            output+=c;
    }
    return output;
}

const QVariant MUVariantUtil::toVar(const QVariant &v)
{
    QVariant vReturn;
    if(v.canConvert(QVariant::Int       ))
        vReturn=v.toInt();
    else if(v.canConvert(QVariant::Time      ))
        vReturn=v.toTime();
    else if(v.canConvert(QVariant::Date      ))
        vReturn=v.toDate();
    else if(v.canConvert(QVariant::DateTime  ))
        vReturn=v.toDateTime();
    else if(v.canConvert(QVariant::UInt      ))
        vReturn=v.toInt();
    else if(v.canConvert(QVariant::Bool      ))
        vReturn=v.toBool();
    else if(v.canConvert(QVariant::LongLong  ))
        vReturn=v.toLongLong();
    else if(v.canConvert(QVariant::ULongLong ))
        vReturn=v.toULongLong();
    else if(v.canConvert(QVariant::Double    ))
        vReturn=v.toDouble();
    else if(v.canConvert(QVariant::String    ))
        vReturn=v.toString();
    else if(v.canConvert(QVariant::ByteArray ))
        vReturn=v.toByteArray();
    else if(v.canConvert(QVariant::Char      ))
        vReturn=v.toChar();
    else if(v.canConvert(QVariant::BitArray  ))
        vReturn=v.toBitArray();
    else if(v.canConvert(QVariant::Uuid      ))
        vReturn=v.toUuid();
    else if(v.canConvert(QVariant::Url       ))
        vReturn=v.toUrl();
    else if(v.canConvert(QMetaType::QObjectStar ))
        vReturn=v;
    else{

        if(v.canConvert(QVariant::Map) || v.canConvert(QVariant::Hash) || v.canConvert(QVariant::List) || v.canConvert(QVariant::StringList)){
            if(!vReturn.isValid()){
                auto vv=v.toList();
                if(!vv.isEmpty())
                    vReturn=vv;
            }

            if(!vReturn.isValid()){
                auto vv=v.toMap();
                if(!vv.isEmpty())
                    vReturn=vv;
            }

            if(!vReturn.isValid()){
                auto vv=v.toHash();
                if(!vv.isEmpty())
                    vReturn=vv;
            }

            if(!vReturn.isValid()){
                auto vv=v.toStringList();
                if(!vv.isEmpty())
                    vReturn=vv;
            }
        }


    }

    return vReturn;
}

bool MUVariantUtil::toBoo(const QVariant &v)
{
    return v.toBool();
}

const QByteArray MUVariantUtil::toJson(const QVariant &v)
{
    QByteArray bytes;
    if(v.type()==QVariant::Map || v.type()==QVariant::Hash || v.type()==QVariant::List)
        bytes=QJsonDocument::fromVariant(v).toJson(QJsonDocument::Compact);
    return bytes;
}

const QVariant MUVariantUtil::toJsonVariant(const QVariant &v)
{
    auto type=v.type();
    if(type==QVariant::List || type==QVariant::Map || type==QVariant::Hash || type==QVariant::StringList)
        return v;
    else
        return QJsonDocument::fromJson(v.toByteArray()).toVariant();
}

const QByteArray MUVariantUtil::toCBor(const QVariant &v)
{
    auto type=v.type();
    if(type==QVariant::List || type==QVariant::Map || type==QVariant::Hash || type==QVariant::StringList)
        return QJsonValue::fromVariant(v).toString().toUtf8();
    else
        return v.toByteArray();

}

const QColor MUVariantUtil::toColor(const QVariant &v, const QColor&defaultValue)
{
    if(v.canConvert(QVariant::Color))
        return v.toString();
    else
        return defaultValue;
}

qlonglong MUVariantUtil::toInt(const QVariant &v, QVariant defaultValue)
{
    if(v.canConvert(QVariant::LongLong))
        return v.toLongLong();
    else
        return defaultValue.toLongLong();
}

double MUVariantUtil::toDouble(const QVariant &v, QVariant defaultValue)
{
    if(v.canConvert(QVariant::Double))
        return v.toDouble();
    else
        return defaultValue.toDouble();
}

const QVariant MUVariantUtil::convertVar(const QVariant &v, const QVariant::Type &type)
{
    if(type==v.type())
        return v;
    else if(type==QVariant::List       )
        return v.toList();
    else if(type==QVariant::Map        )
        return v.toMap();
    else if(type==QVariant::Hash       )
        return v.toHash();
    else if(type==QVariant::StringList )
        return v.toStringList();
    else if(type==QVariant::Int        )
        return v.toInt();
    else if(type==QVariant::UInt       )
        return v.toInt();
    else if(type==QVariant::LongLong   )
        return v.toLongLong();
    else if(type==QVariant::ULongLong  )
        return v.toULongLong();
    else if(type==QVariant::Double     )
        return v.toDouble();
    else if(type==QVariant::Time       )
        return v.toTime();
    else if(type==QVariant::Date       )
        return v.toDate();
    else if(type==QVariant::DateTime   )
        return v.toDateTime();
    else if(type==QVariant::String     )
        return v.toString();
    else if(type==QVariant::ByteArray  )
        return v.toByteArray();
    else if(type==QVariant::Char       )
        return v.toChar();
    else if(type==QVariant::BitArray   )
        return v.toBitArray();
    else if(type==QVariant::Bool       )
        return v.toBool();
    else if(type==QVariant::Uuid       )
        return v.toUuid();
    else if(type==QVariant::Url        )
        return v.toUrl();
    else if(type==QVariant::Color && v.canConvert(QVariant::Color))
        return v;
    else if(type==QVariant::Color)
        return QColor(Qt::transparent);
    else
        return QVariant();
}

const QVariant MUVariantUtil::toAlignment(const QVariant &v, Qt::Alignment alignment)
{
    static QMap<QString,Qt::Alignment> map;

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

    QMapIterator<QString, Qt::Alignment> i(map);
    while (i.hasNext()) {
        i.next();
        if(l.contains(i.key()))
            alignment = alignment | i.value();
    }
    return QVariant(alignment);
}

int MUVariantUtil::toVariantType(const QVariant &v)
{
    static QMap<QString,QVariant::Type> map;
#define addVariantType(t,v)\
    map.insert(QString("%1::%2").arg(#t).arg(#v).toLower(), t::v);\
    map.insert(QString("%1::%2").arg(#t).arg(#v), t::v);\
    map.insert(QString(#t).toLower(), t::v);\
    map.insert(#t, t::v);

    if(map.isEmpty()){
        addVariantType(QVariant, List       )
        addVariantType(QVariant, Map        )
        addVariantType(QVariant, Hash       )
        addVariantType(QVariant, StringList )
        addVariantType(QVariant, Int        )
        addVariantType(QVariant, UInt       )
        addVariantType(QVariant, LongLong   )
        addVariantType(QVariant, ULongLong  )
        addVariantType(QVariant, Double     )
        addVariantType(QVariant, Time       )
        addVariantType(QVariant, Date       )
        addVariantType(QVariant, DateTime   )
        addVariantType(QVariant, String     )
        addVariantType(QVariant, ByteArray  )
        addVariantType(QVariant, Char       )
        addVariantType(QVariant, BitArray   )
        addVariantType(QVariant, Bool       )
        addVariantType(QVariant, Uuid       )
        addVariantType(QVariant, Url        )
    }


    auto s = v.toString().trimmed().toLower();
    auto type = map.contains(s) ? map.value(s) : QVariant::Invalid;
    return type;
}

const QByteArray MUVariantUtil::toVariantTypeName(int v)
{
    return QMetaType::typeName(v);
}

bool MUVariantUtil::isEqual(const QVariant &v1, const QVariant &v2)
{
    auto s1=toStr(v1,"");
    auto s2=toStr(v2,"");
    if(s1==s2)
        return true;
    else
        return false;
}

bool MUVariantUtil::isDiff(const QVariant &v1, const QVariant &v2)
{
    return !isEqual(v1,v2);
}


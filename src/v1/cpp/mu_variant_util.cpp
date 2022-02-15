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


typedef QHash<QString, QVariant::Type> AddVariantTypeHash;
Q_GLOBAL_STATIC(AddVariantTypeHash, addVariantTypeHash)

typedef QHash<QString,Qt::Alignment> ToAlignmentHash;
Q_GLOBAL_STATIC(ToAlignmentHash, toAlignmentHash)

Q_GLOBAL_STATIC(MUVariantUtil, muVariantUtil)


void init()
{
#define addVariantType(t,v)\
    addVariantTypeHash->insert(QString("%1::%2").arg(#t, #v).toLower(), t::v);\
    addVariantTypeHash->insert(QString("%1::%2").arg(#t, #v), t::v);\
    addVariantTypeHash->insert(QString(#t).toLower(), t::v);\
    addVariantTypeHash->insert(#t, t::v);

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


#define addAlignment(t,v) toAlignmentHash->insert(QString(#v).toLower(), t::v);

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


MUVariantUtil::MUVariantUtil(QObject *parent) : QObject(parent)
{

}

MUVariantUtil::~MUVariantUtil()
{

}

MUVariantUtil &MUVariantUtil::i()
{
    return*muVariantUtil;
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
    (v.canConvert(QMetaType_QVariantMap) || v.canConvert(QMetaType_QVariantHash))
                 ?
                     v.toHash()
                 :
                     v.canConvert(QMetaType_QString)||v.canConvert(QMetaType_QByteArray)
                     ?
                        v.toString()
                        :
                         QVariant()
                ;

    if(vv.canConvert(QMetaType_QVariantMap) || vv.canConvert(QMetaType_QVariantHash))
        return vv.toMap();

    QVariantMap __return;
    QJsonParseError*parser=nullptr;
    __return=QJsonDocument::fromJson(vv.toByteArray(), parser).object().toVariantMap();

    if(parser!=nullptr){
        __return=QCborValue::fromCbor(v.toByteArray()).toVariant().toMap();
    }

    return __return;
}

const QVariantHash MUVariantUtil::toHash(const QVariant &v)
{
    QVariant vv=
        (v.canConvert(QMetaType_QVariantMap) || v.canConvert(QMetaType_QVariantHash))
            ?
            v.toHash()
            :
            v.canConvert(QMetaType_QString)||v.canConvert(QMetaType_QByteArray)
                ?
                v.toString()
                :
                QVariant()
        ;

    if(vv.canConvert(QMetaType_QVariantMap) || vv.canConvert(QMetaType_QVariantHash))
        return vv.toHash();

    QVariantHash __return;
    QJsonParseError*parser=nullptr;
    __return=QJsonDocument::fromJson(vv.toByteArray(), parser).object().toVariantHash();

    if(parser!=nullptr){
        __return=QCborValue::fromCbor(v.toByteArray()).toVariant().toHash();
    }

    return __return;
}

const QByteArray MUVariantUtil::toMd5(const QVariant &v)
{
    auto bytes=MUVariantUtil::toBytes(v).toUtf8();
    return QCryptographicHash::hash(bytes, QCryptographicHash::Md5).toHex();
}

const QString MUVariantUtil::toStr(const QVariant &v, const QVariant&defaultValue)
{
    //TODO implement switch (typeId) {}
    if(v.canConvert(QMetaType_QString) || v.canConvert(QMetaType_QByteArray) || v.canConvert(QMetaType_QChar) || v.canConvert(QMetaType_QBitArray))
        return v.toString();

    if(v.canConvert(QMetaType_QVariantMap) || v.canConvert(QMetaType_QVariantList) || v.canConvert(QMetaType_QStringList) || v.canConvert(QMetaType_QVariantHash))
        return (QJsonDocument::fromVariant(v).toJson(QJsonDocument::Compact));

    auto s=v.toString().trimmed();
    return s.isEmpty()?defaultValue.toString():s;
}

const QString MUVariantUtil::toBytes(const QVariant &v, const QVariant &defaultValue)
{
    return toStr(v,defaultValue).toUtf8();
}

const QString MUVariantUtil::toStrNumber(const QVariant &v)
{
    auto text=v.toString();
    static const auto textValid=qsl("01234567890");
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
    const auto textValid=qsl("01234567890%1").arg(QLocale::c().decimalPoint());
    QString output;
    for(auto&c:text){
        if(textValid.contains(c))
            output+=c;
    }
    return output;
}

const QVariant MUVariantUtil::toVar(const QVariant &v)
{
    //TODO implement switch (typeId) {}
    QVariant vReturn;
    if(v.canConvert(QMetaType_Int       ))
        vReturn=v.toInt();
    else if(v.canConvert(QMetaType_QTime      ))
        vReturn=v.toTime();
    else if(v.canConvert(QMetaType_QDate      ))
        vReturn=v.toDate();
    else if(v.canConvert(QMetaType_QDateTime  ))
        vReturn=v.toDateTime();
    else if(v.canConvert(QVariant::UInt      ))
        vReturn=v.toInt();
    else if(v.canConvert(QMetaType_Bool      ))
        vReturn=v.toBool();
    else if(v.canConvert(QMetaType_LongLong  ))
        vReturn=v.toLongLong();
    else if(v.canConvert(QVariant::ULongLong ))
        vReturn=v.toULongLong();
    else if(v.canConvert(QMetaType_Double    ))
        vReturn=v.toDouble();
    else if(v.canConvert(QMetaType_QString    ))
        vReturn=v.toString();
    else if(v.canConvert(QMetaType_QByteArray ))
        vReturn=v.toByteArray();
    else if(v.canConvert(QMetaType_QChar      ))
        vReturn=v.toChar();
    else if(v.canConvert(QMetaType_QBitArray  ))
        vReturn=v.toBitArray();
    else if(v.canConvert(QMetaType_QUuid      ))
        vReturn=v.toUuid();
    else if(v.canConvert(QMetaType_QUrl       ))
        vReturn=v.toUrl();
    else if(v.canConvert(QMetaType_QObjectStar ))
        vReturn=v;
    else{

        //TODO implement switch (typeId) {}
        if(v.canConvert(QMetaType_QVariantMap) || v.canConvert(QMetaType_QVariantHash) || v.canConvert(QMetaType_QVariantList) || v.canConvert(QMetaType_QStringList)){
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
    //TODO implement switch (typeId) {}
    if(v.type()==QMetaType_QVariantMap || v.type()==QMetaType_QVariantHash || v.type()==QMetaType_QVariantList)
        bytes=QJsonDocument::fromVariant(v).toJson(QJsonDocument::Compact);
    return bytes;
}

const QVariant MUVariantUtil::toJsonVariant(const QVariant &v)
{
    //TODO implement switch (typeId) {}
    auto type=v.type();
    if(type==QMetaType_QVariantList || type==QMetaType_QVariantMap || type==QMetaType_QVariantHash || type==QMetaType_QStringList)
        return v;
    return QJsonDocument::fromJson(v.toByteArray()).toVariant();
}

const QByteArray MUVariantUtil::toCBor(const QVariant &v)
{
    //TODO implement switch (typeId) {}
    auto type=v.type();
    if(type==QMetaType_QVariantList || type==QMetaType_QVariantMap || type==QMetaType_QVariantHash || type==QMetaType_QStringList)
        return QJsonValue::fromVariant(v).toString().toUtf8();
    return v.toByteArray();

}

const QColor MUVariantUtil::toColor(const QVariant &v, const QColor&defaultValue)
{
    //TODO implement switch (typeId) {}
    if(v.canConvert(QVariant::Color))
        return v.toString();
    return defaultValue;
}

qlonglong MUVariantUtil::toInt(const QVariant &v, QVariant defaultValue)
{
    //TODO implement switch (typeId) {}
    if(v.canConvert(QMetaType_LongLong))
        return v.toLongLong();
    return defaultValue.toLongLong();
}

double MUVariantUtil::toDouble(const QVariant &v, QVariant defaultValue)
{
    //TODO implement switch (typeId) {}
    if(v.canConvert(QMetaType_Double))
        return v.toDouble();
    return defaultValue.toDouble();
}

const QVariant MUVariantUtil::convertVar(const QVariant &v, const QVariant::Type &type)
{
    //TODO implement switch (typeId) {}
    if(type==v.type())
        return v;
    else if(type==QMetaType_QVariantList       )
        return v.toList();
    else if(type==QMetaType_QVariantMap        )
        return v.toMap();
    else if(type==QMetaType_QVariantHash       )
        return v.toHash();
    else if(type==QMetaType_QStringList )
        return v.toStringList();
    else if(type==QMetaType_Int        )
        return v.toInt();
    else if(type==QVariant::UInt       )
        return v.toInt();
    else if(type==QMetaType_LongLong   )
        return v.toLongLong();
    else if(type==QVariant::ULongLong  )
        return v.toULongLong();
    else if(type==QMetaType_Double     )
        return v.toDouble();
    else if(type==QMetaType_QTime       )
        return v.toTime();
    else if(type==QMetaType_QDate       )
        return v.toDate();
    else if(type==QMetaType_QDateTime   )
        return v.toDateTime();
    else if(type==QMetaType_QString     )
        return v.toString();
    else if(type==QMetaType_QByteArray  )
        return v.toByteArray();
    else if(type==QMetaType_QChar       )
        return v.toChar();
    else if(type==QMetaType_QBitArray   )
        return v.toBitArray();
    else if(type==QMetaType_Bool       )
        return v.toBool();
    else if(type==QMetaType_QUuid       )
        return v.toUuid();
    else if(type==QMetaType_QUrl        )
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
    auto l = v.toString().toLower().trimmed().replace(qsl("text."), QString()).replace(qsl(" "), QString()).split('|');
    const auto&hash=*toAlignmentHash;
    QHashIterator<QString, Qt::Alignment> i(hash);
    while (i.hasNext()) {
        i.next();
        if(!l.contains(i.key()))
            continue;
        alignment = alignment | i.value();
    }
    return QVariant(alignment);
}

int MUVariantUtil::toVariantType(const QVariant &v)
{
    const auto&hash=*addVariantTypeHash;
    auto s = v.toString().trimmed().toLower();
    auto type = hash.contains(s) ? hash.value(s) : QVariant::Invalid;
    return type;
}

const QByteArray MUVariantUtil::toVariantTypeName(int v)
{
    return QMetaType::typeName(v);
}

bool MUVariantUtil::isEqual(const QVariant &v1, const QVariant &v2)
{
    auto s1=toStr(v1,QString());
    auto s2=toStr(v2,QString());
    if(s1==s2)
        return true;
    return false;
}

bool MUVariantUtil::isDiff(const QVariant &v1, const QVariant &v2)
{
    return !isEqual(v1,v2);
}


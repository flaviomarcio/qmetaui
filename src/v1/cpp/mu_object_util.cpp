#include "./mu_object_util.h"
#include <QRandomGenerator>

MUObjectUtil::MUObjectUtil(QObject *parent) : QObject(parent)
{

}

MUObjectUtil::~MUObjectUtil()
{

}

MUObjectUtil &MUObjectUtil::i()
{
    static MUObjectUtil __i;
    return __i;
}

bool MUObjectUtil::isDebug()
{
#if  defined(QT_DEBUG) && (!defined(Q_OS_ANDROID) && !defined(Q_OS_IOS))
    return true;
#else
    return false;
#endif
}

bool MUObjectUtil::isIOS()
{
#if !defined(Q_OS_IOS)
    return false;
#endif
    return true;
}

bool MUObjectUtil::isAndroid()
{
#if !defined(Q_OS_ANDROID)
    return false;
#endif
    return true;
}

bool MUObjectUtil::isDesktop()
{

#if defined(Q_OS_IOS) || defined(Q_OS_ANDROID)
    return false;
#endif
    return true;
}

const QVariant MUObjectUtil::ifThen(const QVariant &vThen, const QVariant &vElse)
{
    auto&v=vThen;

    if(v.canConvert(QMetaType::QObjectStar)){
        if(v.value<QQuickItem*>()!=nullptr)
            return vThen;
    }

    if(
            v.canConvert(QMetaType::QJsonObject) || v.canConvert(QMetaType::QJsonArray) || v.canConvert(QMetaType::QJsonValue)
        ||
            v.canConvert(QVariant::Map) || v.canConvert(QVariant::List) || v.canConvert(QVariant::Hash) || v.canConvert(QVariant::StringList)
        ||
            v.canConvert(QVariant::Uuid) || v.canConvert(QVariant::Url)
        ||
            v.canConvert(QVariant::LongLong) || v.canConvert(QVariant::Int) || v.canConvert(QVariant::Double)
        ||
            v.canConvert(QVariant::DateTime) || v.canConvert(QVariant::Date) || v.canConvert(QVariant::Time)
        ||
            v.canConvert(QVariant::ByteArray) || v.canConvert(QVariant::String) || v.canConvert(QVariant::Char) || v.canConvert(QVariant::BitArray)
        ||
            v.canConvert(QVariant::Bool)
        )
        return vThen;
    else if(v.canConvert(QMetaType::QObjectStar) && v.value<QObject*>()!=nullptr)
        return vThen;
    else
        return vElse;
}

bool MUObjectUtil::isDefined(const QVariant &v)
{
    if(v.canConvert(QMetaType::QObjectStar)){
        if(v.value<QQuickItem*>()!=nullptr)
            return true;

        if(v.value<QObject*>()!=nullptr)
            return true;
    }

    if(v.canConvert(QVariant::Map) || v.canConvert(QVariant::List) || v.canConvert(QVariant::Hash))
        return true;


    if(v.canConvert(QVariant::Uuid) || v.canConvert(QVariant::Url))
        return true;

    if(v.canConvert(QVariant::ByteArray) || v.canConvert(QVariant::String) || v.canConvert(QVariant::Char) || v.canConvert(QVariant::BitArray)){
        auto s = v.toString().trimmed();
        return (s!=QStringLiteral("null")) && (s!=QStringLiteral("undefined")) && (!s.isEmpty());
    }

    if(v.canConvert(QVariant::LongLong) || v.canConvert(QVariant::Int) || v.canConvert(QVariant::Double))
        return true;

    if(v.canConvert(QVariant::DateTime) || v.canConvert(QVariant::Date) || v.canConvert(QVariant::Time))
        return true;

    if(v.canConvert(QVariant::Bool))
        return true;

    if(v.canConvert(QMetaType::QJsonObject) || v.canConvert(QMetaType::QJsonArray) || v.canConvert(QMetaType::QJsonValue))
        return true;


    return false;
}

bool MUObjectUtil::isUndefined(const QVariant &v)
{
    return !isDefined(v);
}

QString MUObjectUtil::makeObjectName(const QVariant &v)
{
    static int seedRandon=1;
    static const auto listChar=QStringList()<<QStringLiteral("(")<<QStringLiteral(")")<<QStringLiteral(".")<<QStringLiteral(" ")<<QStringLiteral("{")<<QStringLiteral("}")<<QStringLiteral("-");
    QString name=v.toString();
    if(name.contains(QStringLiteral("_QMLTYPE_")))
        name=name.split(QStringLiteral("_QMLTYPE_")).first().trimmed();

    if(name.isEmpty())
        name=QStringLiteral("obj");
    name+=QStringLiteral("_");
    {
        QRandomGenerator r;
        r.seed(++seedRandon);
        auto v=r.generate();
        name+=QString::number(v);
    }
    for(auto&v:listChar){
        name=name.replace(v,QStringLiteral("_"));
    }
    while(name.contains(QStringLiteral("__")))
        name=name.replace(QStringLiteral("__"),QStringLiteral("_"));
    return name;
}

QVariantMap MUObjectUtil::objectToMap(const QObject *object)
{
    return QVariant(objectToHash(object)).toMap();
}

bool MUObjectUtil::objectFromMap(QObject *object, const QVariant &v)
{
    return objectFromHash(object, v);

}

QVariantHash MUObjectUtil::objectToHash(const QObject *object)
{
    if(object==nullptr)
        return {};
    QVariantHash __return;
    auto&metaObject = *object->metaObject();
    for(int col = 0; col < metaObject.methodCount(); ++col) {
        auto property = metaObject.property(col);
        if(property.name()==QByteArrayLiteral("objectName"))
            continue;

        if(property.name()==QByteArrayLiteral("0"))
            continue;

        auto k=property.name();
        auto v=property.read(object);
        int typeId=property.type();
        switch (typeId) {
        case QMetaType::QDate:
            v=v.toDate().toString(Qt::ISODate);
            break;
        case QMetaType::QDateTime:
            v=v.toDateTime().toString(Qt::ISODateWithMs);
            break;
        case QVariant::Time:
            v=v.toTime().toString(Qt::ISODateWithMs);
            break;
        default:
            break;
        }

        __return.insert(k, v);
    }
    return __return;
}

bool MUObjectUtil::objectFromHash(QObject *object, const QVariant &v)
{
    if(object==nullptr)
        return false;

    int typeId=v.type();
    switch (typeId) {
    case QMetaType::QVariantMap:
    case QMetaType::QVariantHash:
    {
        bool __return=false;
        auto map=v.toMap();
        auto&metaObject = *object->metaObject();
        for(int col = 0; col < metaObject.methodCount(); ++col) {
            auto property = metaObject.property(col);
            if(property.write(object, map.value(property.name())))
                __return=true;
        }
        return __return;
    }
    default:
        return false;
    }
}

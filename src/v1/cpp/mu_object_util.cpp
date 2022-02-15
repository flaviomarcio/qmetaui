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
    switch (qTypeId(v)) {
    case QMetaType_QObjectStar:
    {
        if(v.value<QObject*>()!=nullptr)
            return vThen;
        break;
    }
    case QMetaType_QJsonObject:
    case QMetaType_QJsonArray:
    case QMetaType_QJsonValue:
    case QMetaType_QVariantMap:
    case QMetaType_QVariantList:
    case QMetaType_QVariantHash:
    case QMetaType_QStringList:
    case QMetaType_QUuid:
    case QMetaType_QUrl:
    case QMetaType_LongLong:
    case QMetaType_Int:
    case QMetaType_Double:
    case QMetaType_QDateTime:
    case QMetaType_QDate:
    case QMetaType_QTime:
    case QMetaType_QByteArray:
    case QMetaType_QString:
    case QMetaType_QChar:
    case QMetaType_QBitArray:
    case QMetaType_Bool:
        return vThen;
    default:
        break;
    }
    return vElse;
}

bool MUObjectUtil::isDefined(const QVariant &v)
{
    switch (qTypeId(v)) {
    case QMetaType_QObjectStar:
    {
        if(v.value<QObject*>()!=nullptr)
            return true;

        return false;
    }
    case QMetaType_QVariantHash:
    case QMetaType_QVariantMap:
    case QMetaType_QVariantList:
    case QMetaType_QStringList:
        return true;
    case QMetaType_QUuid:
    case QMetaType_QUrl:
        return true;
    case QMetaType_QByteArray:
    case QMetaType_QString:
    case QMetaType_QChar:
    case QMetaType_QBitArray:
    {
        auto s = v.toString().trimmed();
        return (s!=qsl("null")) && (s!=qsl("undefined")) && (!s.isEmpty());
    }
    case QMetaType_Double:
    case QMetaType_LongLong:
    case QMetaType_Int:
    case QMetaType_UInt:
    case QMetaType_ULongLong:
        return true;

    case QMetaType_QDateTime:
    case QMetaType_QDate:
    case QMetaType_QTime:
        return true;

    case QMetaType_Bool:
        return true;

    case QMetaType_QJsonObject:
    case QMetaType_QJsonArray:
    case QMetaType_QJsonValue:
        return true;
    default:
        return false;
    }
}

bool MUObjectUtil::isUndefined(const QVariant &v)
{
    return !isDefined(v);
}

QString MUObjectUtil::makeObjectName(const QVariant &v)
{
    static int seedRandon=1;
    static const auto listChar=QStringList()<<qsl("(")<<qsl(")")<<qsl(".")<<qsl(" ")<<qsl("{")<<qsl("}")<<qsl("-");
    QString name=v.toString();
    if(name.contains(qsl("_QMLTYPE_")))
        name=name.split(qsl("_QMLTYPE_")).first().trimmed();

    if(name.isEmpty())
        name=qsl("obj");
    name+=qsl("_");
    {
        QRandomGenerator r;
        r.seed(++seedRandon);
        auto v=r.generate();
        name+=QString::number(v);
    }
    for(auto&v:listChar){
        name=name.replace(v,qsl("_"));
    }
    while(name.contains(qsl("__")))
        name=name.replace(qsl("__"),qsl("_"));
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
        if(property.name()==qbl("objectName"))
            continue;

        if(property.name()==qbl("0"))
            continue;

        auto k=property.name();
        auto v=property.read(object);
        int typeId=property.type();
        switch (typeId) {
        case QMetaType_QDate:
            v=v.toDate().toString(Qt::ISODate);
            break;
        case QMetaType_QDateTime:
            v=v.toDateTime().toString(Qt::ISODateWithMs);
            break;
        case QMetaType_QTime:
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
    case QMetaType_QVariantMap:
    case QMetaType_QVariantHash:
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

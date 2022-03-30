#include "./mu_generic_control.h"

#include <QMutex>

uint qHash( const QVariant & var )
{
    if ( !var.isValid() || var.isNull() )
        //return -1;
        Q_ASSERT(0);

    switch ( var.type() )
    {
        case QVariant::Int:
                return qHash( var.toInt() );
            break;
        case QVariant::UInt:
                return qHash( var.toUInt() );
            break;
        case QVariant::Bool:
                return qHash( var.toUInt() );
            break;
        case QVariant::Double:
                return qHash( var.toUInt() );
            break;
        case QVariant::LongLong:
                return qHash( var.toLongLong() );
            break;
        case QVariant::ULongLong:
                return qHash( var.toULongLong() );
            break;
        case QVariant::String:
                return qHash( var.toString() );
            break;
        case QVariant::Char:
                return qHash( var.toChar() );
            break;
        case QVariant::StringList:
                return qHash( var.toString() );
            break;
        case QVariant::ByteArray:
                return qHash( var.toByteArray() );
            break;
        case QVariant::Date:
        case QVariant::Time:
        case QVariant::DateTime:
        case QVariant::Url:
        case QVariant::Locale:
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        case QVariant::RegularExpression:
#else
        case QVariant::RegExp:
#endif
                return qHash( var.toString() );
            break;
        case QVariant::Map:
        case QVariant::List:
        case QVariant::BitArray:
        case QVariant::Size:
        case QVariant::SizeF:
        case QVariant::Rect:
        case QVariant::LineF:
        case QVariant::Line:
        case QVariant::RectF:
        case QVariant::Point:
        case QVariant::PointF:
            // not supported yet
            break;
        case QVariant::UserType:
        case QVariant::Invalid:
        default:
            return -1;
    }

    // could not generate a hash for the given variant
    return -1;
}

MUGenericControl::MUGenericControl(QObject *parent) : QObject{parent}
{
}

MUGenericControl::~MUGenericControl()
{

}

void MUGenericControl::addOrReplace(const QVariant & key, const QVariant & value)
{
    QMutexLocker locker(&mutex);
    p.insert(key, value);
    emit dataChanged();
}


bool MUGenericControl::add(const QVariant & key, const QVariant & value)
{
    QMutexLocker locker(&mutex);
    if (!p.contains(key)){
        p.insert(key, value);
        emit dataChanged();
        return true;
    }
    return false;
}

bool MUGenericControl::replace(const QVariant & key, const QVariant & value)
{
    QMutexLocker locker(&mutex);
    if (p.contains(key)){
        p.insert(key, value);
        emit dataChanged();
        return true;
    }
    return false;
}

QVariant MUGenericControl::take(const QVariant & key)
{
    QMutexLocker locker(&mutex);
    if (p.contains(key)){
        emit dataChanged();
        return p.take(key);
    }
    return QVariant();
}

bool MUGenericControl::contains(const QVariant & key)
{
    QMutexLocker locker(&mutex);
    return p.contains(key);
}

bool MUGenericControl::remove(const QVariant & key)
{
    QMutexLocker locker(&mutex);
    if (p.contains(key)){
        p.remove(key);
        emit dataChanged();
        return true;
    }
    return false;

}

QVariantMap MUGenericControl::takeFist()
{
    QMutexLocker locker(&mutex);
    QVariantMap retorno;
    if (!p.isEmpty()){
        QHash<QVariant, QVariant>::const_iterator it = p.constBegin();
        auto key = it.key();
        auto value = p.take(key);
        retorno["key"] = key;
        retorno["value"] = value;
        emit dataChanged();
    }
    return retorno;
}

QVariantList MUGenericControl::values()
{
    return p.values();
}

bool MUGenericControl::isEmpty()
{    
    return p.isEmpty();
}

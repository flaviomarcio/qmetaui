#include "./mu_generic_control.h"
#include <QMutex>
#include <QStm>

uint qHash( const QVariant & var )
{
    if ( !var.isValid() || var.isNull() )
        //return -1;
        Q_ASSERT(0);

    switch ( qTypeId(var) )
    {
    case QMetaType_Int:
        return qHash( var.toInt() );
        break;
    case QMetaType_UInt:
        return qHash( var.toUInt() );
    case QMetaType_Bool:
        return qHash( var.toUInt() );
    case QMetaType_Double:
        return qHash( var.toUInt() );
    case QMetaType_LongLong:
        return qHash( var.toLongLong() );
    case QMetaType_ULongLong:
        return qHash( var.toULongLong() );
    case QMetaType_QString:
        return qHash( var.toString() );
    case QMetaType_QChar:
        return qHash( var.toChar() );
    case QMetaType_QStringList:
        return qHash( var.toString() );
    case QMetaType_QByteArray:
        return qHash( var.toByteArray() );
    case QMetaType_QDate:
        return qHash( var.toDate().toString() );
    case QMetaType_QTime:
        return qHash( var.toTime().toString() );
    case QMetaType_QDateTime:
        return qHash( var.toDateTime().toString() );
    case QMetaType_QUrl:
        return qHash( var.toUrl().toString() );
    case QMetaType_QUuid:
        return qHash( var.toUuid().toString() );
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
        retorno[qsl("key")] = key;
        retorno[qsl("value")] = value;
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

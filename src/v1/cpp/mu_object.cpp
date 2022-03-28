#include "./mu_object.h"
#include "./mu_object_util.h"
#include <QJsonDocument>

MUObject::MUObject(QObject *parent) : QObject{parent}
{

}

QVariantHash MUObject::toHash() const
{
    MUObjectUtil util;
    return util.objectToHash(this);
}

QByteArray MUObject::toJson() const
{
    return QJsonDocument::fromVariant(this->toHash()).toJson(QJsonDocument::Compact);
}

bool MUObject::fromMap(const QVariantMap&v)
{
    MUObjectUtil util;
    return util.objectFromMap(this, v);
}

bool MUObject::fromHash(const QVariantHash &v)
{
    MUObjectUtil util;
    return util.objectFromHash(this, v);
}

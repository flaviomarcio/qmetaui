#include "./mu_validation_util.h"
#include "./mu_object_util.h"
#include <QStm>


MUValidationUtil::MUValidationUtil(QObject *parent):MUObject(parent)
{

}

MUValidationUtil::~MUValidationUtil()
{

}

MUValidationUtil &MUValidationUtil::i()
{
    static MUValidationUtil __i;
    return __i;
}

bool MUValidationUtil::isDebug()
{
    return MUObjectUtil::isDebug();
}

const QVariant MUValidationUtil::ifThen(const QVariant &vThen, const QVariant &vElse)
{
    return MUObjectUtil::ifThen(vThen, vElse);
}

bool MUValidationUtil::isDefined(const QVariant &v)
{
    return MUObjectUtil::isDefined(v);
}

bool MUValidationUtil::isUndefined(const QVariant &v)
{
    return MUObjectUtil::isUndefined(v);
}

bool MUValidationUtil::isEmpty(const QVariant &v)
{
    switch (qTypeId(v)){
    case QMetaType_QString:
    case QMetaType_QChar:
    case QMetaType_QByteArray:
        return v.toString().trimmed().isEmpty();
    default:
        return true;
    }
}

QVariant MUValidationUtil::isEmptySet(const QVariant &vThen, const QVariant &vElse)
{
    return isEmpty(vThen)?vElse:vThen;
}

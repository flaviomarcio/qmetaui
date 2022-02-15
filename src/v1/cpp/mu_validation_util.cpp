#include "./mu_validation_util.h"
#include "./mu_object_util.h"


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
    if(v.canConvert(QMetaType_QString) || v.canConvert(QMetaType_QChar) || v.canConvert(QMetaType_QByteArray))
        return v.toString().trimmed().isEmpty();
    return true;
}

QVariant MUValidationUtil::isEmptySet(const QVariant &vThen, const QVariant &vElse)
{
    return isEmpty(vThen)?vElse:vThen;
}

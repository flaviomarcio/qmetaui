#include "./mu_validation_util_public.h"
#include "./mu_string_util.h"

Q_GLOBAL_STATIC(MUValidationUtilPublic, muValidationUtilPublic)


MUValidationUtilPublic::MUValidationUtilPublic(QObject *parent):QObject(parent)
{

}

MUValidationUtilPublic::~MUValidationUtilPublic()
{

}

bool MUValidationUtilPublic::isEmail(const QVariant &v)
{
    if(!v.toString().contains(qsl("@")))
        return false;

    if(!v.toString().contains(qsl(".")))
        return false;

    if(v.toString().length()<=4)
        return false;

    if(v.toString().split(qsl("@")).size()!=2)
        return false;

    return true;
}

bool MUValidationUtilPublic::isPhoneNumber(const QVariant &v)
{
    auto&stringUtil=MUStringUtil::i();
    auto phone=QString::number(stringUtil.toStrPhone(v.toString()).toLongLong());
    switch (phone.length()) {
    case 9://9 9876 5432
        return true;
    case 10://99 9876 5432
        return true;
    case 11://99 9 9876 5432
        return true;
    case 14://99 9 9876 5432
        return true;
    default:
        return false;
    }
}

MUValidationUtilPublic &MUValidationUtilPublic::i()
{
    return*muValidationUtilPublic;
}

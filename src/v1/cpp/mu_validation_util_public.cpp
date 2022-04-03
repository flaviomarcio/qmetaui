#include "./mu_validation_util_public.h"
#include "./mu_string_util.h"


MUValidationUtilPublic::MUValidationUtilPublic(QObject *parent):QObject{parent}
{

}

MUValidationUtilPublic::~MUValidationUtilPublic()
{

}

bool MUValidationUtilPublic::isEmail(const QVariant &v)
{
    if(!v.toString().contains("@"))
        return false;
    else if(!v.toString().contains("."))
        return false;
    else if(v.toString().length()<=4)
        return false;
    else if(v.toString().split("@").size()!=2)
        return false;
    else
        return true;
}

bool MUValidationUtilPublic::isPhoneNumber(const QVariant &v)
{
    auto&stringUtil=MUStringUtil::i();
    auto phone=QString::number(stringUtil.toStrPhone(v.toString()).toLongLong());
    if(phone.length()==9)//9 9876 5432
        return true;
    else if(phone.length()==10)//99 9876 5432
        return true;
    else if(phone.length()==11)//99 9 9876 5432
        return true;
    else if(phone.length()==14)//99 9 9876 5432
        return true;
    else
        return false;
}

MUValidationUtilPublic &MUValidationUtilPublic::i()
{
    static MUValidationUtilPublic __i;
    return __i;
}

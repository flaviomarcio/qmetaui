#include "./mu_validation_util_ptb.h"
#include "./mu_string_util.h"

MUValidationUtilPTB::MUValidationUtilPTB(QObject *parent):MUValidationUtilPublic(parent)
{

}

MUValidationUtilPTB::~MUValidationUtilPTB()
{

}

MUValidationUtilPTB &MUValidationUtilPTB::i()
{
    static MUValidationUtilPTB __i;
    return __i;
}

bool MUValidationUtilPTB::isName(const QVariant &v)
{
    auto&u=MUStringUtil::i();
    if(u.isEmpty(v))
        return false;

    if(v.toString().split(' ').count()<=1)
        return false;

    return true;
}

bool MUValidationUtilPTB::isRG(const QVariant &v)
{
    auto&u=MUStringUtil::i();
    if(u.isEmpty(v))
        return false;

    return true;
}

bool MUValidationUtilPTB::isCPF(const QVariant &v)
{    
    auto&u=MUStringUtil::i();
    QString vStr=u.toStrNumber(v).rightJustified(11,'0');
    if(u.isEmpty(v))
        return false;

    if (vStr.length() != 11)
        return false;

    if (vStr.toLongLong()<=0)
        return false;

    static auto vList=QStringList() <<qsl("00000000000")
                                      <<qsl("11111111111")
                                      <<qsl("22222222222")
                                      <<qsl("33333333333")
                                      <<qsl("44444444444")
                                      <<qsl("55555555555")
                                      <<qsl("66666666666")
                                      <<qsl("77777777777")
                                      <<qsl("88888888888")
                                      <<qsl("99999999999");
    if (vList.contains(vStr))
        return false;

    int ver1 = 0, ver2 = 0;
    for(int j=0; j<9; j++) ver1 += (vStr[j].digitValue() * (10  -j));
    ver1%= 11;
    ver1=(ver1<2)?0:(11-ver1);
    if (vStr[9].digitValue() == ver1){
        for (int j=0; j<10; j++) ver2 += (vStr[j].digitValue() * (11-j));
        ver2%= 11;
        ver2=(ver2<2)?0:(11-ver2);
        return (vStr[10].digitValue() == ver2);
    }
    return false;
}

bool MUValidationUtilPTB::isCNPJ(const QVariant &v)
{
    auto&u=MUStringUtil::i();
    auto vStr=u.toStrNumber(v).rightJustified(14,'0');
    if(u.isEmpty(v))
        return false;

    if (vStr.length() != 14)
        return false;

    if (vStr.toLongLong()<=0)
        return false;

    static auto vList=QStringList()
                        <<qsl("00000000000000")
                        <<qsl("11111111111111")
                        <<qsl("22222222222222")
                        <<qsl("33333333333333")
                        <<qsl("44444444444444")
                        <<qsl("55555555555555")
                        <<qsl("66666666666666")
                        <<qsl("77777777777777")
                        <<qsl("88888888888888")
                        <<qsl("99999999999999");

    // Elimina CNPJs invalidos conhecidos
    if (vList.contains(vStr))
        return false;

    // Valida DVs
    int tamanho = vStr.length() - 2;
    auto numeros = vStr.mid(0,tamanho);
    auto digitos = vStr.mid(tamanho);
    int soma = 0;
    int pos = tamanho - 7;
    for (int i = tamanho; i >= 1; i--) {
        soma += QString(numeros[tamanho - i]).toInt() * pos--;
        if (pos < 2)
            pos = 9;
    }
    auto resultado = soma % 11 < 2 ? 0 : 11 - soma % 11;
    if (resultado != QString(digitos[0]).toInt())
        return false;

    tamanho = tamanho + 1;
    numeros = vStr.mid(0,tamanho);
    soma = 0;
    pos = tamanho - 7;
    for (int i = tamanho; i >= 1; i--) {
        soma += QString(numeros[tamanho - i]).toInt() * pos--;
        if (pos < 2)
            pos = 9;
    }
    resultado = soma % 11 < 2 ? 0 : 11 - soma % 11;
    if (resultado != QString(digitos[1]).toInt())
        return false;

    return true;
}

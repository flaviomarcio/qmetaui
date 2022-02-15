#pragma once

#include "./mu_global.h"
#include "./mu_validation_util_public.h"

#define V_MUValidationUtilPTB()\
    auto&u=MUValidationUtilPTB::i();

#define MU_DECLARE_MUValidationUtilPTB()\
public:\
    static MUValidationUtilPTB&u(){\
        return MUValidationUtilPTB::i();\
    }

class Q_MU_EXPORT MUValidationUtilPTB : public MUValidationUtilPublic
{
    Q_OBJECT
    QML_ELEMENT
public:
    Q_INVOKABLE explicit MUValidationUtilPTB(QObject *parent = nullptr);
    ~MUValidationUtilPTB();

    static MUValidationUtilPTB &i();

    Q_INVOKABLE static bool isRG  (const QVariant&v);
    Q_INVOKABLE static bool isCPF (const QVariant&v);
    Q_INVOKABLE static bool isCNPJ(const QVariant&v);
    Q_INVOKABLE static bool isName(const QVariant&v);
};

//Q_DECLARE_METATYPE(MUValidationUtilPTB)

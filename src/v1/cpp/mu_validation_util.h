#ifndef MUValidationUtil_H
#define MUValidationUtil_H

#include "./mu_global.h"
#include "./mu_object.h"
#include "./mu_validation_util_public.h"
#include "./mu_validation_util_ptb.h"

#define V_MUValidationUtil()\
    auto&u=MUValidationUtil::i();

#define MU_DECLARE_MUValidationUtil()\
public:\
    static MUValidationUtil&u(){\
        return MUValidationUtil::i();\
    }

class Q_MU_EXPORT MUValidationUtil : public MUObject
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit MUValidationUtil(QObject *parent = nullptr);
    ~MUValidationUtil();

    Q_PROPERTY(MUValidationUtilPublic*pub MEMBER pub NOTIFY change)
    Q_PROPERTY(MUValidationUtilPTB*ptb MEMBER ptb NOTIFY change)

    static MUValidationUtil &i();

    Q_INVOKABLE static bool isDebug();
    Q_INVOKABLE static const QVariant ifThen(const QVariant &vThen, const QVariant &vElse);
    Q_INVOKABLE static bool isDefined(const QVariant &v);
    Q_INVOKABLE static bool isUndefined(const QVariant &v);
    Q_INVOKABLE static bool isEmpty(const QVariant &v);
    Q_INVOKABLE static QVariant isEmptySet(const QVariant &vThen, const QVariant &vElse);


private:
    MUValidationUtilPublic*pub=&MUValidationUtilPublic::i();
    MUValidationUtilPTB*ptb=&MUValidationUtilPTB::i();
signals:
    void change();
};

//Q_DECLARE_METATYPE(MUValidationUtil)

#endif // MUValidationUtil_H

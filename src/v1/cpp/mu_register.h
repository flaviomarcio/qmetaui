#pragma once

#include "./mu_global.h"
#include <QObject>
#include <QQmlApplicationEngine>

#define MU_DECLARE_CLASS(packegeName,className)\
    qmlRegisterType<className>(packegeName, 1, 0, #className);\
    qmlRegisterType<className>(packegeName, 0, 0, #className)

#define MU_DECLARE_ENUM(packegeName, enumClass, enumName)\
    qRegisterMetaType<enumName>(#enumName);\
    qmlRegisterUncreatableType<enumClass>(packegeName, 0, 0, #enumName, "Not creatable as it is an enum type");\
    qmlRegisterUncreatableType<enumClass>(packegeName, 1, 0, #enumName, "Not creatable as it is an enum type")

#define MU_DECLARE_ENUM_META_CONTROL(enumClass, enumName)\
    MU_DECLARE_ENUM("QtReforce.Meta.Controls", enumClass, enumName);

#define MU_DECLARE_ENUM_META_SECURITY(enumClass, enumName)\
    MU_DECLARE_ENUM("QtReforce.Meta.Security", enumClass, enumName);

#define MU_DECLARE_ENUM_META_NETWORK(enumClass, enumName)\
    MU_DECLARE_ENUM("QtReforce.Meta.Network", enumClass, enumName);

#define MU_DECLARE_CLASS_META_CONTROL(className)\
    MU_DECLARE_CLASS("QtReforce.Meta.Controls", className);

#define MU_DECLARE_CLASS_META_SECURITY(className)\
    MU_DECLARE_CLASS("QtReforce.Meta.Security", className);\

#define MU_DECLARE_CLASS_META_NETWORK(className)\
    MU_DECLARE_CLASS("QtReforce.Meta.Network", className);

#define MU_DECLARE_CLASS_META_UTILS(className)\
    MU_DECLARE_CLASS("QtReforce.Meta.Utils", className);

#define MU_DECLARE_INSTANCE(NAME, INSTANCE)\
    engine.rootContext()->setContextProperty(NAME, INSTANCE);

class Q_MU_EXPORT MURegister{
    Q_GADGET
public:
    static void init(QQmlApplicationEngine &engine);

    explicit MURegister(){
    }
};

class Q_MU_EXPORT MUEnumUtils{
    Q_GADGET
public:
    static void init(QQmlApplicationEngine &engine);
//private:
    explicit MUEnumUtils(){}
};

class Q_MU_EXPORT MUEnumExtras{
    Q_GADGET
public:
    static void init(QQmlApplicationEngine &engine);
//private:
    explicit MUEnumExtras(){}
};


class Q_MU_EXPORT MUEnumNotification{
    Q_GADGET
public:
    enum Type {
          nt_Unknow     = -1
        , nt_Normal     = 1
        , nt_Error      = 2
        , nt_Fail       = 3
        , nt_Network    = 4
        , nt_Security   = 5
        , nt_Max        = 255
    };

    enum Network {
          nsn_Unknow = nt_Unknow
        , nsn_Normal = nt_Normal
        , nsn_Error = nt_Error
        , nsn_Fail = nt_Fail
        , nsn_ServerOnLine=nt_Max+1
        , nsn_ServerOffLine=nt_Max+2
        , nsn_OnLine=nt_Max+3
        , nsn_OffLine=nt_Max+4
    };


    enum Security {
          nse_Unknow = nt_Unknow
        , nse_Normal = nt_Normal
        , nse_Security = nt_Security
        , nse_Error = nt_Error
        , nse_Fail = nt_Fail
        , nse_LoginSuccessful = nt_Max+1
        , nse_LoginUnSuccessful = nt_Max+2
        , nse_SessionConnected = nt_Max+3
        , nse_SessionDisconnected = nt_Max+4
        , nse_SessionUnauthorized = nt_Max+5
    };

    Q_ENUM(Type)
    Q_ENUM(Security)

    static void init(QQmlApplicationEngine &engine);
//private:
    explicit MUEnumNotification(){}
};

typedef MUEnumNotification::Type MUNotificationType;
typedef MUEnumNotification::Security MUNotificationEspecificationSecurity;
typedef MUEnumNotification::Network MUNotificationEspecificationNetwork;


class Q_MU_EXPORT MUEnumFormType{
    Q_GADGET
public:
    enum Type {
         Home                 = 0
        ,Start                = 1
        ,Register             = 2
        ,LoginEmail           = 3
        ,LoginSmartPhone      = 4
        ,LoginDocument        = 5
        ,LoginUserName        = 6
        ,LoginEmailSmartPhone = 7
    };

    Q_ENUM(Type)

    static void init(QQmlApplicationEngine &engine);
//private:
    explicit MUEnumFormType(){}
};

typedef MUEnumFormType::Type MUFormType;


class Q_MU_EXPORT MUEnumRequest{
    Q_GADGET
public:

    enum AppType{
         atJson=0
        ,atCBor=1
        ,atXml=2
        ,atBinary=3
    };

    Q_ENUM(AppType)

    enum Method{
          rmHead
        , rmOptions
        , rmGet
        , rmPost
        , rmPut
        , rmDelete
        , rmPatch
        , rmTrace
    };

    Q_ENUM(Method)

    static const QHash<int,QString> ___MethodName(){
        QHash<int, QString> r;
        r.insert(rmHead,"Head");
        r.insert(rmHead,"head");

        r.insert(rmGet,"Get");
        r.insert(rmGet,"get");

        r.insert(rmPost,"Post");
        r.insert(rmPost,"post");

        r.insert(rmPut,"Put");
        r.insert(rmPut,"put");

        r.insert(rmDelete,"Delete");
        r.insert(rmDelete,"delete");

        r.insert(rmPatch,"Patch");
        r.insert(rmPatch,"patch");

        r.insert(rmTrace,"Trace");
        r.insert(rmTrace,"trace");

        return r;
    }

    enum Mode{
        mdSync=0, mdASync=1
    };
    Q_ENUM(Mode)

    explicit MUEnumRequest(){}

    static void init(QQmlApplicationEngine &engine);
};

static const auto MUEnumRequestMethodName=MUEnumRequest::___MethodName();

class Q_MU_EXPORT MUEnumRequestType:public MUEnumRequest{
    Q_GADGET
public:
    explicit MUEnumRequestType(){}
};


class Q_MU_EXPORT MUEnumRequestMethod:public MUEnumRequest{
    Q_GADGET
public:
    explicit MUEnumRequestMethod(){}
};


class Q_MU_EXPORT MUEnumRequestMode:public MUEnumRequest{
    Q_GADGET
public:
    explicit MUEnumRequestMode(){}
};

typedef MUEnumRequestType::AppType MURequestAppType;
typedef MUEnumRequestMethod::Method MURequestMethod;
typedef MUEnumRequestMode::Mode MURequestMode;


class Q_MU_EXPORT MUEnumPaintSettings{
    Q_GADGET
public:
    static void init(QQmlApplicationEngine &engine);

    explicit MUEnumPaintSettings(){};
};


class Q_MU_EXPORT MUEnumInstance{
    Q_GADGET
public:
    static void init(QQmlApplicationEngine &engine);

    explicit MUEnumInstance(){}
};

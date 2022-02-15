#pragma once

#define MU_DECLARE_ENUM_META_CONTROL(enumClass, enumName)\
qRegisterMetaType<enumName>(#enumName);\
    qmlRegisterUncreatableType<enumClass>("QtReforce.Meta.Controls", 0, 0, #enumName, "Not creatable as it is an enum type");\
    qmlRegisterUncreatableType<enumClass>("QtReforce.Meta.Controls", 1, 0, #enumName, "Not creatable as it is an enum type")

#define MU_DECLARE_ENUM_META_SECURITY(enumClass, enumName)\
    qRegisterMetaType<enumName>(#enumName);\
    qmlRegisterUncreatableType<enumClass>("QtReforce.Meta.Security", 0, 0, #enumName, "Not creatable as it is an enum type");\
    qmlRegisterUncreatableType<enumClass>("QtReforce.Meta.Security", 1, 0, #enumName, "Not creatable as it is an enum type")

#define MU_DECLARE_ENUM_META_NETWORK(enumClass, enumName)\
    qRegisterMetaType<enumName>(#enumName);\
    qmlRegisterUncreatableType<enumClass>("QtReforce.Meta.Network", 0, 0, #enumName, "Not creatable as it is an enum type");\
    qmlRegisterUncreatableType<enumClass>("QtReforce.Meta.Network", 1, 0, #enumName, "Not creatable as it is an enum type")

#define MU_DECLARE_CLASS_META_CONTROL(className)\
    qmlRegisterType<className>("QtReforce.Meta.Controls", 1, 0, #className);\
    qmlRegisterType<className>("QtReforce.Meta.Controls", 0, 0, #className)\

#define MU_DECLARE_CLASS_META_SECURITY(className)\
    qmlRegisterType<className>("QtReforce.Meta.Security", 1, 0, #className);\
    qmlRegisterType<className>("QtReforce.Meta.Security", 0, 0, #className)\

#define MU_DECLARE_CLASS_META_NETWORK(className)\
    qmlRegisterType<className>("QtReforce.Meta.Network", 1, 0, #className);\
    qmlRegisterType<className>("QtReforce.Meta.Network", 0, 0, #className)\

#define MU_DECLARE_CLASS_META_FORMS(className)\
qmlRegisterType<className>("QtReforce.Meta.Forms", 1, 0, #className);\
    qmlRegisterType<className>("QtReforce.Meta.Forms", 0, 0, #className)\

#define MU_DECLARE_INSTANCE(className)\
    engine.rootContext()->setContextProperty("qApp",QGuiApplication::instance());

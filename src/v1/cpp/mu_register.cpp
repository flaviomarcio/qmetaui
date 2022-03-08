#include "./mu_register.h"
#include <QtQml>
#include <QAbstractListModel>

#include "./mu_global.h"
#include "./mu_application.h"
#include "./mu_notification.h"
#include "./mu_login_engine.h"

#include "./mu_app_session.h"
#include "./mu_app_info.h"
#include "./mu_app_repository.h"

#include "./mu_cache_util.h"
#include "./mu_date_util.h"
#include "./mu_generic_control.h"
#include "./mu_geometry_util.h"
#include "./mu_login_session.h"
#include "./mu_model_navigator.h"
#include "./mu_model_table.h"
#include "./mu_object_util.h"
#include "./mu_paint_setting.h"
#include "./mu_request.h"
#include "./mu_request_model.h"
#include "./mu_string_util.h"
#include "./mu_validation_util.h"
#include "./mu_variant_util.h"
#include "./mu_image_capture_area.h"

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

#define MU_DECLARE_INSTANCE(className)\
    engine.rootContext()->setContextProperty("qApp",QGuiApplication::instance());

void MURegister::init(QQmlApplicationEngine &engine)
{
    MUEnumFormType::init(engine);
    MUEnumNotification::init(engine);
    MUEnumRequestType::init(engine);
    MUEnumRequestMethod::init(engine);
    MUEnumRequestMode::init(engine);
    MUEnumPaintSettings::init(engine);
    MUEnumInstance::init(engine);
    MUCacheUtil::init();
    MUImageCaptureArea::init();
}

void MUEnumNotification::init(QQmlApplicationEngine &engine)
{
    Q_UNUSED(engine)
    MU_DECLARE_ENUM_META_CONTROL(MUEnumNotification, MUNotificationType);
    MU_DECLARE_ENUM_META_CONTROL(MUEnumNotification, MUNotificationEspecificationNetwork);
    MU_DECLARE_ENUM_META_CONTROL(MUEnumNotification, MUNotificationEspecificationSecurity);
}

void MUEnumFormType::init(QQmlApplicationEngine &engine)
{
    Q_UNUSED(engine)
    MU_DECLARE_ENUM_META_CONTROL(MUEnumFormType, MUFormType);

    MU_DECLARE_CLASS_META_CONTROL(MUApplication             );
    MU_DECLARE_CLASS_META_CONTROL(MUCacheUtil               );
    MU_DECLARE_CLASS_META_CONTROL(MUModelTable              );
    MU_DECLARE_CLASS_META_CONTROL(MUGenericControl          );
    MU_DECLARE_CLASS_META_CONTROL(MUImageCaptureArea        );

    MU_DECLARE_CLASS_META_SECURITY(MULoginEngine            );
    MU_DECLARE_CLASS_META_SECURITY(MULoginSession           );
    MU_DECLARE_CLASS_META_SECURITY(MULoginProfile           );

    MU_DECLARE_CLASS_META_SECURITY(MUAppSession             );
    MU_DECLARE_CLASS_META_SECURITY(MUAppInfo                );
    MU_DECLARE_CLASS_META_SECURITY(MUAppRepository          );

    MU_DECLARE_CLASS_META_SECURITY(MUValidationUtil         );
    MU_DECLARE_CLASS_META_SECURITY(MUValidationUtilPublic   );
    MU_DECLARE_CLASS_META_SECURITY(MUValidationUtilPTB      );
}

void MUEnumRequest::init(QQmlApplicationEngine &engine)
{
    Q_UNUSED(engine)

    MU_DECLARE_ENUM_META_NETWORK(MUEnumRequestType    , MURequestAppType );
    MU_DECLARE_ENUM_META_NETWORK(MUEnumRequestMethod  , MURequestMethod );
    MU_DECLARE_ENUM_META_NETWORK(MUEnumRequestMode    , MURequestMode );
    MU_DECLARE_CLASS_META_NETWORK(MURequest           );
    MU_DECLARE_CLASS_META_NETWORK(MURequestModel      );
    MU_DECLARE_CLASS_META_NETWORK(MUServerLink        );
    MU_DECLARE_CLASS_META_NETWORK(MUModelNavigator    );
}

void MUEnumPaintSettings::init(QQmlApplicationEngine &engine)
{
    Q_UNUSED(engine)
    MU_DECLARE_CLASS_META_CONTROL(MUPaintSetting         );
    MU_DECLARE_CLASS_META_CONTROL(MUPaintSettingItem     );
    MU_DECLARE_CLASS_META_CONTROL(MUPaintSettingState    );
    MU_DECLARE_CLASS_META_CONTROL(MUPaintSettingGeometry );
    MU_DECLARE_CLASS_META_CONTROL(MUPaintSettingDrawing  );
    MU_DECLARE_CLASS_META_CONTROL(MUPaintSetting         );

}


void MUEnumInstance::init(QQmlApplicationEngine &engine)
{
    Q_UNUSED(engine)

    MULoginSession::i().load();

    engine.rootContext()->setContextProperty("qApp",QGuiApplication::instance());
    engine.rootContext()->setContextProperty("muApp",&MUApplication::i());

    engine.rootContext()->setContextProperty("objectUtil",&MUObjectUtil::i());
    engine.rootContext()->setContextProperty("variantUtil",&MUVariantUtil::i());
    engine.rootContext()->setContextProperty("geometryUtil",&MUGeometryUtil::i());
    engine.rootContext()->setContextProperty("dateUtil",&MUDateUtil::i());
    engine.rootContext()->setContextProperty("cacheUtil",&MUCacheUtil::i());
    engine.rootContext()->setContextProperty("stringUtil",&MUStringUtil::i());
    engine.rootContext()->setContextProperty("validationUtil",&MUValidationUtil::i());

    engine.rootContext()->setContextProperty("loginSession",&MULoginSession::i());
    engine.rootContext()->setContextProperty("appSession",&MUAppSession::i());

    engine.rootContext()->setContextProperty("loginEngine",&MULoginEngine::i());
    engine.rootContext()->setContextProperty("paintSetting",&MUPaintSetting::i());

    engine.rootContext()->setContextProperty("notification",&MUNotification::i());
    //engine.rootContext()->setContextProperty("mainPaintSetting",&MUPaintSetting::instance());
}

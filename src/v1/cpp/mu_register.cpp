#include "./mu_register.h"
#include <QtQml>
#include <QAbstractListModel>
#include <QtReforce/QStatusBar>

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


void MURegister::init(QQmlApplicationEngine &engine)
{
    MUEnumUtils::init(engine);
    MUEnumFormType::init(engine);
    MUEnumNotification::init(engine);
    MUEnumRequestType::init(engine);
    MUEnumRequestMethod::init(engine);
    MUEnumRequestMode::init(engine);
    MUEnumPaintSettings::init(engine);
    MUEnumInstance::init(engine);
    MUCacheUtil::init();
    MUImageCaptureArea::init();
    MUEnumExtras::init(engine);
}

void MUEnumUtils::init(QQmlApplicationEngine &engine)
{
    Q_UNUSED(engine)
    MU_DECLARE_CLASS_META_UTILS(MUVariantUtil);
    MU_DECLARE_CLASS_META_UTILS(MUGeometryUtil);
    MU_DECLARE_CLASS_META_UTILS(MUDateUtil);
    MU_DECLARE_CLASS_META_UTILS(MUCacheUtil);
    MU_DECLARE_CLASS_META_UTILS(MUStringUtil);
    MU_DECLARE_CLASS_META_UTILS(MUNotification);
}

void MUEnumExtras::init(QQmlApplicationEngine &engine)
{
    Q_UNUSED(engine)
    MU_DECLARE_CLASS("StatusBar", StatusBar);
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
    MU_DECLARE_CLASS_META_CONTROL(MUModelTable              );
    MU_DECLARE_CLASS_META_CONTROL(MUGenericControl          );
    MU_DECLARE_CLASS_META_CONTROL(MUImageCaptureArea        );

    MU_DECLARE_CLASS_META_SECURITY(MULoginEngine            );
    MU_DECLARE_CLASS_META_SECURITY(MULoginEngineRoutes      );
    MU_DECLARE_CLASS_META_SECURITY(MULoginSession           );
    MU_DECLARE_CLASS_META_SECURITY(MULoginProfile           );

    MU_DECLARE_CLASS_META_SECURITY(MUAppSession             );
    MU_DECLARE_CLASS_META_SECURITY(MUAppInfo                );
    MU_DECLARE_CLASS_META_SECURITY(MUAppRepository          );

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

    MU_DECLARE_INSTANCE("qApp",QGuiApplication::instance());
    MU_DECLARE_INSTANCE("muApp",&MUApplication::i());
    MU_DECLARE_INSTANCE("objectUtil",&MUObjectUtil::i());
    MU_DECLARE_INSTANCE("variantUtil",&MUVariantUtil::i());
    MU_DECLARE_INSTANCE("geometryUtil",&MUGeometryUtil::i());
    MU_DECLARE_INSTANCE("dateUtil",&MUDateUtil::i());
    MU_DECLARE_INSTANCE("cacheUtil",&MUCacheUtil::i());
    MU_DECLARE_INSTANCE("stringUtil",&MUStringUtil::i());
    MU_DECLARE_INSTANCE("validationUtil",&MUValidationUtil::i());
    MU_DECLARE_INSTANCE("loginSession",&MULoginSession::i());
    MU_DECLARE_INSTANCE("appSession",&MUAppSession::i());
    MU_DECLARE_INSTANCE("loginEngine",&MULoginEngine::i());
    MU_DECLARE_INSTANCE("paintSetting",&MUPaintSetting::i());
    MU_DECLARE_INSTANCE("notification",&MUNotification::i());
}

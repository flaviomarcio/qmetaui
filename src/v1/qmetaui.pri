QT += core
QT += quickcontrols2
QT += gui
QT += xml
QT += qml
QT += quick
QT += svg
QT += network
QT += websockets
QT += positioning
QT += location

RESOURCES += \
    $$PWD/qml/controls/controls.qrc \
    $$PWD/qml/dynamic/dynamic.qrc \
    $$PWD/qml/forms/forms.qrc \
    $$PWD/qml/network/network.qrc

HEADERS += \
    $$PWD/cpp/mu_app_engine_routes.h \
    $$PWD/cpp/mu_app_info.h \
    $$PWD/cpp/mu_app_repository.h \
    $$PWD/cpp/mu_app_session.h \
    $$PWD/cpp/mu_application.h \
    $$PWD/cpp/mu_cache_util.h \
    $$PWD/cpp/mu_const.h \
    $$PWD/cpp/mu_date_util.h \
    $$PWD/cpp/mu_generic_control.h \
    $$PWD/cpp/mu_geometry_util.h \
    $$PWD/cpp/mu_global.h \
    $$PWD/cpp/mu_macros.h \
    $$PWD/cpp/mu_object.h \
    $$PWD/cpp/mu_request_model.h \
    $$PWD/cpp/mu_routes.h \
    $$PWD/cpp/mu_login_engine_routes.h \
    $$PWD/cpp/mu_login_engine.h \
    $$PWD/cpp/mu_login_token.h \
    $$PWD/cpp/mu_login_profile.h \
    $$PWD/cpp/mu_login_session.h \
    $$PWD/cpp/mu_model_navigator.h \
    $$PWD/cpp/mu_model_table.h \
    $$PWD/cpp/mu_notification.h \
    $$PWD/cpp/mu_object_util.h \
    $$PWD/cpp/mu_paint_setting.h \
    $$PWD/cpp/mu_paint_setting_drawing.h \
    $$PWD/cpp/mu_paint_setting_geometry.h \
    $$PWD/cpp/mu_paint_setting_item.h \
    $$PWD/cpp/mu_paint_setting_state.h \
    $$PWD/cpp/mu_register.h \
    $$PWD/cpp/mu_request.h \
    $$PWD/cpp/mu_server_link.h \
    $$PWD/cpp/mu_string_util.h \
    $$PWD/cpp/mu_validation_util.h \
    $$PWD/cpp/mu_validation_util_public.h \
    $$PWD/cpp/mu_validation_util_ptb.h \
    $$PWD/cpp/mu_variant_util.h \
    $$PWD/cpp/private/p_mu_network_activity.h \
    $$PWD/cpp/private/p_mu_model_navigator.h \
    $$PWD/cpp/private/p_mu_notification.h \
    $$PWD/cpp/private/p_mu_request.h \
    $$PWD/cpp/private/p_mu_request_response.h \
    $$PWD/cpp/private/p_mu_request_job.h \
    $$PWD/cpp/private/p_mu_request_queue.h \
    $$PWD/cpp/private/p_mu_request_queue_pvt.h

SOURCES += \
    $$PWD/cpp/mu_app_engine_routes.cpp \
    $$PWD/cpp/mu_app_info.cpp \
    $$PWD/cpp/mu_app_repository.cpp \
    $$PWD/cpp/mu_app_session.cpp \
    $$PWD/cpp/mu_application.cpp \
    $$PWD/cpp/mu_cache_util.cpp \
    $$PWD/cpp/mu_date_util.cpp \
    $$PWD/cpp/mu_generic_control.cpp \
    $$PWD/cpp/mu_geometry_util.cpp \
    $$PWD/cpp/mu_object.cpp \
    $$PWD/cpp/mu_request_model.cpp \
    $$PWD/cpp/mu_routes.cpp \
    $$PWD/cpp/mu_login_engine_routes.cpp \
    $$PWD/cpp/mu_login_engine.cpp \
    $$PWD/cpp/mu_login_token.cpp \
    $$PWD/cpp/mu_login_profile.cpp \
    $$PWD/cpp/mu_login_session.cpp \
    $$PWD/cpp/mu_model_navigator.cpp \
    $$PWD/cpp/mu_model_table.cpp \
    $$PWD/cpp/mu_notification.cpp \
    $$PWD/cpp/mu_object_util.cpp \
    $$PWD/cpp/mu_paint_setting.cpp \
    $$PWD/cpp/mu_paint_setting_drawing.cpp \
    $$PWD/cpp/mu_paint_setting_geometry.cpp \
    $$PWD/cpp/mu_paint_setting_item.cpp \
    $$PWD/cpp/mu_paint_setting_state.cpp \
    $$PWD/cpp/mu_register.cpp \
    $$PWD/cpp/mu_request.cpp \
    $$PWD/cpp/mu_server_link.cpp \
    $$PWD/cpp/mu_string_util.cpp \
    $$PWD/cpp/mu_validation_util.cpp \
    $$PWD/cpp/mu_validation_util_public.cpp \
    $$PWD/cpp/mu_validation_util_ptb.cpp \
    $$PWD/cpp/mu_variant_util.cpp \
    $$PWD/cpp/private/p_mu_notification.cpp \
    $$PWD/cpp/private/p_mu_request.cpp \
    $$PWD/cpp/private/p_mu_request_queue.cpp

QT += widgets

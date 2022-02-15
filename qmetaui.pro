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

INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/cpp

RESOURCES += \
    $$PWD/qml/controls/controls.qrc \
    $$PWD/qml/dynamic/dynamic.qrc \
    $$PWD/qml/forms/forms.qrc \
    $$PWD/qml/network/network.qrc
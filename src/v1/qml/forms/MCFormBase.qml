import QtQuick 2.14
import QtQuick.Controls 2.14

import "qrc:/QMetaUI/Controls"

MCForm {
    id: control

    readonly property alias e : ee
    property bool back: false

    property int  index: 0
    property bool isEmpty: true
    property bool isLoading: false
    property bool isLoaded: {
        return pvt.isLoaded
    }

    property alias f: control

    signal backClicked()
    signal nextClicked()
    signal searchClicked()
    signal clear()
    signal load()

    visible: false
    enabled: true

    MCFormEnum {id: ee}

    onLoad: pvt.isLoaded=true

    Item {
        id: pvt
        property bool isLoaded: false
    }

    MouseArea {
        anchors.fill: parent
        onClicked   : {
            Qt.inputMethod.hide()
            control.forceActiveFocus()
        }
    }
}

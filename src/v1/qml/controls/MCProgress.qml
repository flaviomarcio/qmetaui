import QtQuick 2.14
import QtQuick.Controls 2.14

ProgressBar {
    id: control
    value: 0.5
    padding: 2

    property alias frameBackground: rec_backgroud
    property alias frameProgress: rec_progress
    property alias frameindeterminate: rec_indeterminate

    property alias settings: settings
    property MCSettingRec settingBase: null

    MCSettingRec {
        id: settings
    }

    readonly property bool loading : {return control.state===control.stateLoading}

    readonly property alias stateActived  : settings.stateActived
    readonly property alias stateFocused  : settings.stateFocused
    readonly property alias stateInactived: settings.stateInactived
    readonly property alias stateLoading  : settings.stateLoading
    readonly property alias stateAttention: settings.stateAttention
    readonly property alias statePressed  : settings.statePressed
    readonly property alias stateError    : settings.stateError
    readonly property alias settingState  : settings.settingState

    width: parent.width
    height: parent.width/4

    indeterminate: true

    Rectangle {
        id: rec_indeterminate
        radius: 2
        width: 20
        height: control.height
        visible: false
        onVisibleChanged: visible=false
    }

    background: Rectangle {
        id: rec_backgroud
        implicitWidth: 200
        implicitHeight: 10
        color: "lightgray"
        radius: 3
    }

    contentItem:Item {
        Rectangle {
            id: rec_progress
            visible: !control.indeterminate
            width: control.visualPosition * parent.width
            height: parent.height
            radius: 2
            color: "gray"
            border.width: 0
        }

        Item {
            anchors.fill: parent
            anchors.margins: 1
            visible: control.indeterminate
            clip: true
            Row {
                Repeater {
                    Rectangle {
                        radius: rec_indeterminate.radius
                        color: index % 2 ? rec_backgroud.color : rec_indeterminate.color
                        width: rec_indeterminate.width
                        height: rec_indeterminate.height
                    }
                    model: control.width / 20 + 2
                }
                XAnimator on x {
                    from: -40 ; to: 0
                    loops: Animation.Infinite
                    running: control.indeterminate
                }
            }
        }
    }

}

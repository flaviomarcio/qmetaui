import QtQuick 2.14
import QtQuick.Controls 2.14

Rectangle {
    id: control
    state: stateActived
    clip: false

    property string displayName: 'display'

    property alias label: labelTitle
    property alias settings: controlSettings
    property alias settingsTitle: settingsTitle
    property alias settingBase: recBackground.settingBase

    readonly property alias stateActived  : controlSettings.stateActived
    readonly property alias stateFocused  : controlSettings.stateFocused
    readonly property alias stateInactived: controlSettings.stateInactived
    readonly property alias stateLoading  : controlSettings.stateLoading
    readonly property alias stateAttention: controlSettings.stateAttention
    readonly property alias statePressed  : controlSettings.statePressed
    readonly property alias stateError    : controlSettings.stateError

    property alias settingsDelegate: delegateLabel
    property alias settingsHighlight : delegateHighlight

    signal clicked(var model)

    property alias settingState: recBackground.settingState

    MCSettingRec{
        id: controlSettings
    }
    MCSettingRec{
        id: settingsTitle
    }
    MCSettingRec{
        id: delegateLabel
    }
    MCSettingRec{
        id: delegateHighlight
    }

    MCRectangleState {
        id: recBackground
        settingBase: controlSettings
        state: control.state
        visible: true
        anchors.fill: parent
        anchors.topMargin: (itemLabel.visible)?(itemLabel.height*0.5):0
        Item {
            id: itemLabel
            z :1
            anchors {
                verticalCenter: parent.top
                left : parent.left
                right: parent.right
            }
            height: MCMeasures.percByScreenHeight(3)

            MCRectangleState {
                id: recTitle
                anchors.centerIn: parent
                visible: true
                state  : control.state
                height : parent.height
                width  : MCMeasures.percByScreenWidth(30)
                settingBase: settingsTitle

                MCLabelState {
                    id: labelTitle
                    state: parent.state
                    settingBase: settingsTitle
                    anchors.fill: parent
                    visible: true
                }
            }
        }
    }
}

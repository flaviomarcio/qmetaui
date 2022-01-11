import QtQuick 2.14

Text {
    id: control
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
    wrapMode: Text.NoWrap
    visible: true

    signal change()

    property alias settings: settings

    property MCSettingRec settingBase: null

    MCSettingRec {
        id: settings
        state: parent.state
        onChange: control.change()
    }

    readonly property alias stateActived  : settings.stateActived
    readonly property alias stateFocused  : settings.stateFocused
    readonly property alias stateInactived: settings.stateInactived
    readonly property alias stateLoading  : settings.stateLoading
    readonly property alias stateAttention: settings.stateAttention
    readonly property alias statePressed  : settings.statePressed
    readonly property alias stateError    : settings.stateError

    readonly property MCSettingState settingState: control.settings.settingState
}

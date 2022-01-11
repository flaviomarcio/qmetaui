import QtQuick 2.5

GridView {
    id: control
    clip: true

    property alias settings: settings

    property MCSettingRec settingBase: null

    MCSettingRec{
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
    readonly property MCSettingState settingState: settings.settingState

    cellHeight: MCMeasures.densityPixel(75)
    cellWidth: control.width

    property int spacing: settingState.spacing

    function isLineSelected(row){
        if(row === control.currentIndex)
            return true
        else
            return false
    }
}

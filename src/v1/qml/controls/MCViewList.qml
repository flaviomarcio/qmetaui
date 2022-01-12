import QtQuick 2.14
import QtQuick.Controls 2.14
import "qrc:/QMetaUI/Controls"

ListView {
    id: control
    clip: true

    function setFocus(){
        control.focus=true
    }

    function forceRefresh(){
        let _model=control.model
        control.model=null
        control.model=Qt.binding(function(){return _model})
    }


    property int cellHeight: control.height
    property int cellWidth: control.width

    highlightRangeMode: ListView.StrictlyEnforceRange
    snapMode: ListView.NoSnap;
    layoutDirection: Qt.LeftEdge
    orientation: ListView.Vertical


    property alias settings: settings
    property MCSettingRec settingBase: null

    readonly property alias stateActived  : settings.stateActived
    readonly property alias stateFocused  : settings.stateFocused
    readonly property alias stateInactived: settings.stateInactived
    readonly property alias stateLoading  : settings.stateLoading
    readonly property alias stateAttention: settings.stateAttention
    readonly property alias statePressed  : settings.statePressed
    readonly property alias stateError    : settings.stateError
    readonly property MCSettingState settingState: settings.settingState
    spacing: (settingState == null || settingState == undefined)?spacing:settingState.spacing

    MCSettingRec {
        id:settings
    }
}

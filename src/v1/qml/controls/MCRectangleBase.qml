import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14

Rectangle{
    id:control
    implicitHeight:  MCMeasures.densityPixel(5)
    implicitWidth:  MCMeasures.densityPixel(10)
    width: MCMeasures.densityPixel(10)
    height: MCMeasures.densityPixel(5)
    clip : true
    state: stateActived

    onStateChanged: {
        if(String(state).trim()!=="")
            settings.state=control.state
    }

    property alias settings: settings
    property MCSettingRec settingBase: null

    MCSettingRec {
        id: settings
    }

    readonly property bool loading : settings.state===control.stateLoading

    readonly property alias stateActived  : settings.stateActived
    readonly property alias stateFocused  : settings.stateFocused
    readonly property alias stateInactived: settings.stateInactived
    readonly property alias stateLoading  : settings.stateLoading
    readonly property alias stateAttention: settings.stateAttention
    readonly property alias statePressed  : settings.statePressed
    readonly property alias stateError    : settings.stateError
    readonly property alias settingState  : settings.settingState

    function setStateActived(){
        control.state=control.stateActived
    }

    function setStateInactived(){
        control.state=control.stateInactived
    }

    function setStateLoading(){
        state=control.stateLoading
    }
}

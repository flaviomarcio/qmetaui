import QtQuick 2.14
import QtReforce.Meta.Controls 0.0
import "qrc:/QMetaUI/Controls"

MCRectangleBase{
    id:control
    implicitHeight: 50//MCMeasures.densityPixel(30)
    implicitWidth: 50//MCMeasures.densityPixel(30)
    width: 50//MCMeasures.densityPixel(30)
    height: 50//MCMeasures.densityPixel(30)

    state: stateActived
    onStateChanged: {
        if(String(state).trim()==="")
            state=stateActived
        else
            settings.state=control.state
    }

    property alias settings: settings
    property MCSettingRec settingBase: null
    MCSettingRec{
        id: settings
    }
    readonly property alias stateActived  : settings.stateActived
    readonly property alias stateFocused  : settings.stateFocused
    readonly property alias stateInactived: settings.stateInactived
    readonly property alias stateLoading  : settings.stateLoading
    readonly property alias stateAttention: settings.stateAttention
    readonly property alias statePressed  : settings.statePressed
    readonly property alias stateError    : settings.stateError
    readonly property alias settingState: settings.settingState

}

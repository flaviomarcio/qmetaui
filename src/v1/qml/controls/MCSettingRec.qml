import QtQuick 2.0

Item {
    id: control
    property alias actived : actived
    property alias inactived : inactived
    property alias loading : loading
    property alias focused : focused
    property alias attention : attention
    property alias error : error
    property alias pressed : pressed
    signal change()

    property Item base: null

    readonly property string stateActived: "actived"
    readonly property string stateFocused: "focused"
    readonly property string stateInactived: "inactived"
    readonly property string stateLoading: "loading"
    readonly property string stateAttention: "attention"
    readonly property string statePressed: "pressed"
    readonly property string stateError: "error"

    onBaseChanged: {
        if(base!=null){
            control.load(base)
        }
    }

    property MCSettingState settingState:stateResolver(state)

    onStateChanged: {
        settingState=stateResolver(state)
    }

    MCSettingState {
        id: actived
        state:control.stateActived
    }
    MCSettingState {
        id: inactived
        state:control.stateInactived
    }
    MCSettingState {
        id: loading
        state:control.stateLoading
    }
    MCSettingState {
        id: focused
        state:control.stateFocused
    }
    MCSettingState {
        id: attention
        state:control.stateActived
    }
    MCSettingState {
        id: error
        state:control.stateError
    }
    MCSettingState {
        id: pressed
        state:control.statePressed
        opacity: 0.8
    }

    function load(object){
        control.actived.load(object.actived)
        control.inactived.load(object.inactived)
        control.loading.load(object.loading)
        control.focused.load(object.focused)
        control.attention.load(object.attention)
        control.error.load(object.error)
        control.pressed.load(object.pressed)
    }

    function stateResolver(state){
        state=String(state).toLowerCase();
        if(state===actived.state)
            return actived;
        else if(state===inactived.state)
            return inactived;
        else if(state===loading.state)
            return loading;
        else if(state===focused.state)
            return focused;
        else if(state===attention.state)
            return attention;
        else if(state===error.state)
            return error;
        else if(state===pressed.state)
            return pressed;
        else
            return inactived
    }

    function clear(){
        actived.clear()
        inactived.clear()
        loading.clear()
        focused.clear()
        attention.clear()
        pressed.clear()
    }
}

import QtQuick 2.14

MCButtonBase{
    id: control
    color:settingState.backgroundColor
    label {
        color  : settingState.label.color
        font   : settingState.label.font                
    }

    image {
        source: settingState.image
    }    
    radius :settingState.radius
    opacity:settingState.opacity

    Connections {
        id: cnnMouse
        target: control.mouseArea        
        property var lastState
        property var actualState

        function onPressed(){
            if(enabled){
                lastState=state
                if(lastState==="")
                    lastState=enabled?control.settings.stateActived:control.settings.stateInactived
                actualState= control.statePressed
                control.state = actualState
            }
        }

        function onReleased(){
            if(control.state===actualState)
                control.state=lastState
        }
    }
}

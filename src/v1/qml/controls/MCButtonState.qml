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
}

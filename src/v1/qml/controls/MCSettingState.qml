import QtQuick 2.14
import QtQuick.Controls 2.14

Item {
    id: control
    property string name
    property bool clip: false
    property color backgroundColor: "transparent"
    property alias forecolor: label.color
    property color borderColor: "gray"
    property int borderWith: 0
    property alias label: label
    property real radius: 0
    property string image: ""
    property string text: ""
    property alias font: label.font
    property real spacing: MCMeasures.densityPixel(3)
    opacity: 1
    visible: true
    height: 50
    width: 50
    enabled: true
    Item {
        visible: {return false}
        Label{
            id:label
            height: {return 0}
            visible: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font{
                weight: Font.Normal
            }
        }
    }

    function clear(){

    }

    function load(object){
        control.name            = object.name
        control.clip            = object.clip
        control.backgroundColor = object.backgroundColor
        control.forecolor       = object.forecolor
        control.borderColor     = object.borderColor
        control.borderWith      = object.borderWith
        control.label.visible   = object.label.visible
        control.label.elide     = object.label.elide
        control.label.horizontalAlignment = object.label.horizontalAlignment
        control.label.verticalAlignment = object.label.verticalAlignment
        control.radius          = object.radius
        control.image           = object.image
        control.text            = object.text
        control.font            = object.font
        control.height          = object.height
        control.width           = object.width
        control.visible         = object.visible
        control.opacity         = object.opacity
    }

}

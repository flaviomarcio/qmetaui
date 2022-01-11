import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14

import "qrc:/QMetaUI/Controls"

MCRectangleState {
    id: control

    clip: true

    z: parent.z + 20

    property real startY: 0
    property real endY: 0
    property int duration : 1500
    property alias message: innerText.text

    signal started()
    signal finished()

    state: ""

    visible: false
    enabled: visible
    radius : 0

    anchors.horizontalCenter: parent===null? undefined : parent.horizontalCenter

    Material.elevation : 4

    onStateChanged: {
        if(String(control.state).trim().length>0 && String(control.message).trim().length>0){
            idAnimation.restart()
        }
    }

    function getRoot(){
        var p=parent
        while(p!==null)
            if(p.parent===null){
                break
            } else {
                p=p.parent
            }
        return p
    }


    function showMessage(message){
        parent=getRoot()
        innerText.text=String(message).trim()
        control.state=""
        control.state=control.stateActived        
    }

    function showError( message ){
        parent=getRoot()
        innerText.text=String(message).trim()
        control.state=""
        control.state=control.stateError
    }

    function showAttention( message ){
        parent=getRoot()
        innerText.text=String(message).trim()
        control.state=""
        control.state=control.stateAttention
    }

    MCLabelState  {
        id:innerText
        anchors.fill: parent
        wrapMode: Label.WordWrap
        state: control.state
        settingBase: control.settingBase
    }

    SequentialAnimation {
        id: idAnimation
        PropertyAnimation { target: control; property: "visible" ; to: true             ; duration: 50   }
        NumberAnimation   { target: control; property: "y"       ; from: control.startY ; to: control.endY ; duration: 100 }

        PauseAnimation    { duration: control.duration }

        PropertyAnimation { target: control; property: "visible" ; to: false             ; duration: 50   }
        NumberAnimation   { target: control; property: "y"       ; from: control.endY    ; to: control.startY ; duration: 100 }

        onStarted: {
            control.started()
        }

        onFinished: {
            control.state=""
            control.finished()
        }
    }
}


import QtQuick 2.14
import QtQuick.Controls 2.14

Rectangle {
    id: control
    color   : "transparent"
    anchors.fill: parent
    z: 99999
    visible: false
    property Item frameMessage: null

    property string title   : ""
    property string text    : ""
    property bool   outClose: true
    property var data

    signal help()
    signal accepted()
    signal rejected()
    signal yes()
    signal no()
    signal apply()
    signal reset()


    onHelp    : control.close()
    onAccepted: control.close()
    onRejected: control.close()
    onYes     : control.close()
    onNo      : control.close()
    onApply   : control.close()
    onReset   : control.close()

    function open(data){
        if(control.frameMessage!==null){
            control.data=data
            control.frameMessage.parent=control
            control.frameMessage.anchors.centerIn = control
            control.frameMessage.visible=true
            control.visible=true
        }
    }

    function close(){
        control.visible=false
        control.frameMessage.visible=false
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            if (control.outClose)
                visible = false
        }
    }
}

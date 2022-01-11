import QtQuick 2.14
import QtQuick.Controls 2.14

MCMessageDialog{
    id: control
    title: qsTr("Message")
    frameMessage: MCRectangleState{
        border.width: 1
        border.color: "gray"
        height: parent.height / 2
        width: parent.width / 2

        Button{
            id:buttonAcceppt
            text: qsTr("OK")
            anchors.centerIn: parent
            width: parent.width/3
            anchors.bottom: parent.bottom
            anchors.left: anchors.left
            onClicked: control.accepted();
        }
    }
}

import QtQuick 2.14
import QtQuick.Controls 2.14

MCMessageDialog{
    id: control
    title: qsTr("Questão")
    frameMessage: MCRectangle {
        id: formMessage
        parent: control
        color: "white"
        border.width: 1
        border.color: "gray"
        width: control.height / 2
        height: control.width / 2
        anchors.margins: 5
        visible: false
        Item{
            anchors.fill: parent
            MCLabel {
                id: text
                anchors.margins: 5
                height: parent.height*0.6
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font{
                    weight: Font.Light
                    bold: true
                }
                text: control.text

            }
            Item{
                anchors{
                    margins: 5
                    top: text.bottom
                    left: parent.left
                    right: parent.right
                    bottom: parent.bottom
                }
                MCButton{
                    id:buttonAcceppt
                    width: (parent.width-anchors.margins)/2
                    MCLabel{
                        anchors.centerIn: parent
                        text: qsTr("Aceitar")
                    }
                    border.width: 1
                    border.color: "gray"
                    anchors{
                        top: parent.top
                        bottom: parent.bottom
                        left: parent.left
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: control.accepted();
                    }
                }
                MCRectangle{
                    MCLabel{
                        anchors.centerIn: parent
                        text: qsTr("Rejeitar")
                    }
                    border.width: 1
                    border.color: "gray"
                    anchors{
                        leftMargin: 5
                        top: parent.top
                        bottom: parent.bottom
                        left: buttonAcceppt.right
                        right: parent.right
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: control.rejected();
                    }
                }
            }
        }
    }

    onFrameMessageChanged: {
        formMessage.visible=false
    }

}

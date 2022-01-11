import QtQuick 2.14
import QtQuick.Controls 2.14

Item {
    id: control
    clip: true

    property alias model: view.model
    property alias delegate: view.delegate
    property alias spacing: view.spacing
    property alias view: view

    property string displayName: "display"

    property alias cellHeight: view.cellHeight
    property alias cellWidth: view.cellWidth

    property int currentIndex: -1
    property var currentItem: null
    property alias currentText: textOption.text

    Rectangle {
        anchors.fill: parent
        color: "white"
        border.width: 1
        border.color: "gray"

        anchors{
            fill: parent
            leftMargin: 2
        }

        MCLabel {
            id:textOption
            anchors.fill: parent
            text: control.currentText
            color: "gray"
        }

        MouseArea{
            anchors.fill: parent
            onClicked: {
                viewRec.parent=root
                viewRec.visible=true
            }
        }
    }

    Rectangle {
        id: viewRec
        color: "transparent"
        anchors.fill: parent

        MouseArea{
            anchors.fill: parent
            onClicked: {
                view.visible=false
            }
        }

        MCViewList {
            id: view
            anchors.fill: parent
            spacing: 2
            interactive: false
            //visible: {return control.visible}
            height: parent.height*0.6
            width: parent.width*0.6

            cellWidth: view.width

            delegate:
                Rectangle {
                id: itemDelegate
                width : view.cellWidth
                height: view.cellHeight
                Row {
                    anchors.centerIn: parent
                    height : parent.height * 0.6
                    width  : parent.width  * 0.92
                    spacing: parent.width * 0.04
                    MCLabel {
                        text  : model.display
                        width : parent.width
                        height: parent.height
                        color: "white"
                        elide: Label.ElideRight
                        wrapMode : Text.WordWrap
                        horizontalAlignment: Qt.AlignLeft
                        verticalAlignment  : Qt.AlignVCenter
                        font {
                            family       : FontDefinitions.fontDefault
                            pixelSize    : FontDefinitions.fontLocalSizeSM
                            letterSpacing: FontDefinitions.fontLocalLetterSpacingSM
                        }
                    }
                }
                MouseArea {
                    z : 0
                    enabled : itemDelegate.enabled
                    anchors.fill: parent
                    onClicked: {
                        view.visible=false
                        control.currentIndex=model.index
                        control.currentItem=model
                        control.currentText=model[control.displayName]
                    }
                }
            }
        }

    }




}

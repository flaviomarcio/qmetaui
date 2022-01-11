import QtQuick 2.14
import QtQuick.Controls 2.14

Item {
    id: control
    clip: true

    property alias model: view.model
    property alias delegate: view.delegate
    property alias spacing: view.spacing
    property alias view: view

    property alias cellHeight: view.cellHeight
    property alias cellWidth: view.cellWidth

    function forceLayout(){
        view.forceLayout()
    }

    MCViewList {
        id: view
        anchors.fill: parent
        spacing: 2
        interactive: false
        visible: {return control.visible}

        delegate:
            Rectangle {
            id: itemMenuPrincipal
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
                z        : 0
                enabled  : itemMenuPrincipal.enabled
                anchors.fill: parent
            }
        }
    }

}

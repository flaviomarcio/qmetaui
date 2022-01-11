import QtQuick 2.14

MCRectangleBase {
    id: control

    anchors{
        top: parent.top
        left: parent.left
        right: parent.right
    }

    property alias label : label

    MCLabel{
        id: label
        anchors.fill: parent
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        opacity: 1
    }
}

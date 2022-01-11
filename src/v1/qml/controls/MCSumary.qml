import QtQuick 2.14

MCRectangleBase {
    id: control
    property alias label : label
    MCLabel{
        id: label
        anchors.fill: parent
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.weight: Font.Light
    }
}

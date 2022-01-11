import QtQuick 2.14

Rectangle {
    id: control    

    color: "transparent"

    property alias sourceSize: image.sourceSize
    property alias asynchronous: image.asynchronous
    property alias status: image.status
    property alias cache: image.cache
    property alias source: image.source
    property alias horizontalAlignment: image.horizontalAlignment
    property alias verticalAlignment: image.verticalAlignment
    property alias fillMode: image.fillMode
    property alias image: image

    property alias paintedHeight : image.paintedHeight
    property alias paintedWidth : image.paintedWidth

    Image {
        id: image
        state: parent.state
        anchors.centerIn: parent
        width: parent.width
        fillMode:Image.PreserveAspectFit
    }
}


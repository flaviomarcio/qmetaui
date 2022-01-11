import QtQuick 2.14
import QtLocation 5.12
import QtPositioning 5.12

MapQuickItem {
    id: control

    width: externalRectangle.width
    height: externalRectangle.height

    property alias sourceImage: internalRectangle.source

    anchorPoint.x: externalRectangle.width/4
    anchorPoint.y: externalRectangle.height

    property alias externalRectangle: externalRectangle
    property alias internalRectangle: internalRectangle
    property alias image: internalRectangle.image

    sourceItem: Rectangle {
        id: externalRectangle
        color: MCColors.transparent
        radius: MCMeasures.densityPixel(50)
        width: MCMeasures.densityPixel(50)
        height: width
        MCImage{
            id: internalRectangle
            radius: parent.radius
            anchors{
                fill: parent
            }
            source: ""
        }
    }
}

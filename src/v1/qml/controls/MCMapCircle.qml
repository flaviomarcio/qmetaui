import QtQuick 2.14
import QtLocation 5.12
import QtPositioning 5.12

MapQuickItem {
    id: control

    width: externalRectangle.width
    height: externalRectangle.height

    anchorPoint.x: externalRectangle.width/4
    anchorPoint.y: externalRectangle.height

    coordinate: map.coordinate

    property alias externalRectangle: externalRectangle
    property alias internalRectangle: internalRectangle

    sourceItem: Rectangle {
        id: externalRectangle
        color: MCColors.alpha("#005E80", 0.4)
        radius: MCMeasures.densityPixel(50)
        width: MCMeasures.densityPixel(50)
        height: width
        Rectangle{
            id: internalRectangle
            anchors{
                fill: parent
                margins: MCMeasures.densityPixel(10)
            }
            radius: parent.radius
            color: "#005E80"
            border.color: "white"
            border.width: MCMeasures.densityPixel(5)
        }
    }
}

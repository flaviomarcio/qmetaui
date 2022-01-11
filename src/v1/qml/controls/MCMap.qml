import QtQuick 2.14
import QtLocation 5.12
import QtPositioning 5.12

Map {
    id: control
    zoomLevel: 14

    property alias selfPosition   : selfPosition
    property alias positionSource : positionSource
    property int   updateInterval : 1000

    PositionSource {
        id: positionSource
        updateInterval: 100
        active: true
        onPositionChanged:{
            ++count
            if(count>10){
                updateInterval=control.updateInterval
            }
            else{
                control.center = positionSource.position.coordinate
            }
        }

        property int count: 0
    }

    MCMapCircle {
        id: selfPosition
        coordinate: positionSource.position.coordinate
        visible: true
    }

}

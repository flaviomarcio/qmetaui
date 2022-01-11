pragma Singleton

import QtQuick 2.14

Item {
    id:measures

    property real pixelDensity: 4.46
    property real multiplier  : 1.4
    property int  guFactor    : 64

    property real scaleFactorFont : 0
    property real scaleFactor     : 0

    property real screenWidth : 1
    property real screenHeight: 1

    function percByScreenHeight(value) {        
        return densityPixel((value/100) * screenHeight)
    }

    function percByScreenWidth(value){
        return densityPixel((value/100) * screenWidth)
    }

    //density-independent pixels
    function densityPixel(value) {
        return value//Math.round( value * innerData.dp  * multiplier )
    }

    //gridUnit
    function gridUnit( value ) {
        return densityPixel( value *  innerData.gridUnit )
    }

    //scalable pixels
    function sp(value){
        return  densityPixel(value) * scaleFactorFont
    }

    QtObject {
        id:innerData

        property int  gridUnit: {
            return densityPixel(measures.guFactor)
        }

        property real dp : {
            return pixelDensity
        }
    }
}

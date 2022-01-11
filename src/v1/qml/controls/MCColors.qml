pragma Singleton

import QtQuick 2.14

QtObject {
    property color transparent            : "transparent"
    property color colorPrimaryDarkest    : "#73B3FF"
    property color colorPrimaryDark       : "#D6D6D6"
    property color colorPrimaryMedium     : "#FBFBFB"
    property color colorPrimaryLight      : "#313450"
    property color colorPrimaryLightest   : "#4D607A"
    property color colorPrimaryLightClear : "#62728A"

    property color colorSecondaryDarkest  : "#E4EDF1"
    property color colorSecondaryDark     : "#BEC8D1"
    property color colorSecondaryMedium   : "#D3DAE0"
    property color colorSecondaryLight    : "#ECECEC"
    property color colorSecondaryLightest : "#809931"
    property color colorSecondaryClear    : "#2B3F5C"

    property color colorNeutralDarkest    : "#005E80"
    property color colorNeutralDark       : "#8B8B8B"
    property color colorNeutralMedium     : "#DFE5EB"
    property color colorNeutralLight      : "#1672F7"
    property color colorNeutralLightest   : "#FFFFFF"
    property color colorNeutralClear      : "#1E314D"

    property color colorSupportError      : "#B00020"
    property color colorSupportNeutral    : "#F5F9FC"
    property color colorSupportAttention  : "#005E80"

    function shadeLight(alpha) {
        return Qt.rgba(0,0,0,alpha)
    }

    function shadeDark(alpha) {
        return Qt.rgba(1,1,1,alpha)
    }

    function alpha(color, alpha) {
        var realColor = Qt.darker(color, 1)
        realColor.a = alpha
        return realColor
    }

    function isDarkColor(background) {
        var temp = Qt.darker(background, 1)
        var a = 1 - ( 0.299 * temp.r + 0.587 * temp.g + 0.114 * temp.b);
        return temp.a > 0 && a >= 0.3
    }

    function isLightColor(background) {
        return !isDarkColor(background)
    }
}

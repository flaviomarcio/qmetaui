import QtQuick 2.14
import QtReforce.Meta.Controls 0.0
import "qrc:/QMetaUI/Controls"

MCRectangleBase{
    id:control
    implicitHeight: MCMeasures.densityPixel(50)
    implicitWidth : MCMeasures.densityPixel(50)
    width         : MCMeasures.densityPixel(50)
    height        : MCMeasures.densityPixel(50)

    clip: settingState.clip
    color:settingState.backgroundColor
    radius: settingState.radius
    visible: settingState.visible
    // A INCLUSÃO DESSA LINHA IMPEDE A PROPAGAÇÃO DO ENABLED PARA OS FILHOS DESSE RETANGLE
    //enabled: settingState.enabled

    border {
        color: settingState.borderColor
        width: settingState.borderWith
    }
    onSettingBaseChanged: {
        if(settingBase!==null){
            settings.load(settingBase)
        }
    }

}

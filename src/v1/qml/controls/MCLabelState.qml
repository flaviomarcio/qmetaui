import QtQuick 2.14

MCLabelBase {
    id: control
    color:settingState.label.color
    font: settingState.label.font
    elide: settingState.label.elide
    //visible: settingState.label.visible

    onSettingBaseChanged: {
        if(settingBase!==null){
            settings.load(settingBase)
        }
    }
}

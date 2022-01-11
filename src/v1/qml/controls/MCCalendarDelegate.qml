import QtQuick 2.14
import Qt.labs.calendar 1.0

MCRectangleState{
    id: control

    signal clicked()
    property Item controlDateChange: null
    property MonthGrid monthGrid: null

    property date localDate

    property date currentDate
    property bool selected: false
    property bool multiSelect: false


    state: selected?stateFocused:stateActived

    MCLabelState{
        anchors.fill: parent
        text: model.day
        state: control.state
        settingBase: parent.settings
    }

    Connections{
        id: cnnPvt
        target: null
        function onCurrentDateChanged(){
            if(!control.multiSelect){
                if(!dateUtil.equalDate(control.localDate, control.currentDate))
                    control.selected=false
            }
        }
    }
    MouseArea{
        anchors.fill: parent
        onClicked: {
            if(multiSelect){
                control.selected=!control.selected
            }
            else{
                control.selected=true
                cnnPvt.target=control.controlDateChange
            }
            control.clicked()
        }
    }
}

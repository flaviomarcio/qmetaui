import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14
import Qt.labs.calendar 1.0

MCGroupBoxItems{
    id: control
    clip: true
    state: stateActived

    signal clear()

    signal reseteDates()
    signal selectDate(var schedule_dt)

    property date from: dateUtil.currentDate()
    property date to: dateUtil.lastDayNextMonth()
    property bool multiSelect: false

    property date currentDate : dateUtil.currentDate()

    property alias calendarModel: calendarModel

    property alias settingsDelegateTitle: settingDelegateTitle

    onClear:{
        var d0=dateUtil.currentDate();
        var d1=dateUtil.lastDayNextMonth();

        control.from = d0;
        control.to = d1;

        view.model=null
        view.model=calendarModel
    }

    view {
        currentIndex: 0
        model       : calendarModel
        cellHeight  : MCMeasures.percByScreenHeight(34)
        spacing     : MCMeasures.percByScreenHeight(1)
    }

    delegate : deletateCalendar
    model : CalendarModel {
        id:calendarModel
        from: control.from
        to : control.to
    }

    MCSettingRec {
        id: settingDelegateTitle
        actived {
            visible: true
            label.visible: true
        }
        inactived{
            visible: true
            label.visible: true
        }
        loading{
            visible: true
            label.visible: true
        }
        focused{
            visible: true
            label.visible: true
        }
    }

    Component {
        id: deletateCalendar
        Item {
            height: view.cellHeight
            width : view.cellWidth-(anchors.margins+anchors.leftMargin+anchors.rightMargin)

            MCGroupBox {
                id:itemRow
                settings.base: control.settingsDelegate
                settingsTitle.base: control.settingsDelegateTitle
                state: control.state
                anchors.fill: parent
                label {
                    text:  Qt.locale().monthName(model.month)
                    visible: true
                }
                Item {
                    anchors {
                        fill: parent
                        topMargin: label.visible ? MCMeasures.percByScreenHeight(2):0
                    }
                    Item {
                        anchors {
                            fill: parent
                            margins: MCMeasures.percByScreenHeight(1)
                        }

                        DayOfWeekRow {
                            id: dayOfWeekRow
                            locale: itemGrid.locale
                            anchors{
                                top: parent.top
                                left: parent.left
                                right: parent.right
                            }
                        }

                        MonthGrid {
                            id: itemGrid
                            anchors {
                                top: dayOfWeekRow.bottom
                                left: parent.left
                                right: parent.right
                                bottom: parent.bottom
                            }
                            month : model.month
                            year  : model.year
                            locale: Qt.locale()
                            delegate:
                                MCCalendarDelegate {
                                id: delegateItem
                                property bool isThisMonth: itemGrid.month === model.month
                                property bool isPast: {
                                    var local_dt = new Date(model.year, model.month, model.day)
                                    return dateUtil.isLowerDateTime(local_dt, control.from)
                                }
                                property bool selectDate: false

                                Connections {
                                    target: control
                                    function onReseteDates(){
                                        delegateItem.selectDate=false
                                        delegateItem.selected=false
                                    }
                                    function onSelectDate(schedule_dt){
                                        var local_dt = new Date(model.year, model.month, model.day)
                                        if (dateUtil.equalDate(dateUtil.toDate(schedule_dt), dateUtil.toDate(local_dt))){
                                            delegateItem.selectDate=true
                                        }
                                    }
                                }

                                Rectangle {
                                    height: parent.height * 0.3
                                    width: height
                                    radius: parent.height * 0.5
                                    anchors.top: parent.top
                                    anchors.left: parent.left
                                    visible: (isThisMonth && selectDate)
                                    color: MCColors.colorNeutralDarkest
                                }

                                state: {
                                    if (isThisMonth && !isPast )
                                        return (selected?stateFocused:stateActived)
                                    return stateInactived
                                }
                                clip: true
                                visible: true
                                controlDateChange: control
                                localDate: model.date
                                multiSelect: control.multiSelect
                                monthGrid: itemGrid
                                settingBase: control.settingsDelegate
                                enabled: (isThisMonth && !isPast )
                                onClicked: {
                                    control.currentDate=dateUtil.toDate(date)
                                    var data={'date': date, 'year':model.year, 'month':model.month, 'day':model.day, 'today': model.today,'weekNumber': model.weekNumber}
                                    control.clicked(data)
                                    delegateItem.selected=true
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

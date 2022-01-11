import QtQuick 2.14
import QtQuick.Controls 2.14

Item {
    id: control
    state: stateActived

    property string displayName: 'display'

    property alias label: labelTitle
    property alias settings: controlSettings
    property alias settingsTitle: settingsTitle
    property alias settingBase : recBackground.settingBase
    property alias settingState: recBackground.settingState


    property bool showLoading : false
    property alias labelEmpty : labelEmpty

    readonly property alias stateActived : controlSettings.stateActived
    readonly property alias stateFocused : controlSettings.stateFocused
    readonly property alias stateInactived: controlSettings.stateInactived
    readonly property alias stateLoading : controlSettings.stateLoading
    readonly property alias stateAttention: controlSettings.stateAttention
    readonly property alias statePressed : controlSettings.statePressed
    readonly property alias stateError : controlSettings.stateError

    property alias settingsDelegate: settingsDelegate
    property alias settingsHighlight : settingsHighlight

    signal clicked(var model)

    property int columns : 0
    property alias model : view.model
    property alias view : view
    property alias delegate: view.delegate

    MCSettingRec {
        id: controlSettings
    }
    MCSettingRec {
        id: settingsTitle
    }
    MCSettingRec {
        id: settingsDelegate
    }
    MCSettingRec {
        id: settingsHighlight
    }

    MCRectangleState {
        id: recBackground
        settingBase: controlSettings
        state: control.state
        visible: true
        anchors.fill: parent
        anchors.topMargin: (itemLabel.visible)?itemLabel.height:0

        Item {
            id: itemLabel
            z:1
            anchors {
                verticalCenter: parent.top
                left : parent.left
                right: parent.right
            }

            height: MCMeasures.percByScreenHeight(4)

            MCRectangleState {
                id: recTitle
                anchors.left: parent.left
                anchors.leftMargin: MCMeasures.percByScreenHeight(1)
                visible: true
                state: control.state
                height: parent.height
                width: MCMeasures.percByScreenWidth(30)
                settingBase: settingsTitle
                MCLabelState {
                    id: labelTitle
                    state: parent.state
                    settingBase: settingsTitle
                    anchors.fill: parent
                    visible: true
                }
            }
        }

        Item {
            id: loading
            visible: control.showLoading
            anchors {
                fill        : parent
                topMargin   : (control.label.visible)?(itemLabel.height * 0.5):view.spacing
                leftMargin  : view.spacing
                rightMargin : view.spacing
                bottomMargin: view.spacing
            }

            BusyIndicator {
                height  : parent.height * 0.4
                width   : height
                running :  control.showLoading
                anchors.centerIn: parent
            }
        }

        Item {
            id: emptyState
            visible: (!control.showLoading) && (view.count <= 0)
            anchors {
                fill        : parent
                topMargin   : (control.label.visible)?(itemLabel.height * 0.5):view.spacing
                leftMargin  : view.spacing
                rightMargin : view.spacing
                bottomMargin: view.spacing
            }

            MCLabel {
                id: labelEmpty
                anchors.fill: parent
                horizontalAlignment: Qt.AlignHCenter
                wrapMode : Text.WordWrap
            }
        }

        MCViewGrid {
            id: view
            visible: (!loading.visible)
            currentIndex: -1
            settingBase: control.settings
            spacing: MCMeasures.percByScreenHeight(1)
            anchors {
                fill        : parent
                topMargin   : (control.label.visible)?(itemLabel.height * 0.5):view.spacing
                leftMargin  : view.spacing
                rightMargin : view.spacing
                bottomMargin: view.spacing
            }
            snapMode  : ListView.SnapOneItem
            cellHeight: MCMeasures.percByScreenHeight(10)
            cellWidth : view.width           
            delegate:
                Item {
                    clip  : true
                    width : view.cellWidth
                    height: view.cellHeight

                    MCRectangleState {
                        id: delegateItem
                        anchors.centerIn: parent
                        width   : view.cellWidth  * 0.9
                        height  : view.cellHeight * 0.9
                        visible : true
                        clip    : true
                        enabled : state !== stateInactived
                        settingBase: settingsDelegate
                        property bool focused: (view.currentIndex === model.index)
                        onFocusedChanged: {
                            state=focused?stateFocused: stringUtil.isEmptySet(model["state"], stateActived)
                        }
                        Component.onCompleted: {
                            state=model["state"];
                        }
                        MCLabelState {
                            text: stringUtil.ifThen(model[control.displayName],'')
                            settingBase: settingsDelegate
                            anchors.fill: parent
                            visible: true
                            state: parent.state
                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    view.currentIndex = model.index
                                    control.clicked(model)
                                }
                            }
                        }
                    }
                }
        }
    }

}

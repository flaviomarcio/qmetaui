import QtQuick 2.0

Item {
    id: control

    height: MCMeasures.densityPixel(50)

    property alias lineEdit: lineEdit

    property alias buttonSearch: buttonSearch
    property alias buttonBack: buttonBack

    signal backClicked()
    signal searchClicked()

    Item {
        anchors.margins: MCMeasures.densityPixel(2)
        anchors.fill: parent
        MCButtonState{
            id: buttonBack
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            state: {
                if(!control.enabled || !enabled)
                    return stateActived
                else if(focus)
                    return stateFocused
                else
                    return stateActived
            }
            width: {
                if(!visible)
                    return 0
                else
                    return height
            }
            visible: false
            onClicked: control.backClicked()
        }
        MCLineEdit{
            id: lineEdit
            state: {
                if(!control.enabled || !enabled)
                    return stateInactived
                else if(focus)
                    return stateFocused
                else
                    return stateActived
            }
            border.width: 0
            anchors.margins: MCMeasures.densityPixel(2)
            anchors.top: parent.top
            anchors.left: buttonBack.visible?buttonBack.right:parent.left
            anchors.right: buttonSearch.left
            anchors.bottom: parent.bottom
        }
        MCButtonState{
            id: buttonSearch
            state: {
                if(!control.enabled || !enabled)
                    return stateInactived
                else if(focus)
                    return stateFocused
                else
                    return stateActived
            }
            width: {
                if(!visible)
                    return 0
                else
                    return height
            }
            visible: false
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            onClicked: control.searchClicked()
        }
    }

}

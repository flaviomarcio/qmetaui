import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14
import QtReforce.Meta.Controls 0.0
import "qrc:/QMetaUI/Controls"

MCViewGrid{
    id:control

//    anchors.top: parent.top
//    anchors.left: parent.left
//    anchors.right: parent.right
//    anchors.bottom: parent.bottom

    signal cellClicked(variant cellIndex, variant cellData)

    function dynLoad(jsonObject){
        if(pvtGrid.jsonObject!==null){
            var jsonGridHeader=jsonObject["header"];
            var jsonGridDelegate=jsonObject["delegate"];
            if(pvtGrid.objectUtil.isDefined(jsonGridDelegate)){
                var jsonBody=jsonGridDelegate["body"];
                if(pvtGrid.objectUtil.isDefined(jsonBody)){
                    pvtGrid.data_cellWidth = jsonBody["cellWidth"];
                    pvtGrid.data_cellHeight = jsonBody["cellHeight"];
                    pvtGrid.data_color = jsonBody["color"];
                }

                pvtDelegate.data_component=jsonGridDelegate["component"]
            }
        }
    }

    cellHeight: pvtGrid.data_cellHeight
    cellWidth: pvtGrid.data_cellWidth

    delegate:gridDelegate

    MCItem{
        id:pvtGrid
        property int data_cellWidth: parent.width
        property int data_cellHeight: 0
        property color data_color: "transparent";
    }

    Item{
        id:pvtDelegate
        property variant data_component: null
    }

    MCLabel{
        id:labelBase
        anchors.fill: parent
        visible: false
    }

    Component{
        id: gridDelegate
        MCDelegateLabel {
            id:recRow
            width: control.cellWidth
            height: control.cellHeight
            label.text: "model.text"
        }
    }

}




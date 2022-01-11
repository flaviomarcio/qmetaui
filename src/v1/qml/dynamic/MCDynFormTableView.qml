import QtQuick 2.14
import QtQuick.Controls 2.14
import QtReforce.Meta.Controls 0.0
import Qt.labs.qmlmodels 1.0
import "qrc:/QMetaUI/Controls"

TableView {
    id: control
    clip: true

    signal cellClicked(var cellId, var cellData)

    property MCPaintPrivateItem privateItem: pvt

    MCHeader {
        id:columnsHeader
        visible: false
    }

    topMargin: columnsHeader.height;

    delegate: MCDelegateLabel{
        id : itemDelegate
        color : model.background
        label.color : model.foreground
        label.text : model.display
        width: control.columnWidthProvider(column)
        height: control.rowHeightProvider(column)
        label.horizontalAlignment : model.textAlignment
    }

    ScrollBar.horizontal: ScrollBar{}
    ScrollBar.vertical: ScrollBar{}

    ScrollIndicator.horizontal: ScrollIndicator {}
    ScrollIndicator.vertical: ScrollIndicator {}

    Item{
        id: pvtModel

        property MUModelTable tableModel: null

        MCListModel{
            id:repeatHeaderModel
            onLoaded: {
                repeatHeader.model=repeatHeaderModel
            }
        }

        function setModel(v){
            repeatHeader.model=undefined
            repeatHeaderModel.clear();
            if(objectUtil.isDefined(v)){
                tableModel=v
                var vModel=tableModel.columnSetting()
                repeatHeaderModel.setJsonObject(vModel);
                repeatHeader.model=repeatHeaderModel
            }
        }
    }

    Row {
        id: columnsHeaderR
        y: control.contentY
        z: 2
        Repeater {
            id: repeatHeader
            MCDelegateLabel {
                label.text : display
                Component.onCompleted: {
                    width= control.columnWidthProvider(column)
                    height= control.rowHeightProvider(column)
                }
            }
        }

    }

    onModelChanged: {
        pvtModel.setModel(control.model)
    }

}

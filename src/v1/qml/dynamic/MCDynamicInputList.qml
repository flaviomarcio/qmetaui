import QtQuick 2.14
import QtQuick.Controls 2.14
import QtReforce.Meta.Controls 0.0
import Qt.labs.qmlmodels 1.0
import "qrc:/QMetaUI/Controls"
import "qrc:/QMetaUI/Forms"

MCRectangleBase {
    id: control
    clip: true

    signal recordNew()
    signal recordEdit(string cellId)
    signal recordModify(string cellId, string cellData)
    signal recordRemove(string cellId)
    signal recordReload(string cellId)

    property string request_url_list
    property string request_url_item

    function dynLoad(jsonObject){
        if(objectUtil.isDefined(jsonObject)){
            var jsonForm=jsonObject["form"]
            if(objectUtil.isDefined(jsonForm)){
                dynHeader.dynLoad(jsonForm["header"])
            }

            var jsonGrid=jsonObject["grid"]
            if(objectUtil.isDefined(jsonGrid)){
                var jsonGridHeader=jsonGrid["header"]
                if(objectUtil.isDefined(jsonGridHeader)){
                    tableView.model=undefined
                    tableModel.setSetting(jsonGridHeader);
                    for (var i = 1; i <= 10; ++i) {
                        var s='linha numero: '+String(i);
                        var data={'desc':s , 'qtd':10};
                        tableModel.append(data);
                    }
                    tableView.model=tableModel
                }
            }
        }

    }

    MCItem{
        id:pvt
    }

    MCDynHeader{
        id:dynHeader
        anchors.margins: 1
        border.width: 10
    }

    MUModelTable{
        id: tableModel
    }

    MCDynFormTableView {
        id: tableView
        anchors.top: dynHeader.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        model: tableModel

        onModelChanged: {
            if(objectUtil.isDefined(tableModel)){
                tableView.headerSetting = tableModel.headerSetting()
                tableView.columnSetting = tableModel.columnSetting()
                tableView.rowSetting = tableModel.rowSetting()
            }
            else{
                tableView.headerSetting = null
                tableView.columnSetting = null
                tableView.rowSetting = null
            }
        }

        property var headerSetting: null
        property var columnSetting: null
        property var rowSetting: null

        columnWidthProvider: function (col) {
            var v = tableModel.columnWidth(col)
            v = paintState.geometry.calcWidth(v);
            return v;
        }

        rowHeightProvider: function (col) {
            var v = tableModel.rowHeight(col)
            v = paintState.geometry.calcHeight("5%");
            return v;
        }

        onCellClicked: {
            control.recordEdit(cellData)
        }

        function reloadRecord(){

        }
        function newRecord(){

        }
        function editRecord(){

        }
        function removeRecord(){

        }
    }
}

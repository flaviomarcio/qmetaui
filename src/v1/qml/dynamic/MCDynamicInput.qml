import QtQuick 2.14
import QtQuick.Controls 2.14
import "qrc:/QMetaUI/Controls"

MCRectangleBase {
    id:control
    clip: true

    property MCDynEngine engine: MCDynEngine{
        id:pvtEngine
        onLoaded: {
            pvt.dynLoad()
        }
    }

    property string request_url_list
    property string request_url_item
    property string request_url_item_delete
    property string request_url_item_modify

    Component.onCompleted: {
        pvt.push(inputList)
    }

    MCItem {
        id: pvt

        property Item activeControl: null

        function dynLoad(){
            var jsonObject = pvtEngine.jsonObject()

            var jsonInputList = jsonObject["list"]
            if(objectUtil.isDefined(jsonInputList)){
                inputList.dynLoad(jsonInputList)
            }

            //var jsonInputEdit = jsonObject["edit"]
            //if(objectUtil.isDefined(jsonInputEdit)){
            //    inputEdit.dynLoad(jsonInputEdit)
            //}

            var jsonInputEditLink = jsonObject["link"]
            if(objectUtil.isDefined(jsonInputEditLink)){
                control.request_url_list        = jsonInputEditLink["request_url_list"];
                control.request_url_item        = jsonInputEditLink["request_url_item"];
                control.request_url_item_delete = jsonInputEditLink["request_url_item_delete"];
                control.request_url_item_modify = jsonInputEditLink["request_url_item_modify"];
            }
        }

        function push(v){
            if(objectUtil.isDefined(pvt.activeControl)){
                pvt.activeControl.visible = false
                pvt.activeControl = v
            }

            if(objectUtil.isDefined(v)){
                pvt.activeControl = v
                pvt.activeControl.visible = true
            }
        }
    }

    MCDynamicInputList{
        id:inputList
        anchors.fill: parent

        request_url_list: control.request_url_list
        request_url_item: control.request_url_item

//        onRecordNew: inputEdit.newRecord()
//        onRecordEdit: inputEdit.editRecord(cellId)
//        onRecordModify: inputEdit.modifyRecord(cellId,cellData)
//        onRecordRemove: inputEdit.removeRecord(cellId)
//        onRecordReload: pvt.push(inputList)
    }

//    MCDynamicInputEdit{
//        id:inputEdit
//        anchors.fill: parent
//        request_url_item: control.request_url_item
//        request_url_item_delete: control.request_url_item_delete
//        request_url_item_modify: control.request_url_item_modify
//        visible: false

//        onRecordNew: pvt.push(inputEdit)
//        onRecordEdit: pvt.push(inputEdit)
//        onRecordSaved: pvt.push(inputList)
//        onRecordRemoved: pvt.push(inputList)
//        onRecordCancel: pvt.push(inputList)
//    }
}

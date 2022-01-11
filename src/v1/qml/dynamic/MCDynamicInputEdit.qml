import QtQuick 2.14
import QtQuick.Controls 2.14
import "qrc:/QMetaUI/Controls"
import "qrc:/QMetaUI/Forms"

MCDynFormBase {
    id: control

    frameHeader: null;
    MCDynHeader{
        id:dynHeader
        visible: false
    }

    property string option_uuid
    property string option_url

    signal recordLoad(string cellId)
    signal recordNew()
    signal recordEdit(string cellId)
    signal recordSaved(string cellId)
    signal recordRemoved(string cellId)
    signal recordCancel(string cellId)

    property string request_url_item
    property string request_url_item_delete
    property string request_url_item_modify

    function dynLoad(jsonObject){
        var jsonForm=jsonObject["form"]
        if(objectUtil.isDefined(jsonForm)){
            dynHeader.dynLoad(jsonForm["header"])
        }
    }

    function editRecord(cellId){
        control.recordEdit(cellId)
    }

    function newRecord(){
        var cellId=""
        control.recordNew(cellId)
    }

    function saveRecord(cellId){
        control.recordSaved(cellId)
    }

    function removeRecord(cellId){
        control.recordRemoved(cellId)
    }

    function modifyRecord(cellId, recorddata){
        control.recordModify(cellId)
    }

    MCItem{
        id:pvt
    }
}

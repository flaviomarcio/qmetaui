import QtQuick 2.15

ListModel {
    id: control

    signal loaded()

    property bool blockSignals: false

    property bool isEmpty: (count===0)

    property var jsonObject: undefined

    onJsonObjectChanged: {
        setJsonObject(jsonObject);
    }

    onRowsInserted: {
        if(!blockSignals)
            loaded()
    }

    function setJsonString(json){
        if(!objectUtil.isDefined(json))
            return control;
        else{
            control.setJsonObject(jsonObject)
        }
    }

    function setJsonObject(json){

        var aux=blockSignals;

        blockSignals=false;

        control.clear()

        for ( var i in json ){
            control.append(json[i]);
        }

        blockSignals=aux
        if(aux)
            control.loaded()


        if(!blockSignals)
            loaded()
        return control;
    }

    function requestPost(url, body){
        var xhr = new XMLHttpRequest;
        xhr.open("POST", body);
        xhr.onreadystatechange = function() {
            if (xhr.readyState === XMLHttpRequest.DONE)
                control.setJsonString(xhr.responseText)
        }
        xhr.send();
    }

    function requestGet(url, body){
        var xhr = new XMLHttpRequest;
        xhr.open("GET", source);
        xhr.onreadystatechange = function() {
            if (xhr.readyState === XMLHttpRequest.DONE)
                control.setJsonString(xhr.responseText)
        }
        xhr.send();
    }
}

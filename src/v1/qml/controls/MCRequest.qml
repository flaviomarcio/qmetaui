import QtQuick 2.0
import QtReforce.Meta.Network 0.0

Item {
    id: control

    signal requestStarted()
    signal requestSuccess()
    signal requestFinished()
    signal requestError(var message)
    signal clear()

    property var model: null
    property var body: null
    property MUServerLink link: pvt.link
    property alias request: request

    signal makeFakeData()

    property int count:0
    property bool isEmpty:true

    function execute(body){
        request.link=control.link
        request.setBody(body)
        return request.start()
    }

    onClear:{
        count=0
        isEmpty=true
        return request.clear()
    }

    Item {
        id: pvt
        property MUServerLink link
        onLinkChanged: {
            request.link=control.link
        }
    }

    MURequestModel {
        id: request

        onRequestStart:{
            control.requestStarted()
        }
        onRequestSuccess:{
            control.model=Qt.binding(function(){return request.model})
            control.count=request.model.rowCount()
            control.isEmpty=(request.count===0)
            control.requestSuccess()
        }

        onRequestFinished: {
            control.requestFinished()
        }

        onRequestFail: {
            snackBar.showError(message)
            control.requestError(message)
        }

        onRequestUnauthorized: {
            snackBar.showError(message)
            control.requestError(message)
        }
        onRequestError: {
            snackBar.showError(message)
            control.requestError(message)
        }

    }

}

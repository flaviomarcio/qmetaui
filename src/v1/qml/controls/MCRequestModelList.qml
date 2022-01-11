import QtQuick 2.0
import QtReforce.Meta.Network 0.0

Item {
    id: control

    property alias model: navigator.model
    property alias link: navigator.link
    property alias navigator: navigator

    property int count:0
    property bool isEmpty:true
    property bool isLoading:false

    signal makeFakeData()
    signal searchResponse(var body)
    signal searchDiscarted()
    signal searchStarted()
    signal changedHeaders()
    signal searchFinished()
    signal searchError(var message)

    function search(bodyFilter){
        control.isLoading=true
        return navigator.search(bodyFilter)
    }

    function clear(){
        count=0
        isEmpty=true
        return navigator.clear()
    }

    onLinkChanged: {
        if(objectUtil.isDefined(link))
            navigator.cacheFileName=link.hash
        else
            navigator.cacheFileName=""
    }

    MUModelNavigator {
        id: navigator
        link {
            onChangedHeaders: {
                control.changedHeaders()
            }
        }
        searchPageCount: -1
        searchRowCount : -1
        onSearchStarted: control.searchStarted()
        onSearchDiscarted: control.searchDiscarted()
        onSearchUnauthorized: navigator.showError(message)
        onSearchFail: navigator.showError(message)
        onSearchError: navigator.showError(message)
        onSearchResponse: {
            control.searchResponse(responseBody)
        }
        onSearchFinished: {
            control.isLoading=false
            navigator.setVar()
            control.searchFinished()
        }
        onLinkChanged: {
            navigator.setVar()
        }

        function showError(message){
            control.isLoading=false
            navigator.setVar()
            snackBar.showError(message)
            control.searchError(message)
        }
        function setVar(){
            control.count=navigator.model.rowCount()
            control.isEmpty=(control.count===0)
        }
    }

}

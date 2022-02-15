import QtQuick 2.14
import QtQuick.Controls 2.14

Item {
    id: control
    anchors.fill: parent

    property Component frameStart    : null
    property Component frameLogin    : null
    property Component frameRegister : null
    property Component frameHome     : null

    function showStart(){
        stackViewBase.pop(frameStart)
    }
    function showLogin(){
        stackViewBase.pop(frameLogin)
    }
    function showRegister(){
        stackViewBase.pop(frameRegister)
    }
    function showHome(){
        stackViewBase.pop(frameHome)
    }

    function show(){
        if(loginSession.isLogged()){
            showHome()
            return;
        }
        showStart()
    }

    StackView {
        id: stackViewBase
        anchors.fill: parent
    }
}

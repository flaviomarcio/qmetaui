import QtReforce.Meta.Controls 0.0
import QtQuick 2.14

Item {
    id: control

    function startTypePlaceholderText(type){
        if(type===MUFormType.Home)
            return qsTr("");
        else if(type===MUFormType.LoginEmail)
            return qsTr("Enter your email");
        else if(type===MUFormType.LoginSmartPhone)
            return qsTr("Enter your phone");
        else if(type===MUFormType.LoginDocument)
            return qsTr("Enter your document");
        else if(type===MUFormType.LoginUserName)
            return qsTr("Enter your username");
        else if(type===MUFormType.LoginEmailSmartPhone)
            return qsTr("Enter your email or phone");
        else
            return qsTr("Log in for authentication");



    }

}

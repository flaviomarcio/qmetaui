import QtReforce.Meta.Controls 0.0
import QtQuick 2.14

Item {
    id: control

    function startTypePlaceholderText(type){
        if(type===MUFormType.Home)
            return qsTr("");

        if(type===MUFormType.LoginEmail)
            return qsTr("Enter your email");

        if(type===MUFormType.LoginSmartPhone)
            return qsTr("Enter your phone");

        if(type===MUFormType.LoginDocument)
            return qsTr("Enter your document");

        if(type===MUFormType.LoginUserName)
            return qsTr("Enter your username");

        if(type===MUFormType.LoginEmailSmartPhone)
            return qsTr("Enter your email or phone");

        return qsTr("Log in for authentication");
    }

}

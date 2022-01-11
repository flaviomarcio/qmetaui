import QtReforce.Meta.Controls 0.0
import QtQuick 2.14
import QtQuick.Controls 2.14

MCFormBase {
    id: control
    property alias le: le

    signal make(int showType)
    signal loginStarted(string message)
    signal loginSuccessful(string message)
    signal loginUnsuccessful(string message)
    signal loginError(string message)
    signal loginFail(string message)
    signal loginMessage(string message)
    signal loginCancel()
    signal loginClear()
    signal loginMatch()
    signal loginNotMatch()
    signal loginCodeSent(string message)

    property string placeholderText: ""

    MCLoginEngine{
        id:le

        enabled: (control.enabled && control.visible)

        onLoginClear: {
            if(enabled)
                control.loginClear()
        }
        onLoginStarted: {
            if(enabled)
                control.loginStarted( message )
        }
        onLoginSuccessful: {
            if(enabled)control.loginSuccessful( message )
        }
        onLoginUnsuccessful: {
            if(enabled)
                control.loginUnsuccessful( message )
        }
        onLoginError: {
            if(enabled)
                control.loginError( message )
        }
        onLoginFail: {
            if(enabled)
                control.loginFail( message )
        }
        onLoginMessage: {
            if(enabled)
                control.loginMessage( message )
        }
        onLoginCancel: {
            if(enabled)
                control.loginCancel( message )
        }
        onLoginMatch: {
            if(enabled)
                control.loginMatch()}
        onLoginNotMatch: {
            if(enabled)
                control.loginNotMatch()
        }
        onLoginCodeSent:  {
            if(enabled)
                control.loginCodeSent(message)
        }
    }

    onMake:{
        control.placeholderText = control.e.startTypePlaceholderText(showType)
        control.open()
    }

    Component.onCompleted: {
        control.placeholderText=control.e.startTypePlaceholderText(control.e.STLoginEmailSmartPhone)
    }
}

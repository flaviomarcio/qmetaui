import QtQuick 2.14
import QtQuick.Controls 2.14
import "qrc:/QMetaUI/Controls"

Item {
    id: control

    enabled: true

    /**
     * @brief loginClear
     */
    signal loginClear();

    /**
     * @brief loginStarted
     * @param message
     * toda acao de request vai disparar aqui
     */
    signal loginStarted(var message);

    /**
     * @brief loginSuccessful
     * @param message
     * se a acao de autenticacao do usuário for bem feita vai disparar aqui
     */
    signal loginSuccessful(var message);

    /**
     * @brief loginUnsuccessful
     * @param message
     * se a acao de autenticacao do usuário falhar vai disparar aqui
     */
    signal loginUnsuccessful(var message);

    /**
     * @brief loginMatch
     * @param message
     * se verificar existencia de uma conta e encontrar vai disparar aqui
     */
    signal loginMatch(var message);

    /**
     * @brief loginNotMatch
     * @param message
     * se verificar existencia de uma conta e nao encontrar vai disparar aqui
     */
    signal loginNotMatch(var message);

    /**
     * @brief loginError
     * @param message
     * mensagem especifica de erro
     */
    signal loginError(var message);

    /**
     * @brief loginFail
     * @param message
     * mensagem especifica de fail
     */
    signal loginFail(var message);

    /**
     * @brief loginMessage
     * @param message
     * qualquer mensagem enviada vai disparar aqui
     */
    signal loginMessage(var message);

    /**
     * @brief loginCancel
     * informa quando a operacao foi cancelada
     */
    signal loginCancel();

    /**
     * @brief loginCodeSent
     * @param message
     * informa quando codigo foi enviado
     */
    signal loginCodeSent(var message);

    Item {
        id: pvt
        property string textAccount;
        property string textPassword;
        property string textCode;
    }

    function account_verify(textAccount){
        pvt.textAccount = textAccount
        loginEngine.account_verify(textAccount)
    }

    function account_autenticate(textAccount, textPhoneNumber){
        pvt.textAccount = textAccount
        loginEngine.account_autenticate(textAccount, textPhoneNumber)
    }

    function account_autenticate_password(textAccount, textPassword){
        pvt.textAccount = textAccount
        pvt.textPassword = textPassword
        loginEngine.account_autenticate_password(textAccount, textPassword)
    }

    function account_autenticate_code(code){
        pvt.textCode = code
        loginEngine.account_autenticate_code(pvt.textAccount, pvt.textCode)
    }

    Connections{
        id: loginEngineConnection
        target: enabled?loginEngine:null

        /**
         * @brief loginClear
         */
        function onLoginClear(){
            control.loginClear()
        }

        /**
         * @brief loginStarted
         * @param message
         * toda acao de request vai disparar aqui
         */
        function onLoginStarted(message){
            control.loginStarted(message)

        }

        /**
         * @brief loginSuccessful
         * @param message
         * se a acao de autenticacao do usuário for bem feita vai disparar aqui
         */
        function onLoginSuccessful(message){
            control.loginSuccessful(message)
        }

        /**
         * @brief loginUnsuccessful
         * @param message
         * se a acao de autenticacao do usuário falhar vai disparar aqui
         */
        function onLoginUnsuccessful(message){
            control.loginUnsuccessful(message)
        }

        /**
         * @brief loginMatch
         * @param message
         * se verificar existencia de uma conta e encontrar vai disparar aqui
         */
        function onLoginMatch(message){
            control.loginMatch(message)
        }

        /**
         * @brief loginNotMatch
         * @param message
         * se verificar existencia de uma conta e nao encontrar vai disparar aqui
         */
        function onLoginNotMatch(message){
            control.loginNotMatch(message)
        }

        /**
         * @brief loginError
         * @param message
         * mensagem especifica de erro
         */
        function onLoginError(message){
            control.loginError(message)
        }

        /**
         * @brief loginFail
         * @param message
         * mensagem especifica de fail
         */
        function onLoginFail(message){
            control.loginFail(message)
        }

        /**
         * @brief loginMessage
         * @param message
         * qualquer mensagem enviada vai disparar aqui
         */
        function onLoginMessage(message){
            control.loginMessage(message)
        }

        /**
         * @brief loginCancel
         * informa quando a operacao foi cancelada
         */
        function onLoginCancel(){
            control.loginCancel(message)
        }

        /**
         * @brief loginCodeSent
         * @param message
         * informa quando codigo foi enviado
         */
        function onLoginCodeSent(message){
            control.loginCodeSent(message)
        }

    }

}

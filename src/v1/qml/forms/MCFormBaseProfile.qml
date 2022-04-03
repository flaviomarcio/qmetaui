import QtQuick 2.14
import QtQuick.Controls 2.14
import QtReforce.Meta.Controls 0.0
import QtReforce.Meta.Network 0.0
import QtReforce.Meta.Security 0.0
import "qrc:/QMetaUI/Controls"

MCFormBase {
    id: control
    signal logoff()
    signal dataLoaded()
    signal dataSaved()

    signal requestStarted()
    signal requestFinished()

    property alias loginProfile  : loginProfile
    property bool  registerValid : false
    property bool  onlyLogged: false

    property string nameText       : ""
    property string emailText      : ""
    property string documentText   : ""
    property string phoneNumberText: ""
    property string dtBirthText    : ""

    onLoad: loginProfile.loadCurrentSession()
    onRequestStarted: control.state=stateLoading
    onRequestFinished : control.state=stateActived

    Component.onCompleted: {
        if (!onlyLogged){
            load()
            reqGet.execute()
        }
    }

    function dataLoad(){
        control.state=control.stateLoading
        reqGet.execute()
    }

    function check(){
        return loginProfile.isValid()
    }

    function dataSave(){
        control.forceActiveFocus()
        control.state=control.stateLoading

        let name         = control.nameText.trim()
        let email        = control.emailText.trim()
        let document     = stringUtil.toStrNumber(control.documentText.trim())
        let phone_number = stringUtil.toStrPhone(control.phoneNumberText.trim())
        let dt_birth     = dateUtil.toDate(control.dtBirthText.trim())
        let currentDate  = dateUtil.currentDate()

        if(!validationUtil.ptb.isName(name))
            snackBar.showMessage(qsTr("Necessário nome e sobrenome."))
        else if(!validationUtil.ptb.isCPF(document))
            snackBar.showMessage(qsTr("O CPF não é válido."))
        else if(!validationUtil.ptb.isEmail(email))
            snackBar.showMessage(qsTr("O email não é válido."))
        else if(!validationUtil.ptb.isPhoneNumber(phone_number))
            snackBar.showMessage(qsTr("O telefone não é válido."))
        else if( dt_birth >= currentDate )
            snackBar.showMessage(qsTr("Data de nascimento inválida."))
        else {

            loginProfile.name         = name
            loginProfile.email        = email
            loginProfile.document     = document
            loginProfile.phone_number = phone_number
            loginProfile.dt_birth     = dt_birth

            var body = loginProfile.toHash()
            reqSet.execute(body)
        }
    }

    MULoginProfile{
        id:loginProfile
    }

    Item {
        id: pvt
        property bool firstStart : false
    }

    MCRequest{
        id: reqGet
        link: hostingAclSession.account
        onRequestStarted: {
            control.requestStarted()
        }
        onRequestError: {
            control.state=control.stateActived
        }
        onRequestSuccess: {
/*
//TODO MOVER PARA LoginSession
//            var v=request.responseBodyMap();
//            if(!loginSession.setData(v)){
//                snackBar.showMessage(qsTr("Os dados da sessão não são validos"))
//            } else {
//            }
*/
            loginProfile.loadCurrentSession()
            if(pvt.firstStart){
                control.dataLoaded()
            }
            pvt.firstStart=true
            control.state=control.stateActived
            control.requestFinished()
        }
    }

    MCRequest {
        id: reqSet
        link: hostingAclSession.modify
        onRequestStarted: {
            control.requestStarted()
            control.state=control.stateLoading
        }
        onRequestError: {
            snackBar.showMessage(qsTr("Error ao salvar dados do cadastro."))
            control.state=control.stateActived
        }
        onRequestSuccess : {
            reqGetOnSet.execute()
        }
    }

    MCRequest {
        id: reqGetOnSet
        link: hostingAclSession.account
        onRequestStarted: {
            control.requestStarted()
            control.state=control.stateLoading
        }
        onRequestError: {
            control.state=control.stateActived
        }
        onRequestSuccess : {
            if(!loginSession.setData(request.responseBodyMap())){
                snackBar.showMessage(qsTr("Os dados da sessão não são validos"))
            }
            else {
                loginProfile.loadCurrentSession()
                if(pvt.firstStart){
                    control.dataLoaded()
                }
                pvt.firstStart=true
            }
            control.state=control.stateActived
            control.requestFinished()
            control.dataSaved()
        }
    }
}

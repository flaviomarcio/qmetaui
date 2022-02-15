import QtReforce.Meta.Controls 0.0
import QtQuick 2.14
import QtQuick.Controls 2.14
import "qrc:/QMetaUI/Controls"

Item {
    id: control
    anchors.fill: parent
    property bool  autoStart : false
    property alias frameStart : loaderStart.sourceComponent
    property alias frameLogin : loaderLogin.sourceComponent
    property alias frameRegister : loaderRegister.sourceComponent
    property alias frameHome : loaderHome.sourceComponent
    property MCSnackBar snackBar : null
    property MCMsgQuest messageQuestLogoff: null

    onSnackBarChanged: {
        if(snackBar!=__snackBar && (snackBar==null || snackBar==undefined)){
            __snackBar.load()
            return;
        }
        if(snackBar!==__snackBar.item){
            __snackBar.unload()
        }
        if(snackBar!=null || snackBar!=undefined)
            snackBar.parent=control
    }


    onMessageQuestLogoffChanged: {
        if(messageQuestLogoff!=__messsageQuestLogoff){
            if(messageQuestLogoff==null && messageQuestLogoff==undefined){
                __messsageQuestLogoff.load()
                return;
            }
        }
        if(messageQuestLogoff!==__messsageQuestLogoff.item){
            __messsageQuestLogoff.unload()
            if(messageQuestLogoff.text==="")
                messageQuestLogoff.text= qsTr("Deseja desconectar?")
        }

        if(messageQuestLogoff!=null)
            messageQuestLogoff.parent=control
        messageQuestLogoffConnection.target=control.messageQuestLogoff
    }

    Component.onCompleted: {
        pvt.formLoad()
    }

    function run(){
        if(loginSession.isLogged()){
            runFormShow.start()
            return;
        }
        if (objectUtil.isDefined(pvt.frameStart)){
            pvt.show(pvt.frameStart)
        } else {
            pvt.show(pvt.frameLogin)
        }
        runReInit.start()
    }

    function initObjects(){
        pvt.formLoad()
    }


    Connections{
        id: messageQuestLogoffConnection
        target: null
        function onAccepted(){
            loginSession.logoff()
        }
    }

    Item {
        id: formBody
        anchors.fill: parent
    }

    MCFormLoader{
        id: __snackBar
        sourceComponent: undefined
        onLoaded: {
            control.snackBar=__snackBar.item
        }
        Component {
            id: snackBarComponent
            MCSnackBar {
                startY: parent.y + parent.height
                endY  : startY - (parent.height * 0.3)
            }
        }
    }

    MCFormLoader{
        id: __messsageQuestLogoff
        sourceComponent: Component{
            MCMsgQuest{
                parent: control
                text: qsTr("Deseja desconectar?")
            }
        }
        onLoaded: {
            control.snackBar = __snackBar.item
            control.messageQuestLogoff = __messsageQuestLogoff.item
        }
    }

    MCFormLoader{
        id: loaderStart
        onLoaded: pvt.frameStart=form
        onUnloaded: pvt.frameStart=null
    }

    MCFormLoader{
        id: loaderLogin
        onLoaded: pvt.frameLogin=form
        onUnloaded: pvt.frameLogin=null
    }

    MCFormLoader{
        id: loaderRegister
        onLoaded: pvt.frameRegister=form
        onUnloaded: pvt.frameRegister=null
    }

    MCFormLoader{
        id: loaderHome
        onLoaded: pvt.frameHome=form
        onUnloaded: pvt.frameHome=null
    }

    MCItem {
        id: pvt

        property MCForm frameStart   : null
        property MCForm frameLogin   : null
        property MCForm frameRegister: null
        property MCForm frameHome    : null

        function show(frame){
            if(frame!==null && frame!==undefined){
                frame.parent=formBody
                frame.anchors.fill=frame.parent
                frame.open()
                frame.visible=true
                formBody.visible=true
            } else {
                formBody.visible=false
            }
        }

        function hide(obj) {
            if(obj!==null && obj!==undefined){
                obj.hide()
                obj.visible=false
            }
        }

        function formLoad(){
            if(control.snackBar==null)
                __snackBar.load()

            if(control.messageQuestLogoff==null)
                __messsageQuestLogoff.load()
            else
                messageQuestLogoffConnection.target=control.messageQuestLogoff

            if(loginSession.isLogged()){
                loaderHome.load()
                loaderStart.unload()
                loaderLogin.unload()
                loaderRegister.unload()
            } else {
                loaderHome.unload()
                loaderStart.load()
                loaderLogin.load()
                loaderRegister.load()
            }
        }

        function formUnload(){
            loaderStart.unload()
            loaderLogin.unload()
            loaderRegister.unload()
            loaderHome.unload()
        }

        function formHide(){
            hide(pvt.frameStart)
            hide(pvt.frameLogin)
            hide(pvt.frameRegister)
            hide(pvt.frameHome)
        }

        function formShow(){
            pvt.formHide()
            if(loginSession.isLogged())
                pvt.show(pvt.frameHome)
            else if(pvt.frameStart!=null)
                pvt.show(pvt.frameStart)
            else if(pvt.frameLogin!=null)
                pvt.show(pvt.frameLogin)
        }

        Connections {
            target: pvt.frameStart
            function onMake(showType){
                if ( showType === MUFormType.LoginSmartPhone )
                    pvt.show(pvt.frameLogin)
            }
        }

        Connections {
            target: pvt.frameLogin

            function onMake(showType){
                if ( showType === MUFormType.Register )
                    pvt.show(pvt.frameRegister)
            }

            function onHide(){
                pvt.show(pvt.frameStart)
            }

            function onLoginSuccessful(){
                snackBar.showMessage(qsTr("Autenticação concluída"))
                pvt.formLoad()
                runFormShow.start()
            }

            function onLoginCancel(){
                pvt.show(pvt.frameStart)
            }
        }

        Connections {
            target : pvt.frameRegister
            function onHide(){
                pvt.formLoad()
            }
        }
    }


    Connections{
        id: loginEngineConnection
        target: loginSession
        function onSessionUnLogged(){
            pvt.formUnload()
            pvt.formLoad()
            runFormShow.start()
        }

        function onSessionUnAuthorized(){
            loginEngine.account_session_verify()
        }
    }

    SequentialAnimation {
        id:runFormShow
        running: false
        property alias duration: runPause.duration
        PauseAnimation{id:runPause; duration: 100 }
        onFinished: pvt.formShow()
    }

    SequentialAnimation {
        id:runReInit
        running: false
        property int duration: 100
        PauseAnimation{ duration: 100 }
        onFinished: pvt.formLoad()
    }

}

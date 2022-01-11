import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14

MCRectangleBase {
    id: control

    signal show()
    signal hide()

    signal open()
    signal close()

    signal active ()

    signal reject ( var value )
    signal accept ( var value )

    signal finish      ()

    signal backPressed ( var event)

    property int index: -1

    Keys.onBackPressed: {        
        control.backPressed( event )
    }

    onAccept: {
        control.close()        
    }

    onReject: {
        control.close()
    }

    onFinish: {
        control.close()
    }

    onClose: {
        pvt.inheritsCloseForm()
    }

    onOpen: {
        pvt.inheritsOpenForm()
    }

    Item {
        id: pvt

        function inheritsOpenForm(){
            control.enabled=true
            control.visible=true
        }

        function inheritsCloseForm(){
            control.enabled=false
            control.visible=false
        }
    }
}

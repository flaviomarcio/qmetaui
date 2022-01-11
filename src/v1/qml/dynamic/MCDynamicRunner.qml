import QtQuick 2.14
import QtQuick.Controls 2.14
import "qrc:/QMetaUI/Controls"
import "qrc:/QMetaUI/Forms"

MCRectangle {
    id:control

    property alias engine: pvt.engine

    Component{
        id:dynamicInput
        MCDynamicInput{
            id:dynInput
            engine: parent.engine
            anchors.fill: parent
            Component.onCompleted: {
                dynReport.parent=recMaster
                dynReport.source=control.source
            }
        }
    }

    Component{
        id:dynamicInput
        MCDynamicReport{
            id:dynReport
            engine: parent.engine
            anchors.fill: parent
            Component.onCompleted: {
                dynReport.parent=recMaster
                dynReport.source=control.source
            }
        }
    }

    MCItem {
        id:pvt

        MCDynEngine{
            id:engine
        }
    }

    MCRectangle{
        id: recMaster
        anchors.fill: parent
        color: parent.color
    }



    Loader{
        id:loaderComponent

        onStatusChanged: {
            if(status===Loader.Ready){
                if(objectUtil.isDefined(loadedComponent.item)){
                    loaderComponent.item.source=control.source
                    loaderComponent.item.parent=recMaster
                    loadedComponent.item.anchors.fill=recMaster
                    loadedComponent.item.visible=true
                }
            }
            recMaster.visible=status===Loader.Ready
        }

    }

}

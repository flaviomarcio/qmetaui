import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14
import QtReforce.Meta.Controls 0.0

MCRectangleBase{
    id: control
    clip: true

    property bool clickOnLoading: false
    property bool loading: {return state===control.stateLoading}

    implicitHeight: 50//MCMeasures.densityPixel(30)
    implicitWidth: 50//MCMeasures.densityPixel(30)
    width: 50//MCMeasures.densityPixel(30)
    height: MCMeasures.densityPixel(50)


    property double imageHArea: 0.75
    property double imageWArea: 100

    color: "transparent"

    property Item  alignControl : null
    property alias display      : lbl.text
    property alias image        : img
    property alias label        : lbl
    property alias mouseArea    : mouse
    property alias text         : lbl.text
    property bool  selected     : false
    property int index          :0
    property string resourceName: ""

    signal clicked()


    Item {
        id: pvt

        function arrangeControls(){
            var lblText=String(lbl.text).trim()
            var imgSource=String(img.source).trim()

            var lblVisible=String(lblText).trim().length>0
            var imgVisible=String(imgSource).trim().length>0

            if(imgVisible && !lblVisible){
                img.anchors.top=undefined
                img.anchors.left=undefined
                img.anchors.right=undefined
                img.anchors.fill=control
            } else if(!imgVisible && lblVisible){
                lbl.anchors.top=undefined
                lbl.anchors.left=undefined
                lbl.anchors.right=undefined
                lbl.anchors.fill=control
            } else if( imgVisible && lblVisible){
                img.anchors.fill=undefined
                img.anchors.top=control.top
                img.anchors.left=control.left
                img.anchors.right=control.right
                img.height=control.height*control.imageHArea

                lbl.anchors.fill=undefined
                lbl.anchors.left=control.left
                lbl.anchors.right=control.right
                lbl.anchors.bottom=control.bottom
                lbl.height=(control.height-img.height)
            }
            img.visible=imgVisible
            lbl.visible=lblVisible
        }

    }

    MCImage {
        id: img
        clip: true
        radius: control.radius
        enabled: control.enabled
        source : ""
        onSourceChanged: pvt.arrangeControls()
        Component.onCompleted: {
            pvt.arrangeControls()
        }
    }

    MCLabel {
        id: lbl
        text: ""
    }

    MouseArea {
        id:mouse
        anchors.fill: parent
        onClicked: {
            if(control.state===control.stateLoading){
                if(control.clickOnLoading){
                    control.clicked()
                }
            }
            else{
                control.clicked()
            }
        }
    }
}

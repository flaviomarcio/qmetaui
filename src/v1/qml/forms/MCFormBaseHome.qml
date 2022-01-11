import QtQuick 2.14
import QtQuick.Controls 2.14

import "qrc:/QMetaUI/Forms"
import "qrc:/QMetaUI/Controls"

MCFormBase {
    id:control

    property bool frameAutoAlign: false

    property MCFormBaseAdsSale       frameAdsSale      : null
    property MCFormBaseChat          frameChat         : null
    property MCFormBaseContent       frameContent      : null
    property MCFormBaseNotify        frameNotify       : null
    property MCFormBaseProfile       frameProfile      : null
    property MCFormBaseProductDetail frameProductDetail: null
    property MCFormBaseShoppingCart  frameShoppingCart : null
    property MCFormBasePayment       framePayment      : null    
    property Item                    frameResumo       : null
    property Item                    frameStore        : null
    property Item                    frameAddress      : null
    property Item                    frameMenu         : null
    property Item                    frameSaleFinished : null
    property Item                    frameSearch       : null
    property Item                    frameBody         : null
    property Item                    frameFooter       : null

    onFrameAutoAlignChanged: {

        if(frameAutoAlign)
            cnnControl.target=control
        else
            cnnControl.target=null

        if(frameAutoAlign){
            pvt.__showBody(frameBody)
            pvt.__showFooter(frameFooter)
        }
    }

    Connections{
        id: cnnControl
        target: null
        function onFrameBodyChanged(){
            pvt.__showBody(frameBody)
        }
        function onFrameFooterChanged(){
            pvt.__showFooter(frameFooter)
        }
    }


    Item {
        id: pvt

        function __showBody(obj){
            hideBody()
            if (objectUtil.isDefined(obj)){
                frameBody = obj
                obj.parent=recBody
                obj.anchors.fill = recBody
                if (objectUtil.isDefined(obj.show)){
                    obj.show()
                }
            }
        }

        function __showFooter(obj){
            hideFooter()
            if (objectUtil.isDefined(obj)){
                frameFooter = obj
                recFooter.height=obj.height
                obj.parent = recFooter
                obj.anchors.fill=recFooter
                recFooter.height = Qt.binding(function() { return obj.height })
                obj.visible = true
                recFooter.visible=true
            }
        }

        function __hideBody (){
            if (objectUtil.isDefined(frameBody)){
                if (objectUtil.isDefined(frameBody.close))
                    frameBody.close()
                frameBody.anchors.fill = undefined
                frameBody.parent = control
                frameBody = null
            }
        }
        function __hideFooter(){
            if (objectUtil.isDefined(frameFooter)){
                frameFooter.visible = false
                frameFooter.anchors.fill = undefined
                frameFooter.parent = control
                recFooter.height = 0
                frameFooter = null
            }
        }

    }

    function showBody(obj){
        if(control.frameAutoAlign)
            frameBody = obj
        else
            pvt.__showBody(obj)
    }

    function showFooter(obj){
        if(control.frameAutoAlign)
            frameFooter = obj
        else
            pvt.__showFooter(obj)

    }

    function hideBody (){
        pvt.__hideBody()
    }

    function hideFooter(){
        pvt.__hideFooter()
    }


    Item  {
        id:recBody
        clip: true
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: recFooter.top
    }

    Item {
        id:recFooter
        z: recBody.z + 1000
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
    }
}

import QtQuick 2.14
import QtQuick.Controls 2.14

import "qrc:/QMetaUI/Controls"

MCFormBase {
    id: control
    property Rectangle frameHeader : null
    property Rectangle frameBody   : null
    property Rectangle frameBottom : null

    onFrameHeaderChanged: {
        pvt.changeAnchor()
    }

    onFrameBodyChanged: {
        pvt.changeAnchor()
    }

    onFrameBottomChanged: {
        pvt.changeAnchor()
    }

    MCItem{
        id: pvt
        property Rectangle frameHeader : null
        property Rectangle frameBody : null
        property Rectangle frameBottom : null

        function changeAnchor(){
            if(objectUtil.isDefined(frameHeader)){
                if(objectUtil.isDefined(pvt.frameHeader)){
                    pvt.frameHeader.visible=false
                    pvt.frameHeader.anchors.fill=undefined
                    pvt.frameHeader.parent=undefined
                }
            }

            if(objectUtil.isDefined(pvt.frameBody)){
                if(objectUtil.isDefined(pvt.frameBody)){
                    pvt.frameBody.visible=false
                    pvt.frameBody.anchors.fill=null
                    pvt.frameBody.parent=null
                }
            }


            if(objectUtil.isDefined(pvt.frameBottom)){
                if(objectUtil.isDefined(pvt.frameBottom)){
                    pvt.frameBottom.anchors.fill=undefined
                    pvt.frameBottom.parent=null
                    pvt.frameBottom.visible=false
                }
            }

            pvt.frameHeader= control.frameHeader
            pvt.frameBody = control.frameBody
            pvt.frameBottom = control.frameBottom

            if(!objectUtil.isDefined(pvt.frameHeader)){
                recHeader.height=0
            }
            else{
                pvt.frameHeader.parent=recHeader
                pvt.frameHeader.anchors.top=recHeader.top
                pvt.frameHeader.anchors.left=recHeader.left
                pvt.frameHeader.anchors.right=recHeader.right
                pvt.frameHeader.visible=true
                recHeader.height=pvt.frameHeader.height
                recHeader.visible=true
            }

            if(!objectUtil.isDefined(pvt.frameBody)){
                recBody.height=0
            }
            else{
                pvt.frameBody.parent=recBody
                pvt.frameBody.anchors.fill=recBody
                pvt.frameBody.visible=true
                recBody.visible=true
            }

            if(!objectUtil.isDefined(pvt.frameBottom)){
                recBottom.height=0
            }
            else{
                pvt.frameBottom.parent=recBottom
                pvt.frameBottom.anchors.margins=0
                pvt.frameBottom.anchors.left=recBottom.left
                pvt.frameBottom.anchors.right=recBottom.right
                pvt.frameBottom.anchors.bottom=recBottom.bottom
                pvt.frameBottom.visible=true
                recBottom.height=pvt.frameBottom.height
                recBottom.visible=true
            }
        }
    }

    Rectangle{
        id:recHeader
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        color: parent.color
        clip: false
        height: 100
        visible: height>0
    }

    Rectangle{
        id:recBody
        anchors.top: recHeader.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: recBottom.top
        clip: false
        color: parent.color
        visible: height>0
    }

    Rectangle{
        id:recBottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
    }

}

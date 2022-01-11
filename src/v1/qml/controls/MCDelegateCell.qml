import QtQuick 2.14
import QtQuick.Window 2.2

MCRectangleBase {
    id: control

    property Item delegateControl: null

    color: pvt.pvtColor
    onColorChanged: color=pvt.pvtColor

    onDelegateControlChanged: {

        if(objectUtil.isDefined(pvt.item))
            if(pvt.item!=delegateControl)
                pvt.item.visible=false

        pvt.item=null

        if(objectUtil.isDefined(control.delegateControl)){
            pvt.item=control.delegateControl
            pvt.item.anchors.fill=control
            pvt.item.parent=control
            pvt.item.visible=true
        }
    }

    MCItem{
        id: pvt
        property Item item: null
        readonly property color pvtColor:"transparent"
    }

    MCHSeparator{
        anchors.left: parent.left
    }

    MCHSeparator{
        anchors.left: parent.right
    }

    MCHSeparator{
        anchors.left: parent.left
    }

    MCHSeparator{
        anchors.left: parent.right
    }
}

import QtQuick 2.14

MCButton {
    id:control
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    onAlignControlChanged: {
        if(!privateItem.objectUtil.isDefined(alignControl))
            control.anchors.right = undefined
        else if(alignControl===control.parent)
            control.anchors.right = alignControl.right
        else
            control.anchors.right = alignControl.left
    }

}

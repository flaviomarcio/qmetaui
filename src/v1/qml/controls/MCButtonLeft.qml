import QtQuick 2.14

MCButton {
    id:control
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    onAlignControlChanged: {
        if(!privateItem.objectUtil.isDefined(alignControl))
            control.anchors.left = undefined
        else if(alignControl===control.parent)
            control.anchors.left = alignControl.left
        else
            control.anchors.left = alignControl.right
    }
}

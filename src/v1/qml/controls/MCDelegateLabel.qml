import QtQuick 2.0

MCDelegateCell {
    id: control
    property alias label : label
    delegateControl: MCLabelBase {
        id:label
        anchors.fill: parent
    }
}

import QtQuick 2.14
import QtQuick.Controls 2.14

MCMsg{
    id: control
    title: qsTr("Warning message")
    function open(){
        control.accepted()
    }
}

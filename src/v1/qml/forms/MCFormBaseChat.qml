import QtQuick 2.14
import QtQuick.Controls 2.14

MCFormBase {
    id: control
    signal messageSent(variant value)
    signal messageReceived(variant value)

    function check(value){
        return false;
    }
}

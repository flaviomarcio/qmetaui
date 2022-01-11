import QtQuick 2.14
import QtQuick.Controls 2.14

MCFormBase {
    id: control
    signal paymentSuccess(variant filter)
    signal paymentCancel()
    signal paymentFail()

    function check(value){
        return false;
    }
}

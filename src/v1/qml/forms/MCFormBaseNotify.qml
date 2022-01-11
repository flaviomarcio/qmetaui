import QtQuick 2.14
import QtQuick.Controls 2.14

MCFormBase {
    id: control
    signal notify(variant value)

    function check(filter){
        return false;
    }
}

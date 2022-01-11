import QtQuick 2.14
import QtQuick.Controls 2.14

MCFormBase {
    id: control
    signal search(variant filter)
    signal requestRows(variant filter)
    signal requestAdsSale(variant value)
    signal saleItemChanged(variant filter)
    signal finishSale()
    function check(value){
        return false;
    }
}

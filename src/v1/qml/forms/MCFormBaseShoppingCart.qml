import QtQuick 2.14
import QtQuick.Controls 2.14

MCFormBase {
    id: control
    property alias framePayment: pvt.framePayment

    signal requestUpdate()
    signal requestAdsSale(variant value)
    signal finishSale()

    Item {
        id: pvt
        property MCFormBasePayment framePayment: null
    }
}

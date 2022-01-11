import QtQuick 2.14

Item {

    property alias header : pvtHeader
    property alias body : pvtHeader

    ListModel{
        id: pvtHeader
    }

}

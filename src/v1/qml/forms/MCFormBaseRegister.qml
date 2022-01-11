import QtQuick 2.14
import QtQuick.Controls 2.14

//import "qrc:/QMetaUI/Engine"

MCFormBase {
    id: control

    signal make(int showType)

    property string placeholderText: ""

    onMake:{
        control.open()
    }
}

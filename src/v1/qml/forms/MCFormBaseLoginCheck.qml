import QtQuick 2.14
import QtQuick.Controls 2.14

MCFormBase {
    id: control
    signal loginSuccessful
    signal loginFail
    signal loginCancel
    signal make(int showType)

    onMake:{
        control.open()
    }
}

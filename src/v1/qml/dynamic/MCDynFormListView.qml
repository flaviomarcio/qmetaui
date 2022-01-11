import QtQuick 2.14
import QtQuick.Window 2.2
import "qrc:/QMetaUI/Controls"

MCDynFormBase {
    id: control

    color: prp.data_color

    property alias buttons: prp.data_buttons

    signal clicked(int index, variant data)

    Item {
        id: pvt
    }

    Item {
        id: prp
        property string data_title : "";
        property variant data_buttons: null
        onData_buttonsChanged: pvt.changeBody()
    }

    function dynLoad(jsonObject){
        prp.data_title          = jsonObject["title"            ];
        prp.data_buttons        = jsonObject["buttons"          ];
        pvt.changeBody()

    }

    MCHeader{
        id: recHeader
        label.text: prp.data_title
    }

    MCRectangle{
        id: recButton
        anchors.top: recHeader.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        visible: true
        function changeModel(){
            if(modelButtons.count===0){
                modelButtons.setJsonObject(prp.data_buttons)
            }

            if(modelButtons.count===0)
                recButton.visible=false
            else
                recButton.visible=true

            if(recButton.visible)
                recButton.height=recHeader.height
            else
                recButton.height=0

            control.height=(recHeader.height+recButton.height)

        }
        MCViewList{
            id:viewList

            anchors.fill: parent
            model: MCDynListModel{
                id: modelButtons
            }
            orientation: ListView.Horizontal
            delegate: MCRectangle{
                id:cellRec
                color: "transparent"
                width: height*2
                height: viewList.height
                MCButton{
                    id:cellButton
                    anchors.fill: parent
                    index: model.index
                    label.text: model.text
                    label.visible: true

                    onClicked: {
                        var data=model
                        control.clicked(data.index, data)
                    }
                }
            }
        }
    }
}

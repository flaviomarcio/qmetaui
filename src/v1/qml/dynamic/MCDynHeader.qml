import QtQuick 2.14
import QtQuick.Window 2.2
import "qrc:/QMetaUI/Controls"

MCRectangleBase {
    id: control

    readonly property alias modelColumn: modelRepeat


    signal clicked(int index, variant data)

    function widthColumn(w){
        return pvt.widthReal(w);
    }

    onWidthChanged: pvt.changeAll=Date.now()

    MCItem {
        id: pvt
        property variant changeAll: Date.now()

        function widthReal(w){
            if(objectUtil.isDefined(control.paintState))
                w=control.paintState.geometry.calcWidth();
            return w
        }

        function changeBody(){
            modelRepeat.setJsonObject(prp.data_columns)
            if(modelRepeat.count>0 && objectUtil.isDefined(control.paintState))
                control.height=control.paintState.geometry.calcHeight()
            else
                control.height=0
        }
    }

    Item {
        id: prp

        property string data_title:"";
        property variant data_columns: null
    }

    function dynLoad(jsonObject){
        prp.data_title          = jsonObject["title"            ];
        prp.data_columns        = jsonObject["columns"          ];

        repeat.model=modelRepeat.setJsonObject(prp.data_columns)
        pvt.changeBody()

    }

    Rectangle{
        id: recRepeat
        anchors.fill: parent
//        anchors.top: parent.top
//        anchors.left: parent.left
//        anchors.right: parent.right
//        anchors.bottom: parent.bottom
          onWidthChanged: forceUpdate=Date.now()


        property var forceUpdate: pvt.forceUpdate


        MCDynListModel{
            id: modelRepeat
        }

        Grid {
            id: flow
            spacing: 1
            rows: 1
            anchors.fill: parent
            Repeater{
                id:repeat

                MCButtonToolBar{
                    id:recCell
                    parent: recRepeat
                    height: parent.height

                    property var forceUpdate: recRepeat.forceUpdate

                    width: height*2

                    anchors.leftMargin: 2

                    label.text: display
                    label.visible: true
                    MCHSeparator{
                        id:recSeparatorLeft
                        anchors.left: parent.left
                    }
                    MCHSeparator{
                        id:recSeparatorRight
                        anchors.right: parent.right
                    }
                }
            }

        }


        MCVSeparator{
            id:recVSeparator1
            anchors.top: parent.top
        }
        MCVSeparator{
            id:recVSeparator2
            anchors.bottom: parent.bottom
        }

    }
}

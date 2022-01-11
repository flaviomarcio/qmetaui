import QtQuick 2.14

MCPaintPrivateItem{
    id:pvt

    function changeVisible(){
        if(image.visible)
            lbl.anchors.top = parent.top
        else
            lbl.anchors.top = img.bottom
    }
    function resourceLoad(){

    }


}

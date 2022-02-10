import QtQuick 2.15
import QtReforce.Meta.Controls 0.0

MouseArea{
    id:mouseControl
    anchors.fill: parent

    readonly property alias captured: pvt.captured
    readonly property alias captureResouce: pvt.captureResouce

    property int captureWidth:100
    property int captureHeight:50

    signal captureStarted()
    signal captureFinished()
    signal capturePosition(int x, int y)

    Item {
        id: pvt
        property bool captured: false
        property string captureResouce:""
    }

    function calc(){
        if(!pvt.captured)
            return;
        let aXDec=captureWidth/2
        let aYDec=captureHeight/2
        let aX=mouseControl.mouseX-aXDec
        let aY=mouseControl.mouseY-aYDec
        capturePosition(aX, aY)
        printScreen.screenShot(aX, aY, captureWidth, captureHeight)
    }

    onPressed: {
        printScreen.printCapture()
        pvt.captured=true
        mouseControl.captureStarted()
        calc()
    }
    onReleased: {
        pvt.captured=false
        mouseControl.captureFinished()
        printScreen.printRelease()
    }
    onPositionChanged: {
        calc()
    }
    MUImageCaptureArea{
        id: printScreen
        onResource: pvt.captureResouce=fileName
    }
}

import QtQuick 2.15
import QtReforce.Meta.Controls 0.0

MouseArea{
    id:control
    anchors.fill: parent

    readonly property alias captured: pvt.captured
    readonly property alias captureResouce: pvt.captureResouce

    property int captureWidth:100
    property int captureHeight:50

    signal captureStarted()
    signal captureFinished()
    signal capturePosition(int x, int y)

    function calc(){
        if(!pvt.captured)
            return;
        let aXDec=captureWidth/2
        let aYDec=captureHeight/2
        let aX=control.mouseX-aXDec
        let aY=control.mouseY-aYDec
        capturePosition(aX, aY)
        imageCaptureArea.captureScreenShot(aX, aY, captureWidth, captureHeight)
    }

    onPressed: {
        imageCaptureArea.captureScreen()
        pvt.captured=true
        calc()
        control.captureStarted()
    }
    onReleased: {
        pvt.captured=false
        control.captureFinished()
        imageCaptureArea.captureRelease()
    }
    onPositionChanged: calc()


    Item {
        id: pvt
        property bool captured: false
        property string captureResouce:""
    }

    MUImageCaptureArea{
        id: imageCaptureArea
        onResource: pvt.captureResouce=fileName
    }
}

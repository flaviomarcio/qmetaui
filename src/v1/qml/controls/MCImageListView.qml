import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14

MCRectangle {
    id: control

    color: "transparent"

    signal bannerClicked(var index);
    property alias model: listView.model;
    property alias delegate: listView.delegate;
    property alias listView: listView

    ListView {
        id:listView
        anchors.fill   : parent
        currentIndex   : pageIndicator.currentIndex
        snapMode       : ListView.SnapOneItem
        orientation    : ListView.Horizontal
        boundsBehavior : Flickable.StopAtBounds
        highlightRangeMode : ListView.StrictlyEnforceRange

        preferredHighlightBegin: 0
        preferredHighlightEnd  : 0
        highlightMoveVelocity  : -1
        highlightMoveDuration  : 0

        maximumFlickVelocity   : {
            let base = ( listView.orientation === ListView.Horizontal ? width : height )
            return 2 * base
        }

        cacheBuffer: {
            let base = ( listView.orientation === ListView.Horizontal ? width : height )
            if(control.count <= 0)
                return 0
            return (control.count -1) * base
        }
    }
    PageIndicator {
        id: pageIndicator
        interactive: true
        count: listView.count
        currentIndex: listView.currentIndex
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Component{
        id: delegateItem
        Rectangle {
            id: labelItem
            color: "transparent"
            width: listView.width
            height: listView.height
            implicitWidth : control.implicitWidth
            implicitHeight: control.implicitHeight
            MCLabel {
                anchors.fill: parent
                text: model.display
                wrapMode: Text.WordWrap
            }
            MCImage {
                id: imagePro
                anchors.centerIn: parent
                visible  : enabled
                enabled  : (status === Image.Ready)
                fillMode : Image.PreserveAspectCrop
                asynchronous: true
                width : parent.width
                height: parent.height
                sourceSize.width : width
                sourceSize.height: height
                source: model.image
            }
            MouseArea {
                anchors.fill: parent
                z:1
                onClicked: control.bannerClicked(model.index)
            }
        }
    }

    //Component.onCompleted: listView.delegate=delegateItem

}

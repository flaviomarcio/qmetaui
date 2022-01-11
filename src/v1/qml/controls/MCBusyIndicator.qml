import QtQuick 2.14
import QtQuick.Controls 2.14

BusyIndicator {

    id: control

    property real baseSize: MCMeasures.percByScreenHeight(55)
    property color color: "lightgray"

    running: false
    visible: running

    contentItem:
        Item {
        id:baseIndicator


        implicitWidth : control.baseSize
        implicitHeight: control.baseSize

        Item {
            id: item
            x: (parent.width * 0.5) - control.baseSize * 0.5
            y: (parent.height* 0.5) - control.baseSize * 0.5

            width : control.baseSize
            height: control.baseSize

            opacity: control.running ? 1 : 0

            Behavior on opacity {
                OpacityAnimator {
                    duration: 250
                }
            }

            RotationAnimator {
                target: item
                running: control.visible && control.running
                from: 0
                to: 360
                loops: Animation.Infinite
                duration: 1250
            }

            Repeater {
                id: repeater
                model: 6
                Rectangle {
                    id:innerItem
                    x: (item.width  * 0.5)
                    y: (item.height * 0.5)
                    color: control.color
                    implicitWidth : item.width * 0.2
                    implicitHeight: item.height* 0.2
                    radius: implicitHeight * 0.5
                    transform: [
                        Translate {
                            y: -Math.min(item.width, item.height) * 0.5 +innerItem.implicitWidth * 0.5
                        },
                        Rotation {
                            angle: index / repeater.count * 360
                        }
                    ]
                }
            }
        }
    }
}

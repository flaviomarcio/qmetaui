/*
 * QML Material - An application framework implementing Material Design.
 *
 * Copyright (C) 2014-2016 Michael Spencer <sonrisesoftware@gmail.com>
 *               2014 Marcin Baszczewski
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

import QtQuick 2.14
import QtGraphicalEffects 1.0
import "qrc:/QMetaUI/Controls"


MouseArea {
    id: view
    hoverEnabled: true
    clip: true

    property int startRadius: circular ? width/10: width/6
    property int endRadius
    property int parentRadius: 0//height * 0.5


    property color color//: focusBackground.color
    property real radius//: focusBackground.radius

    property bool circular: false
    property bool centered: false

    property int focusWidth: width - MCMeasures.densityPixel(32)
    property bool  focused
    property color focusColor: "transparent"


    property bool showFocus: true

    onPressed: {
        pvt.createTapCircle(mouse.x, mouse.y)
    }

    onCanceled: {
        pvt.lastCircle.removeCircle();
    }

    onReleased: {
        pvt.lastCircle.removeCircle();
    }


    Item {
        id: pvt
        property Item lastCircle
        function createTapCircle(x, y) {
            endRadius = centered ? width/2 : pvt.radius(x, y)
            showFocus = false

            pvt.lastCircle = tapCircle.createObject(view, {
                                                           "circleX": centered ? width/2 : x,
                                                           "circleY": centered ? height/2 : y
                                                       });
        }

        function radius(x, y) {
            var dist1 = Math.max(pvt.dist(x, y, 0, 0), pvt.dist(x, y, width, height))
            var dist2 = Math.max(pvt.dist(x, y, width, 0), pvt.dist(x, y, 0, height))

            return Math.max(dist1, dist2)
        }

        function dist(x1, y1, x2, y2) {
            var xs = 0;
            var ys = 0;

            xs = x2 - x1;
            xs = xs * xs;

            ys = y2 - y1;
            ys = ys * ys;

            return Math.sqrt( xs + ys );
        }
    }


    Component {
        id: tapCircle

        Item {
            id: circleItem

            anchors.fill: parent

            property bool done

            function removeCircle() {
                done = true

                if (fillSizeAnimation.running) {
                    fillOpacityAnimation.stop()
                    closeAnimation.start()

                    circleItem.destroy(500);
                } else {
                    showFocus = true
                    fadeAnimation.start();

                    circleItem.destroy(300);
                }
            }

            property real circleX
            property real circleY

            property bool closed

            Item {
                id: circleParent
                anchors.fill: parent
                visible: !circular
                clip: true

                Rectangle {
                    id: circleRectangle

                    x: circleItem.circleX - radius
                    y: circleItem.circleY - radius

                    width: radius * 2
                    height: radius * 2

                    opacity: 0
                    color: view.color

                    radius: control.radius
                    clip: true

                    NumberAnimation {
                        id: fillSizeAnimation
                        running: true

                        target: circleRectangle; property: "radius"; duration: 500;
                        from: startRadius; to: endRadius; easing.type: Easing.InOutQuad

                        onStopped: {
                            if (done)
                                showFocus = true
                        }
                    }

                    NumberAnimation {
                        id: fillOpacityAnimation
                        running: true

                        target: circleRectangle; property: "opacity"; duration: 300;
                        from: 0; to: 1; easing.type: Easing.InOutQuad
                    }

                    NumberAnimation {
                        id: fadeAnimation

                        target: circleRectangle; property: "opacity"; duration: 300;
                        from: 1; to: 0; easing.type: Easing.InOutQuad
                    }

                    SequentialAnimation {
                        id: closeAnimation

                        NumberAnimation {
                            target: circleRectangle; property: "opacity"; duration: 250;
                            to: 1; easing.type: Easing.InOutQuad
                        }

                        NumberAnimation {
                            target: circleRectangle; property: "opacity"; duration: 250;
                            from: 1; to: 0; easing.type: Easing.InOutQuad
                        }
                    }
                }
            }

            Item {
                id: item
                source: circleParent
                anchors.fill: parent
                visible: circular

                property alias source: mask.source

                Rectangle {
                    id: circleMask
                    anchors.fill: parent
                    smooth : true
                    visible: false
                    radius: view.parentRadius
                }

                OpacityMask {
                    id: mask

                    anchors.fill: parent
                    maskSource: circleMask
                }
            }

        }
    }
}

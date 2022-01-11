import QtQuick 2.14
import QtQuick.Controls 2.14

Item {
    id:control
    height: MCMeasures.densityPixel(30)
    width: MCMeasures.densityPixel(100)

    border{
        width: 1
        color: "gray"
    }

    signal enterPressed()

    onFocusChanged: {
        lineEdit.focus=false
        if(focus){
            lineEdit.focus=true
            lineEdit.forceActiveFocus()
        }
        labelPlaceHolder.changeVisible()
    }

    property Item forwardFocus: null

    function forwardNext(item){
        if(item===null || item===undefined)
            item=control.forwardFocus

        if(!(item===null || item===undefined)){
            item.focus=true
            item.forceActiveFocus()
        }
    }

    property alias labelCaption: labelCaption
    property alias labelPlaceHolder: labelPlaceHolder
    property alias placeholderText : labelPlaceHolder.text
    property alias lineEdit: lineEdit
    property alias textEditBox: lineEdit
    property alias background: recBackground
    property alias lineBottom: lineBottom
    property alias radius: recBackground.radius
    property alias border: recBackground.border

    activeFocusOnTab: true
//    activeFocusOnPress: false

//    property alias acceptableInput                      : lineEdit.acceptableInput
//    property alias activeFocusOnPress                   : lineEdit.activeFocusOnPress
//    property alias autoScroll                           : lineEdit.autoScroll
//    property alias bottomPadding                        : lineEdit.bottomPadding
//    property alias canPaste                             : lineEdit.canPaste
//    property alias canRedo                              : lineEdit.canRedo
//    property alias canUndo                              : lineEdit.canUndo
//    property alias color                                : lineEdit.color
//    property alias contentHeight                        : lineEdit.contentHeight
//    property alias contentWidth                         : lineEdit.contentWidth
//    property alias cursorDelegate                       : lineEdit.cursorDelegate
//    property alias cursorPosition                       : lineEdit.cursorPosition
//    property alias cursorRectangle                      : lineEdit.cursorRectangle
//    property alias cursorVisible                        : lineEdit.cursorVisible
//    property alias displayText                          : lineEdit.displayText
//    property alias echoMode                             : comboContentItem.echoMode
//    property alias effectiveHorizontalAlignment         : lineEdit.effectiveHorizontalAlignment
    property alias font                                 : comboContentItem.font
    property alias horizontalAlignment                  : comboContentItem.horizontalAlignment
//    property alias inputMask                            : lineEdit.inputMask
//    property alias inputMethodComposing                 : lineEdit.inputMethodComposing
//    property alias inputMethodHints                     : lineEdit.inputMethodHints
//    property alias leftPadding                          : lineEdit.leftPadding
    property int length                               : 0//lineEdit.length
    property int maximumLength                        : 0//lineEdit.maximumLength
//    property alias mouseSelectionMode                   : lineEdit.mouseSelectionMode
//    property alias overwriteMode                        : lineEdit.overwriteMode
//    property alias padding                              : lineEdit.padding
//    property alias passwordCharacter                    : lineEdit.passwordCharacter
//    property alias passwordMaskDelay                    : lineEdit.passwordMaskDelay
//    property alias persistentSelection                  : lineEdit.persistentSelection
//    property alias preeditText                          : lineEdit.preeditText
//    property alias readOnly                             : lineEdit.readOnly
//    property alias renderType                           : lineEdit.renderType
//    property alias rightPadding                         : lineEdit.rightPadding
//    property alias selectByMouse                        : lineEdit.selectByMouse
//    property alias selectedText                         : lineEdit.selectedText
//    property alias selectedTextColor                    : lineEdit.selectedTextColor
//    property alias selectionColor                       : lineEdit.selectionColor
//    property alias selectionEnd                         : lineEdit.selectionEnd
//    property alias selectionStart                       : lineEdit.selectionStart
    property alias text                                 : lineEdit.currentText
    property alias textEdit                             : lineEdit.currentText
//    property alias topPadding                           : lineEdit.topPadding
//    property alias validator                            : lineEdit.validator
    property alias verticalAlignment                    : comboContentItem.verticalAlignment
    property alias wrapMode                             : comboContentItem.wrapMode

    signal textEdited()
    signal accepted()
    signal editingFinished()

    Item {
        id: pvt
        property Rectangle background: {
            if(control.background===null || control.background===undefined)
                return recBackground
            else
                return control.background
        }
    }

    onBackgroundChanged: {
        pvt.background.parent=itemText
        pvt.background.anchors.fill=pvt.background.parent
    }

    onEnabledChanged: {
        control.background.enabled=control.enabled
    }

    function copy(){
        lineEdit.copy()
    }

    function past(){
        lineEdit.paste()
    }

    function cut(){
        lineEdit.cut()
    }

    function clear(){
        lineEdit.clear()
    }


    function deselect(){
        return lineEdit.deselect()
    }

    function ensureVisible(position){
        return lineEdit.ensureVisible(position)
    }

    function getText(start, end){
        return lineEdit.insert(start, end)
    }

    function insert(position, text){
        return lineEdit.insert(position, text)
    }

    function isRightToLeft(start, end){
        return lineEdit.isRightToLeft(start, end)
    }

    function moveCursorSelection(position, mode){
        return lineEdit.moveCursorSelection(position, mode)
    }

    function positionAt(x, y, position){
        return lineEdit.positionAt(x,y,position)
    }

    function redo(){
        return lineEdit.redo()
    }

    function remove(start, end){
        return lineEdit.remove(start, end)
    }

    function select(start, end){
        return lineEdit.select(start, end)
    }

    function selectAll(){
        return lineEdit.selectAll();
    }

    function selectWord(){
        return lineEdit.selectWord();
    }

    function undo(){
        return lineEdit.undo();
    }

    Text{
        id: labelCaption
        parent: pvt.background
        anchors{
            left: parent.left
            right: parent.right
            bottom: parent.top
        }
        wrapMode: Text.NoWrap

        onVisibleChanged: background.clip=false

        enabled: control.enabled
        height: lineEdit.height
        width: parent.width
        color: "gray"
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
        visible: false
        MouseArea{
            anchors.fill: parent
            onClicked: {
                lineEdit.focus=true
            }
        }
    }

    Column {
        id: itemContent
        anchors.fill: parent
        property int itemHeight: control.height/(labelCaption.visible?2:1)
        width: parent.width
        Item {
            id: itemText
            width: parent.width
            height: parent.itemHeight
            Rectangle{
                id: recBackground
                parent: itemText
                anchors.fill: parent
                clip: {return false}
                color : "transparent"
                border.color : "gray"
                border.width : 1
                visible: (control.background===recBackground)
                enabled: control.enabled
            }
            Text{
                id: labelPlaceHolder
                //property alias focus: lineEdit.focus
                anchors{
                    fill: parent
                    leftMargin: 1
                }
                wrapMode: Text.NoWrap
                enabled: control.enabled
                color: "lightgray"
                horizontalAlignment: comboContentItem.horizontalAlignment
                verticalAlignment: comboContentItem.verticalAlignment
                visible: { return stateVisible();}
                function stateVisible(){
                    if(lineEdit.activeFocus)
                        return false;
                    else if(String(lineEdit.text)!=="")
                        return false;
                    else if(String(labelPlaceHolder.text).trim()==="")
                        return false;
                    else
                        return true;
                }

                function changeVisible(){
                    visible=stateVisible()
                }

                onFocusChanged: {

                }

                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        lineEdit.focus=true
                        lineEdit.forceActiveFocus()
                    }
                }
                font{
                    pixelSize: {return lineEdit.font.pixelSize}
                    weight: {return lineEdit.font.weight}
                    bold: {return lineEdit.font.bold}
                    letterSpacing: {return lineEdit.font.letterSpacing}
                    family: {return lineEdit.font.family}
                }


            }
            Item {
                clip: true
                anchors.fill: parent

                ComboBox {
                    id: lineEdit
                    model: ["First", "Second", "Third"]

                    delegate: ItemDelegate {
                        width: lineEdit.width
                        contentItem: Text {
                            text: modelData
                            color: "gray"
                            font: lineEdit.font
                            elide: Text.ElideRight
                            verticalAlignment: Text.AlignVCenter
                        }
                        highlighted: lineEdit.highlightedIndex === index
                    }

                    indicator: Canvas {
                        id: canvas
                        x: lineEdit.width - width - lineEdit.rightPadding
                        y: lineEdit.topPadding + (lineEdit.availableHeight - height) / 2
                        width: 12
                        height: 8
                        contextType: "2d"

                        Connections {
                            target: lineEdit
                            function onPressedChanged() { canvas.requestPaint(); }
                        }

                        onPaint: {
                            context.reset();
                            context.moveTo(0, 0);
                            context.lineTo(width, 0);
                            context.lineTo(width / 2, height);
                            context.closePath();
                            context.fillStyle = "#D3DAE0";
                            context.fill();
                        }
                    }

                    contentItem: Text {
                        id: comboContentItem

                        leftPadding: 0
                        rightPadding: lineEdit.indicator.width + lineEdit.spacing

                        text: lineEdit.displayText
                        font: lineEdit.font
                        color: "gray"
                        verticalAlignment: Text.AlignVCenter
                        elide: Text.ElideRight
                    }

                    background: Rectangle {
                        implicitWidth: 120
                        implicitHeight: 40
                        border.color: "gray"
                        border.width: lineEdit.visualFocus ? 2 : 1
                        radius: 2
                    }

                    popup: Popup {
                        y: lineEdit.height - 1
                        width: lineEdit.width
                        implicitHeight: contentItem.implicitHeight
                        padding: 1

                        contentItem: ListView {
                            clip: true
                            implicitHeight: contentHeight
                            model: lineEdit.popup.visible ? lineEdit.delegateModel : null
                            currentIndex: lineEdit.highlightedIndex

                            ScrollIndicator.vertical: ScrollIndicator { }
                        }

                        background: Rectangle {
                            border.color: "gray"
                            radius: 2
                        }
                    }

                    Keys.onPressed: {
                        if(event.key === Qt.Key_Tab) {
                            if(control.activeFocusOnTab){
                                if(forwardFocus!==null){
                                    forwardFocus.forceActiveFocus()
                                }
                            }
                            event.accepted = true
                        }
                        else if(event.key ===Qt.Key_Return || event.key===Qt.Key_Enter){
                            if(control.activeFocusOnPress){
                                if(forwardFocus!==null){
                                    forwardFocus.forceActiveFocus()
                                }
                            }
                            event.accepted = true
                        }
                    }


                    Rectangle{
                        id: lineBottom
                        anchors{
                            //topMargin: MCMeasures.densityPixel(2)
                            top: lineEdit.bottom
                            left: parent.left
                            right: parent.right
                        }
                        color: "gray"
                        height: {return MCMeasures.densityPixel(2)}
                    }
                }
            }
        }
    }
}

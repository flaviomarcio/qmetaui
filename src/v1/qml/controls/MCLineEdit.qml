import QtQuick 2.14
import QtQuick.Controls 2.14

Item {
    id: control

    height: MCMeasures.densityPixel(30)
    width : MCMeasures.densityPixel(100)

    activeFocusOnTab: true    

    property Item forwardFocus     : null

    property bool onlyNumber      : false

    property alias labelCaption    : labelCaption
    property alias labelPlaceHolder: labelPlaceHolder
    property alias placeholderText : labelPlaceHolder.text
    property alias lineEditText    : lineEdit.text
    property alias lineEdit        : lineEdit
    property alias textEditBox     : lineEdit
    property alias background      : recBackground
    property alias radius          : recBackground.radius
    property alias border          : recBackground.border

    property alias lineBottom      : lineBottom

    property alias acceptableInput              : lineEdit.acceptableInput
    property alias activeFocusOnPress           : lineEdit.activeFocusOnPress
    property alias autoScroll                   : lineEdit.autoScroll
    property alias bottomPadding                : lineEdit.bottomPadding
    property alias canPaste                     : lineEdit.canPaste
    property alias canRedo                      : lineEdit.canRedo
    property alias canUndo                      : lineEdit.canUndo
    property alias color                        : lineEdit.color
    property alias contentHeight                : lineEdit.contentHeight
    property alias contentWidth                 : lineEdit.contentWidth
    property alias cursorDelegate               : lineEdit.cursorDelegate
    property alias cursorPosition               : lineEdit.cursorPosition
    property alias cursorRectangle              : lineEdit.cursorRectangle
    property alias cursorVisible                : lineEdit.cursorVisible
    property alias displayText                  : lineEdit.displayText
    property alias echoMode                     : lineEdit.echoMode
    property alias effectiveHorizontalAlignment : lineEdit.effectiveHorizontalAlignment
    property alias font                         : lineEdit.font
    property alias horizontalAlignment          : lineEdit.horizontalAlignment
    property alias inputMask                    : lineEdit.inputMask
    property alias inputMaskExtra               : lineEdit.inputMaskExtra
    property alias inputMethodComposing         : lineEdit.inputMethodComposing
    property alias inputMethodHints             : lineEdit.inputMethodHints
    property alias leftPadding                  : lineEdit.leftPadding
    property alias length                       : lineEdit.length
    property alias maximumLength                : lineEdit.maximumLength
    property alias mouseSelectionMode           : lineEdit.mouseSelectionMode
    property alias overwriteMode                : lineEdit.overwriteMode
    property alias padding                      : lineEdit.padding
    property alias passwordCharacter            : lineEdit.passwordCharacter
    property alias passwordMaskDelay            : lineEdit.passwordMaskDelay
    property alias persistentSelection          : lineEdit.persistentSelection
    property alias preeditText                  : lineEdit.preeditText
    property alias readOnly                     : lineEdit.readOnly
    property alias renderType                   : lineEdit.renderType
    property alias rightPadding                 : lineEdit.rightPadding
    property alias selectByMouse                : lineEdit.selectByMouse
    property alias selectedText                 : lineEdit.selectedText
    property alias selectedTextColor            : lineEdit.selectedTextColor
    property alias selectionColor               : lineEdit.selectionColor
    property alias selectionEnd                 : lineEdit.selectionEnd
    property alias selectionStart               : lineEdit.selectionStart
    property alias text                         : lineEdit.text
    property alias textEdit                     : lineEdit.text
    property alias topPadding                   : lineEdit.topPadding
    property alias validator                    : lineEdit.validator
    property alias verticalAlignment            : lineEdit.verticalAlignment
    property alias wrapMode                     : lineEdit.wrapMode

    signal accepted()
    signal textEdited()
    signal enterPressed()
    signal editingFinished()

    onFocusChanged: {
        if(focus){
            lineEdit.focus=true
            lineEdit.forceActiveFocus()
        }
        else{
            lineEdit.focus=false
        }
        labelPlaceHolder.changeVisible()
    }

    onBackgroundChanged: {
        pvt.background.parent=itemText
        pvt.background.anchors.fill=pvt.background.parent
    }

    onEnabledChanged: {
        control.background.enabled=control.enabled
    }

    function forwardNext(item){
        if(item===null || item===undefined)
            item=control.forwardFocus

        if(!(item===null || item===undefined)){
            item.focus=true
            item.forceActiveFocus()
        }
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

    Item {
        id: pvt
        property Rectangle background: {
            if(control.background == null || control.background == undefined)
                return recBackground
            return control.background
        }
    }

    Column {
        id: itemContent
        anchors.fill: parent

        Text {
            id: labelCaption            
            wrapMode: Text.NoWrap
            enabled : control.enabled
            height  : itemContent.height * (labelCaption.visible?0.2:0)
            width   : parent.width
            color   : "gray"
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            visible: false
            onVisibleChanged: background.clip=false
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    lineEdit.focus=true
                }
            }
        }

        Item {
            id: itemText            
            height: itemContent.height * (labelCaption.visible?0.8:1)
            width : parent.width

            Rectangle {
                id: recBackground
                anchors.fill: parent
                clip         : false
                color        : "transparent"
                border.color : "gray"
                border.width : 1                
                enabled: control.enabled
            }

            Text {
                id: labelPlaceHolder
                anchors.fill: parent
                wrapMode: Text.NoWrap
                enabled : control.enabled
                color   : "lightgray"
                horizontalAlignment: lineEdit.horizontalAlignment
                verticalAlignment  : lineEdit.verticalAlignment
                visible            : stateVisible()
                font {
                    pixelSize    : lineEdit.font.pixelSize
                    weight       : lineEdit.font.weight
                    bold         : lineEdit.font.bold
                    letterSpacing: lineEdit.font.letterSpacing
                    family       : lineEdit.font.family
                }

                function stateVisible() {
                    let txtNow = (String(lineEdit.displayText).trim()=="")  && (String(lineEdit.preeditText).trim()=="") && ( String(lineEdit.text).trim()=="" )
                    if(txtNow)
                        return true
                    return false
                }

                function changeVisible() {
                    visible = Qt.binding(function(){ return labelPlaceHolder.stateVisible() })
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        lineEdit.focus=true
                        lineEdit.forceActiveFocus()
                    }
                }
            }

            Item {
                clip: true
                anchors.fill: parent

                TextInput {
                    id: lineEdit

                    property bool ___ignoreEventChanged : false
                    property string inputMaskExtra : ""

                    anchors {
                        top : parent.top
                        left : parent.left
                        right : parent.right
                        bottom: lineBottom.top
                    }
                    focus : false
                    activeFocusOnTab : true
                    activeFocusOnPress : true
                    enabled : control.enabled
                    color : "gray"
                    selectByMouse : true

                    horizontalAlignment: Qt.AlignLeft
                    verticalAlignment  : Qt.AlignBottom

                    onFocusChanged : labelPlaceHolder.changeVisible()

                    onTextEdited : control.textEdited()

                    onEditingFinished : control.editingFinished()

                    onAccepted : load()

                    Keys.onTabPressed: load()

                    Keys.onEnterPressed: load()

                    Keys.onReturnPressed: load()

                    Keys.onBacktabPressed: load()

                    onDisplayTextChanged: labelPlaceHolder.changeVisible()

                    onPreeditTextChanged: labelPlaceHolder.changeVisible()

                    onTextChanged : {
                        if(___ignoreEventChanged)
                            return

                        ___ignoreEventChanged=true

                        if (inputMaskExtra.trim()!==''){
                            if (control.onlyNumber){
                                lineEdit.text = stringUtil.toStrNumber(lineEdit.text)
                            }
                            if (inputMaskExtra.trim()!==''){
                                var txt=stringUtil.inputMaskFormat(lineEdit.inputMaskExtra, lineEdit.text)
                                text = txt
                            }
                            if (inputMask.trim()!==''){
                                var pos=stringUtil.inputMaskCursorPosition(lineEdit.inputMask, lineEdit.text)
                                lineEdit.cursorPosition=pos
                            }
                        }
                        labelPlaceHolder.changeVisible()
                        ___ignoreEventChanged=false
                    }

                    Keys.onPressed: {
                        if(event.key === Qt.Key_Tab) {
                            if(control.activeFocusOnTab){
                                if(forwardFocus != null && forwardFocus != undefined){
                                    forwardFocus.forceActiveFocus()
                                }
                            }
                            event.accepted = true
                        }
                        else if(event.key ===Qt.Key_Return || event.key===Qt.Key_Enter){
                            if(control.activeFocusOnPress){
                                if(forwardFocus != null && forwardFocus != undefined){
                                    forwardFocus.forceActiveFocus()
                                }
                            }
                            event.accepted = true
                        }

                        if(event.key === Qt.Key_Tab || event.key === Qt.Key_Return || event.key === Qt.Key_Back){
                            lineEdit.selectAll();
                        }
                        else if(event.key === Qt.Key_Left || event.key === Qt.Key_Right || event.key === Qt.Key_Up || event.key === Qt.Key_Down) {
                            lineEdit.selectionEnd
                        }
                        else{
                            lineEdit.selectionEnd
                        }
                    }


                    function load(){
                        Qt.inputMethod.hide()
                        control.accepted(text)
                    }

                    function isEmpty(){
                        return String(lineEdit.text).trim().length()===0
                    }
                }

                Rectangle {
                    id: lineBottom
                    color: "gray"
                    height: MCMeasures.densityPixel(2)
                    anchors {
                        left   : parent.left
                        right  : parent.right
                        bottom : parent.bottom
                        rightMargin: MCMeasures.percByScreenWidth(1)
                        bottomMargin: MCMeasures.percByScreenWidth(1)
                    }
                }
            }
        }
    }
}

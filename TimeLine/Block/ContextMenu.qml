import QtQuick 2.4
import QtGraphicalEffects 1.0

Rectangle {
    id: contextMenuItem
property Repeater globalRep
    property int blockIndex: 0
    property int columnIndex: 0    
    property int   minBlockWidth : 0
  //  signal menuSelected(int index) // index{1: Select All, 2: Remove Selected}
    property bool isOpen: false
    width: 150
    height: menuHolder.height + 20
    visible: isOpen
    focus: isOpen
    border { width: 2; color: "black" }
     color: "gray"
     property color text_color: "white"

    Column {
        id: menuHolder
        spacing: 1
        width: parent.width
        height: children.height * children.length
        anchors { verticalCenter: parent.verticalCenter; left: parent.left; leftMargin: 3 }
        ContextButton {
            text_color: contextMenuItem.text_color
            /*
           property color text_entered_color: "green"
           property color text_clicked_color: "red"*/
            color: contextMenuItem.color
            id: but_edit
            button_text: "Edit block"
            index: 1
            onButtonClicked: {

                var component = Qt.createComponent("EditBlock.qml")
                var window    = component.createObject(root)
                window.modality = Qt.WindowModal
                window.blockIndex = contextMenuItem.blockIndex
                window.columnIndex = contextMenuItem.columnIndex
                window.show()
                window.globalRep = contextMenuItem.globalRep
                 window.minBlockWidth = contextMenuItem.minBlockWidth
                contextMenuItem.visible = false
            }
        }

        ContextButton {
            text_color: contextMenuItem.text_color
            color: contextMenuItem.color
            id: but_remove
            button_text: "Remove block"
            index: 2
            onButtonClicked: {
                var col= contextMenuItem.columnIndex;
                var id = contextMenuItem.blockIndex;
                timeControll.removeBlock(col,id)
                globalRep.updateModel()
            }
        }
    }
}

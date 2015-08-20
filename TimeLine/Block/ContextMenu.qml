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

     Rectangle {
         border {width: 5; color: "black" }
         x: parent.width*0.6
         y: but_append.y
         z: 5
         id: appen_block_items
         visible: false
         width: parent.width/2
         color: "gray"
         ContextButton {
             text_color: contextMenuItem.text_color
             x: parent.border.width*2
             y: parent.border.width*2
             width: parent.width*0.8
             color: parent.color
             id: but_app_left
             button_text: "left"
             height: parent.height/3
             onButtonClicked: {
                contextMenuItem.visible = false
                timeControll.addBlockAt(columnIndex,blockIndex)
                 appen_block_items.visible = false
                 main222.needToLightSelected = false;
                 globalRep.updateModel();
                  but_append.color = contextMenuItem.color
             }
         }
         ContextButton {
             x: parent.border.width*2
             y: parent.border.width*2 +but_app_left.height
             text_color: contextMenuItem.text_color
             width: parent.width*0.8
             color: parent.color
             id: but_app_right
             button_text: "right"
              height: parent.height/3
             onButtonClicked: {

                 contextMenuItem.visible = false
                timeControll.addBlockAt(columnIndex,blockIndex+1)
                  appen_block_items.visible = false
                 main222.needToLightSelected = false;
                 globalRep.updateModel();
                  but_append.color = contextMenuItem.color
             }
         }
          height: but_edit.height*2.5
     }
     function showEditBlock()
     {
         var window    = Qt.createComponent("EditBlock.qml").createObject(contextMenuItem)
         window.modality = Qt.WindowModal
        // window.flags =  Qt.WindowMinimizeButtonHint| Qt.WindowMaximizeButtonHint | Qt.CustomizeWindowHint
        // Qt.WindowCloseButtonHint

         window.blockIndex = contextMenuItem.blockIndex
         window.columnIndex = contextMenuItem.columnIndex
         window.show()
         var temp = 400
         window.maximumHeight = temp
         window.maximumWidth = temp
         window.minimumHeight = temp
         window.minimumWidth = temp

         window.globalRep = contextMenuItem.globalRep
          window.minBlockWidth = contextMenuItem.minBlockWidth

     }

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
                 but_append.color = contextMenuItem.color
                appen_block_items.visible = false

                contextMenuItem.visible = false
                contextMenuItem.showEditBlock()
            }
        }


        ContextButton {
            text_color: contextMenuItem.text_color
            color: contextMenuItem.color
            id: but_append
            button_text: "Append block"
            index: 2

            onButtonClicked: {

                appen_block_items.visible = !appen_block_items.visible
                if (appen_block_items.visible)
                     color = "darkgrey"
                else
                    color = contextMenuItem.color
            }

        }
        ContextButton {
            text_color: contextMenuItem.text_color
            color: contextMenuItem.color
            id: but_remove
            button_text: "Remove block"
            index: 2
            onButtonClicked: {
                 but_append.color = contextMenuItem.color
                 appen_block_items.visible = false

                var col= contextMenuItem.columnIndex;
                var id = contextMenuItem.blockIndex;
                timeControll.removeBlock(col,id);
                main222.needToLightSelected = false;
                globalRep.updateModel();
                contextMenuItem.visible = false;

                // //console.log(" contextMenuItem.visible = false;")
            }
        }
        ContextButton {
            text_color: contextMenuItem.text_color
            color: contextMenuItem.color
            id: but_loadFile
            button_text: "Load from file"
            index: 3
            onButtonClicked: {
                 but_append.color = contextMenuItem.color
                appen_block_items.visible = false

                /*var col= contextMenuItem.columnIndex;
                var id = contextMenuItem.blockIndex;*/
                timeControll.loadFromFile();//removeBlock(col,id)
                contextMenuItem.visible = false;
                // //console.log("AFTER 9999999999999999999999");
                //main222.selectedBlock.repaint();
               // globalRep.updateModel();



            }
        }
        ContextButton {
            text_color: contextMenuItem.text_color
            color: contextMenuItem.color
            id: but_convertToText
            button_text: "Convert to text block"
            index: 3
            onButtonClicked: {
                appen_block_items.visible = false

                /*var col= contextMenuItem.columnIndex;
                var id = contextMenuItem.blockIndex;*/
                timeControll.convertCurentBlockToText();//removeBlock(col,id)
                contextMenuItem.visible = false;
                // //console.log("AFTER 9999999999999999999999");
                //main222.selectedBlock.repaint();
                globalRep.updateModel();



            }
        }
    }
    function show(a,b, globRep)
    {
        contextMenuItem.globalRep = globRep
        x = a
      y = b
        context_menu.visible = true
    }

}

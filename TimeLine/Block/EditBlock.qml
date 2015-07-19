import QtQuick 2.4
import QtGraphicalEffects 1.0
import QtQuick.Controls 1.2

ApplicationWindow  {
    id: mainwindow
    property int blockIndex: 0
    property int columnIndex: 0
     property int   minBlockWidth : 0

    property Repeater globalRep

    Rectangle {
    id: contextMenuItem
    signal menuSelected(int index) // index{1: Select All, 2: Remove Selected}
    property bool isOpen: false

    width: block_width.width + 1
    height: 200
     color: "gray"
     property color text_color: "white"
     Column {
         id: columns
         spacing: 1
         width: parent.width
         height: children.height * children.length
         anchors { verticalCenter: parent.verticalCenter; left: parent.left; leftMargin: 3 }

            Rectangle {
                id: block_width
                color: "black"
                width: 200 // block_width_text + 10 + block_width_value.width
                height: 40
                border  { width: 2; color: "white" }
                Text {
                    id: block_width_text
                    text: "Block width"
                    color: "white"
                    anchors { verticalCenter: parent.verticalCenter; left: parent.left; leftMargin: 10 }
                    font { pixelSize: 14 }
                }
                SpinBox {
                     id: block_width_value
                     x: block_width.width - 70
                     anchors.verticalCenter: block_width.verticalCenter
                     maximumValue : 999999
                    // minimumValue : minBlockWidth
                    value: timeControll.getTestWidth(mainwindow.columnIndex,mainwindow.blockIndex)
                    onFocusChanged:  {
                        if (value < minBlockWidth)
                            value = minBlockWidth;
                    }

                }
            }



     }
         Button {
             id: but_ok
             y: contextMenuItem.height - 10 -height
            x: 10
             text: "OK"
             onClicked: {
                 timeControll.setTestWidth(mainwindow.columnIndex,mainwindow.blockIndex,block_width_value.value)
                 globalRep.updateModel()
                 close();
             }
         }
         Button {
             id: but_cancel
             y: contextMenuItem.height - 10 - height
             x: contextMenuItem.width - 10 - width
             text: "CANCEL"
           onClicked: {
               close();
           }
         }

    }
}

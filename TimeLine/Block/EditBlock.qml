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

    width: 400
    height: 400
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
                width: contextMenuItem.width // block_width_text + 10 + block_width_value.width
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

            Rectangle {
                id: block_name
                color: "black"
                width: contextMenuItem.width // block_width_text + 10 + block_width_value.width
                height: 40
                border  { width: 2; color: "white" }
                Text {
                    id: block_name_text
                    text: "Block\'s name"
                    color: "white"
                    anchors { verticalCenter: parent.verticalCenter; left: parent.left; leftMargin: 10 }
                    font { pixelSize: 14 }
                }
                TextField   {
                     id: block_name_value
                     x: block_width.width - width - 10
                     width: 200
                     font { pixelSize: 14 }
                     y: 7
                    // minimumValue : minBlockWidth
                     property string initText : timeControll.getTest(mainwindow.columnIndex,mainwindow.blockIndex)
                    text: initText
                   // color: text_color
                    onFocusChanged:  {
                        if (text.length ==0)
                            text = initText;
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
                 timeControll.setTestName(mainwindow.columnIndex,mainwindow.blockIndex,block_name_value.text)
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

import QtQuick 2.4
import QtGraphicalEffects 1.0
import QtQuick.Controls 1.2

ApplicationWindow  {
    id: mainwindow
    property int blockIndex: 0
    property int columnIndex: 0
     property int   minBlockWidth : 1000
    property Item selectedBlock

    property Repeater globalRep

    Rectangle {
    id: contextMenuItem
    signal menuSelected(int index) // index{1: Select All, 2: Remove Selected}
    property bool isOpen: false

    width: 400
    height: 400
     color: "gray"
     property color text_color: "white"

  // onWindowChanged:   timeControll.setIsEditBlockShow(true) //when show
     Column {
         id: columns
         spacing: 1
         width: parent.width
         height: children.height * children.length
         anchors { verticalCenter: parent.verticalCenter; left: parent.left; leftMargin: 3 }

            Rectangle {
                id: block_width
                color: "black"
                enabled: !timeControll.getCurent_group() //@BAG@//NICOlas
                width: contextMenuItem.width // block_width_text + 10 + block_width_value.width
                height: 40
                border  { width: 2; color: "white" }
                Text {
                    id: block_width_text
                    text: "Block time (ms)"
                    color: "white"
                    anchors { verticalCenter: parent.verticalCenter; left: parent.left; leftMargin: 10 }
                    font { pixelSize: 14 }
                }             
                TextField   {
                     id: block_time_value
                     x: block_width.width - width - 10
                     width: 200
                     font { pixelSize: 14 }
                     y: 7
                    // minimumValue : minBlockWidth
                     property string initText : timeControll.getBlockTime(mainwindow.columnIndex,mainwindow.blockIndex)
                    text: initText
                   // color: text_color
                    onFocusChanged:  {
                        if (text.length ==0)
                            text = initText;
                        if(text< minBlockWidth)
                            text = minBlockWidth
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
                     property string initText : timeControll.getBlockKey(mainwindow.columnIndex,mainwindow.blockIndex)
                    text: initText
                   // color: text_color
                    onFocusChanged:  {
                        if (text.length ==0)
                            text = initText;
                    }

                }
            }

            Rectangle {
                id: block_X
                color: "black"
                width: contextMenuItem.width // block_width_text + 10 + block_width_value.width
                height: 40
                border  { width: 2; color: "white" }
                Text {
                    id: block_X_text
                    text: "Draw\'s X"
                    color: "white"
                    anchors { verticalCenter: parent.verticalCenter; left: parent.left; leftMargin: 10 }
                    font { pixelSize: 14 }
                }
                TextField   {
                     id: block_X_value
                     x: block_width.width - width - 10
                     width: 200
                     font { pixelSize: 14 }
                     y: 7
                    // minimumValue : minBlockWidth
                     property string initText : timeControll.getDrawX(mainwindow.columnIndex,mainwindow.blockIndex)
                    text: initText
                   // color: text_color
                    onFocusChanged:  {
                        if (text.length ==0)
                            text = initText;
                    }
                }
            }

            Rectangle {
                id: block_Y
                color: "black"
                width: contextMenuItem.width // block_width_text + 10 + block_width_value.width
                height: 40
                border  { width: 2; color: "white" }
                Text {
                    id: block_Y_text
                    text: "Draw\'s Y"
                    color: "white"
                    anchors { verticalCenter: parent.verticalCenter; left: parent.left; leftMargin: 10 }
                    font { pixelSize: 14 }
                }
                TextField   {
                     id: block_Y_value
                     x: block_width.width - width - 10
                     width: 200
                     font { pixelSize: 14 }
                     y: 7
                    // minimumValue : minBlockWidth
                     property string initText : timeControll.getDrawY(mainwindow.columnIndex,mainwindow.blockIndex)
                    text: initText
                   // color: text_color
                    onFocusChanged:  {
                        if (text.length ==0)
                            text = initText;
                    }
                }
            }

            Rectangle {
                id: block_Z
                color: "black"
                width: contextMenuItem.width // block_width_text + 10 + block_width_value.width
                height: 40
                border  { width: 2; color: "white" }
                Text {
                    id: block_Z_text
                    text: "Draw\'s Z"
                    color: "white"
                    anchors { verticalCenter: parent.verticalCenter; left: parent.left; leftMargin: 10 }
                    font { pixelSize: 14 }
                }
                TextField   {
                     id: block_Z_value
                     x: block_width.width - width - 10
                     width: 200
                     font { pixelSize: 14 }
                     y: 7
                    // minimumValue : minBlockWidth
                     property string initText : timeControll.getDrawZ(mainwindow.columnIndex,mainwindow.blockIndex)
                    text: initText
                   // color: text_color
                    onFocusChanged:  {
                        if (text.length ==0)
                            text = initText;
                    }
                }
            }

            Rectangle {
                id: block_Width
                color: "black"
                width: contextMenuItem.width // block_width_text + 10 + block_width_value.width
                height: 40
                border  { width: 2; color: "white" }
                Text {
                    id: block_Width_text
                    text: "Draw\'s width"
                    color: "white"
                    anchors { verticalCenter: parent.verticalCenter; left: parent.left; leftMargin: 10 }
                    font { pixelSize: 14 }
                }
                TextField   {
                     id: block_Width_value
                     x: block_width.width - width - 10
                     width: 200
                     font { pixelSize: 14 }
                     y: 7
                    // minimumValue : minBlockWidth
                     property string initText : timeControll.getDrawSize(mainwindow.columnIndex,mainwindow.blockIndex).width
                    text: initText
                   // color: text_color
                    onFocusChanged:  {
                        if (text.length ==0)
                            text = initText;
                    }
                }
            }

            Rectangle {
                id: block_Height
                color: "black"
                width: contextMenuItem.width // block_width_text + 10 + block_width_value.width
                height: 40
                border  { width: 2; color: "white" }
                Text {
                    id: block_Height_text
                    text: "Draw\'s height"
                    color: "white"
                    anchors { verticalCenter: parent.verticalCenter; left: parent.left; leftMargin: 10 }
                    font { pixelSize: 14 }
                }
                TextField   {
                     id: block_Height_value
                     x: block_width.width - width - 10
                     width: 200
                     font { pixelSize: 14 }
                     y: 7
                    // minimumValue : minBlockWidth
                     property string initText : timeControll.getDrawSize(mainwindow.columnIndex,mainwindow.blockIndex).height
                    text: initText
                   // color: text_color
                    onFocusChanged:  {
                        if (text.length ==0)
                            text = initText;
                    }
                }
            }


            /*
             Q_INVOKABLE void setDrawX(int col, int i, int value);
             Q_INVOKABLE int getDrawX(int col, int i);
            Q_INVOKABLE void setDrawY(int col, int i, int value);
            Q_INVOKABLE int getDrawY(int col, int i);
            Q_INVOKABLE void setDrawZ(int col, int i, int value);
            Q_INVOKABLE int getDrawZ(int col, int i);
            Q_INVOKABLE void setDrawWidth(int col, int i, int value);
            Q_INVOKABLE int getDrawWidth(int col, int i);
            Q_INVOKABLE void setDrawHeight(int col, int i, int value);
            Q_INVOKABLE int getDrawHeight(int col, int i);

*/

     }
         Button {
             id: but_ok
             y: contextMenuItem.height - 10 -height
            x: 10
             text: "OK"
             onClicked: {
                 if (block_time_value.text < minBlockWidth)
                     block_time_value.text = minBlockWidth;
                 timeControll.setBlockTime(mainwindow.columnIndex,mainwindow.blockIndex,block_time_value.text)
                 timeControll.setBlockKey(mainwindow.columnIndex,mainwindow.blockIndex,block_name_value.text)

                 timeControll.setDrawX(mainwindow.columnIndex,mainwindow.blockIndex,block_X_value.text)
                 timeControll.setDrawY(mainwindow.columnIndex,mainwindow.blockIndex,block_Y_value.text)
                 timeControll.setDrawZ(mainwindow.columnIndex,mainwindow.blockIndex,block_Z_value.text)
                 timeControll.setDrawSize(mainwindow.columnIndex,mainwindow.blockIndex,block_Width_value.text,block_Height_value.text)

                timeControll.emitBlockEditedSignal()
               // mainwindow.globalRep.updateModel()
                 //console.log("AAAAAAAAAAAAAAAAAAAA "+ mainwindow.columnIndex +" " + mainwindow.blockIndex)
                 mainwindow.selectedBlock.updateTrackWhereIsBlock()
                mainwindow.close();
                mainwindow.destroy();
             }
         }
         Button {
             id: but_cancel
             y: contextMenuItem.height - 10 - height
             x: contextMenuItem.width - 10 - width
             text: "CANCEL"
           onClicked: {
               mainwindow.close();
               mainwindow.destroy();
           }
         }

    }
}

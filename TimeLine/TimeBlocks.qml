import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtGraphicalEffects 1.0

import "Block" as ContentBlock
import "ToolBar" as ContentToolBar

    Item {
    id:main_root
     property Repeater globalRep
    property int clicked_blockId : -1
  property int clicked_blockX : -1
   property int clicked_blockY : -1
   property int drop_blockX : -1
    property int drop_blockY : -1
   property int maIsPressed: 0
   property int dropEntered: 0

    Row {
      id: blocks
      height: 220

      Repeater {
          id: repka
          property bool isDrag : false
          model: timeControll.getTrackSize()
          function updateModel()      {
              model = model - 1;
              console.log("function updateModel()      {")
                   model =  timeControll.getTrackSize()

              }
          delegate:
          ContentBlock.Block{
              id: cool
              globalRep : repka
              height: 200
              width: timeControll.getBlockTime(index)
              mIndex: index
              title: timeControll.getBlockKey(index)
          }
          Component.onCompleted: {
             //trackbar.globalRep = repka
              main_root.globalRep = repka
          }
      }
    }
    Component.onCompleted: {
        main_root.width = blocks.childrenRect.width
        main_root.height = blocks.childrenRect.height
    }
    }


  /*

    Image {
        x: 30
        source: "qrc:/iphone_toolbar_icons/arrowdown.png"
        height: 100
        width: 1000
    }*/



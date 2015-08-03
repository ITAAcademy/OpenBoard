import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtGraphicalEffects 1.0

import "Block" as ContentBlock
import "ToolBar" as ContentToolBar

Rectangle {
    id: frama
    color: "#333333"
  //  width: 1000 ///main222.width + 20
  // height: 500 //main222.height + 20
    //anchors.margins : 20
   // onHeightChanged: // console.log("HEIGHT = " + height)
z: -150
radius: 10
MouseAreaForWindowDraging{
    id: framaMA
anchors.fill:   frama
}
/*
MouseAreaForWindowDraging{
anchors.left:   frama.left
width: 20
}
MouseAreaForWindowDraging{
 anchors.right:   frama.right
 width: 20
}
MouseAreaForWindowDraging{
 anchors.top:   frama.top
 height: 20
}
MouseAreaForWindowDraging{
 anchors.bottom:   frama.bottom
 height : 20
}*/
property Rectangle p_main222

Rectangle
{

    id:main222

    anchors.fill: parent
    property int margin_value : 20
    anchors.margins:  margin_value
    radius: 10
        color: "gray"

    Component.onCompleted: {
    frama.p_main222 = main222
    }
    width: childrenRect.width ///main222.width + 20
   height: childrenRect.height //main222.height + 20
    property int clicked_blockId : -1
    property int clicked_blockX : -1
    property int clicked_blockY : -1
    property int drop_blockX : -1
    property int drop_blockY : -1
    property int maIsPressed: 0
    property int dropEntered: 0
   property Item selectedBlock
   property int selectedBlockCol : 0
   property int selectedBlockIndex : 0
   property int minBlockWidth : 0
   property bool isPlay : false


   property  bool needToLightSelected : false
  property Repeater p_rep_columns
    property Item p_item_col
  property Item  p_trackbar
   property Item  p_scale_pointer
   property Item  p_context_menu

   property int mX : 0


    property real scaling : 1
    onScalingChanged: {
        if (scaling <= 0.02)
            scaling = 0.02
    }

    function addTrack()     {
        timeControll.addNewTrack( )
    rep_columns.model +=1
    }

    function removeTrack()    {
        timeControll.removeLastTrack()
    rep_columns.model -=1
    }

    function play()    {
        main222.isPlay = true

    }
    function pause()    {
main222.isPlay = false

    }
    function stop()    {
      //  scale_pointer.x =
main222.isPlay = false
//scale_pointer.x = timeControll.getMaxTrackTime() + scale_pointer.width/2 - scroll.flickableItem.contentX;
    }

    function setScalePointerPos(xx)    {
        scale_pointer.x = xx

    }

     Connections {
       target: timeControll

      onPlaySignal: {
       main222.play()
       }
      onPauseSignal: {
       main222.pause()
       }
       onStopSignal: {
       main222.stop()
       }
       onSetScalePointerPosSignal: {
       main222.setScalePointerPos(value)
       }

       onUpdateSignal:  {
           if (main222.isPlay )
           {
                scale_pointer.x = timeControll.getPlayTime() + 15 - scroll.flickableItem.contentX;
               timeControll.calcPointedBlocksAtTime()
              // console.log("timer value: " +timeControll.getPlayTime())
           }


       }
       }





    Rectangle {
        id: time_scale
        property int division : 50
        property bool ud_down : true
        width: 2000//item_col.width
        height: 20// item_col.height/10
        color: "gray"
             property int tX: 0
        x: scroll.flickableItem.contentX  //trackbar.x   //  item_col.x
        y: 0// main222.height -height - 20
        z: 2

       /* Component.onCompleted: {
            var rec = mapFromItem(time_scale,10,10)
            // console.log(rec.x + " mapFromItem "  + rec.y)

        }*/
        Row {
        Repeater {
            id: time_scale_rep
            model:   time_scale.width/ time_scale.division
            delegate:
            Rectangle{
                width: time_scale.division
               height: time_scale.height
                 color: "black"
               // x: time_scale.tX
               Rectangle {
                    id: hor_line
                width: time_scale.division
                height: time_scale.height/20
                color: "white"
                y: time_scale.height/2
                x:0
                }
                Rectangle {
                id: ver_line
                height: time_scale.height
                width: hor_line.height
                x: time_scale.division - width
                color: "white"
                }
                Text {
                text:  time_scale.division * index + " ms"

                y:  time_scale.ud_down === true ? 0: hor_line.y
                width:  time_scale.division
                height: time_scale.height/2
                 color: "white"
                 anchors.right: ver_line.left


                 //font { pixelSize: 10 }
                 Component.onCompleted: {
                     time_scale.ud_down = !time_scale.ud_down
                 }
                }

                Component.onCompleted: {
                 /*  time_scale.tX += time_scale.division
                    // console.log(" new division added " +  time_scale.tX)*/
                }
            }
        }
        }
    }
    Image{
        id: scale_pointer
        source: "qrc:/iphone_toolbar_icons/arrow.png"
        height: time_scale.height
        width: height
        scale: 1.5
        x: 20 //absolute zdvig 20
        z: time_scale.z +1
        //property int trackbar_right
        Component.onCompleted: {
            main222.p_scale_pointer = scale_pointer
          //  x = 40
        }

        onYChanged: y = 0
        onXChanged: {
          //  if (x===0)     x = scroll.flickableItem.width
         //  console.log("1000")
           // var half_scale_pointer_width = -scale_pointer.width/2
            var zdvig = 20 - scroll.flickableItem.contentX
           // // console.log(" 3 scroll.flickableItem.contentX = " + scroll.flickableItem.contentX )
        // console.log("10001")
            if (zdvig < 0)
            {
             zdvig = -width/2//   zdvig = 0;
            // console.log("10002")
            }
            // console.log("10003")
            if (x<zdvig)
            {
                 // console.log("10004")
                scroll.flickableItem.contentX -= zdvig -x
                if (scroll.flickableItem.contentX < 0)
                {
                    scroll.flickableItem.contentX = 0;
                     // console.log("10005")
                }
               x = zdvig
                  //console.log("10006")
            }
            else
            {
               var temp = timeControll.getMaxTrackTime() - scroll.flickableItem.contentX + width
                if (x  > temp )
                {
                   // console.log("HAAAAAAAAAAA")
                    x = temp
                  // timeControll.stop();
                   // main222.stop()
                }
                else
                {
                temp = scroll.width -width - 3  /// scroll.x + scroll.width - main222.p_trackbar.width*1.4
                 //console.log("10007")
                if (x> temp)
                {
                   // console.log("DAAAAAAAAAAAAAAAAAAAAAAAAAAAAAa")
                    if (timeControll.getMaxTrackTime()  >= scroll.width  )
                    {
                         //console.log("10008")
                    scroll.flickableItem.contentX += x - temp
                    var sad = timeControll.getMaxTrackTime() - scroll.width + 17  // scroll.flickableItem.contentWidth - scroll.width + 10
                    if (scroll.flickableItem.contentX  >  sad)
                    {
                            scroll.flickableItem.contentX = sad;
                        //timeControll.stop();
                       // x-=3;
                    }
                    }
                    else
                       {
                        timeControll.stop();
                        //x = temp
                         //console.log("10010")
                    }
                    x = temp
                }
            }
            }


            if (!main222.isPlay)
            {
            timeControll.calcPointedBlocks();
                //console.log("AAAAAAAAAAA")
                //console.log("getScalePointerPos = " + timeControll.getScalePointerPos())

            }
            timeControll.setScalePointerPos(x-20 + scroll.flickableItem.contentX);
           // // console.log("x + scroll.flickableItem.contentX = "+x +" + " + scroll.flickableItem.contentX

            //console.log("scale_pointer X = " +(x+width/2))
        }

        MouseArea {
            id: spMA
            anchors.fill: parent
            drag.target : scale_pointer
            onPressed: {
                 context_menu.visible = false
            }
        }
    }

    Rectangle{
        id:scale_pointer_verline
       height: tollbar.height  //  scroll.height - main222.margin_value
        width: 2
        color: "#6E0000"
       // y: scale_pointer.height
        x: scale_pointer.width/2 + scale_pointer.x
        z: 200
      // height:400
       //  onHeightChanged: // console.log("HEIGHT  pointer line = " + height)

    }


    Row { //scroll + toolbar
        id: toolbar_scroll
        width: parent.width
        height: parent.height - time_scale.height
        y : time_scale.height


         ScrollView {
              id: scroll
              width: parent.width - tollbar.width
              height: parent.height
              property int horizontalX: flickableItem.contentX
              property int verticalY: flickableItem.contentY
             property int baba: scroll.flickableItem.contentWidth
              onHorizontalXChanged:  {
               time_scale.x = -horizontalX + 30
                  context_menu.visible = false
              }
              onVerticalYChanged:  {
                  context_menu.visible = false

              }


              horizontalScrollBarPolicy :Qt.ScrollBarAlwaysOn
              verticalScrollBarPolicy  :Qt.ScrollBarAlwaysOn
                clip: true
                __wheelAreaScrollSpeed: 50

              Rectangle {
                    id: item_col
                    scale: 1
                    property Item p_columns
                    property Item p_trackbar
                   // width: childrenRect.width
                    height: childrenRect.height
                    color: "gray"
                    onWidthChanged: {
                        if (time_scale.width < width  )
                        {
                            time_scale.width = width  ;
                            time_scale_rep.model = time_scale.width/ time_scale.division + 2
                        }
                         //console.log("122  item_col.width=" + item_col.width)
                    }
                    Column {
                          id: columns
                          width:  timeControll.getMaxTestWidth()
                          property Repeater globalRep
                          spacing: 2
                          Repeater {
                          id: rep_columns
                          model: 1
                          onModelChanged: {
                              if ( model < 0)
                                  model = 0;
                          }

                          Component.onCompleted: {
                          main222.p_rep_columns = rep_columns
                          }

                          delegate:
                               Row {
                               id: bar_track
                               function abortColorize()
                               {
                                   for (var i=0; i< repka.model; i++)
                                        repka.itemAt(i).p_color_overlay.color = "#00000000"
                                  // blocks.itemAt(i).icon_coloroverlay.color = "#00000000"
                               }
                               function setColorize(indexa, color)
                               {
                                       repka.itemAt(indexa).p_color_overlay.color = color
                                  //  // console.log("GGGGGGGGGG " + repka.itemAt(indexa).mX)
                                  // // console.log("GGGGGGGGGG " + repka.itemAt(indexa).x)
                                   //main222.p_scale_pointer.x = repka.itemAt(indexa).x
                               }
                               function getBlockX (indexa)
                               {
                                   // console.log("repka.itemAt(indexa).x="+repka.itemAt(indexa).x)

                                     return repka.itemAt(indexa).x
                               }


                               property int mIndex: index
                                 ContentToolBar.TrackToolBar {
                                        id: trackbar
                                        width: 30
                                         property int mIndex: index
                                        height: main_root.height
                                        z:12
                                        x: 0
                                     Rectangle {
                                     id:main_root
                                     x: 30
                                     width: 4000
                                     height: 100
                                     color: "gray"
                                     Row {
                                       id: blocks
                                     //  height: 220
                                       Repeater {
                                           id: repka



                                           property bool isDrag : false
                                           model:  timeControll.getTrackSize(trackbar.mIndex)//     bar_track.mIndex)
    function updateModel()      {
        model = model - 1;
        item_col.width = timeControll.getMaxTrackTime() + 31
            timeControll.update();
        model =  timeControll.getTrackSize(bar_track.mIndex)
        if (main222.needToLightSelected)
        {
            rep_columns.itemAt(main222.selectedBlockCol).setColorize(main222.selectedBlockIndex,"#8000FF00")
            // console.log("selectedBlockIndex=" + main222.selectedBlockIndex)
       // main222.p_scale_pointer.x =rep_columns.itemAt(main222.selectedBlockCol).getBlockX(main222.selectedBlockIndex)
       //main222.mX//
            main222.needToLightSelected = false

        }
        timeControll.calcPointedBlocks();

    }
                                           delegate:
                                           ContentBlock.Block{
                                               id: cool
                                               globalRep : repka
                                               height:  100 //* main222.scaling
                                               mIndex: index
                                                colIndex:  bar_track.mIndex
                                   width:  timeControll.getBlockTime(colIndex, mIndex) //* main222.scaling
                                    p_main222: main222

                                               title: timeControll.getBlockKey(colIndex,mIndex)

                                              /* time_scale_valueRecX : time_scale_value.mX
                                               time_scale_valueRecY : time_scale_value.mY*/

                                              /* p_mouse_area.onPositionChanged: {
                                                  time_scale_value.mX = scrollMA.mouseX
                                                    time_scale_value.mY = scrollMA.mouseY
                                               }*/
                                           }
                                           onModelChanged: {
                columns.width =  timeControll.getMaxTrackTime() //* main222.scaling
                                           }

                                       }
                                       Component.onCompleted: {
                                         main222.minBlockWidth = repka.itemAt(0).minWidth
                                         /*   // console.log("item_col.p_columns.globalRep " + item_col.p_columns.globalRep)
                                           // console.log("cool.repka " + cool.repka)
                                           item_col.p_columns.globalRep = cool.repka
                                           // console.log("REPKA " + item_col.p_columns.globalRep)*/
                                           //item_col.main_root = main_root
                                       }
                                     }

                                          }
                                     Component.onCompleted: {
                                    trackbar.globalRep = repka
                                         main222.p_trackbar = trackbar
                                          time_scale.x = trackbar.width + trackbar.x
                                     }
                                 }
                                 }    //
                            }
                   onChildrenRectChanged:  {
                   width =  timeControll.getMaxTrackTime()/// * main222.scaling
                   // // console.log(" timeControll.getMaxTestWidth() = " +  width)
                   }
                    } /* rep_columns end */
              }
           }
         ContentToolBar.ToolBar{
             id: tollbar
             z: 30
             x: scroll.width
             width: 30
             height: parent.height
         }

       ////////////////////////tuta
        }



    }

ContentBlock.ContextMenu {
    id: context_menu
    x: 20
    y: 0
    z: 500
    visible: false
    Component.onCompleted: {
        main222.p_context_menu = context_menu
    }

    columnIndex : main222.selectedBlockCol
    blockIndex: main222.selectedBlockIndex


    /*onXChanged: {
            x = root.x + root.width/2;
        z:500

    }*/
    globalRep: main222.p_trackbar.globalRep
    minBlockWidth : main222.minBlockWidth
}

Rectangle {
    anchors.fill: parent
    border.color: "#333333";
    color: "transparent"
    radius: 10
    border.width: main222.margin_value
}
}

  /*

    Image {
        x: 30
        source: "qrc:/iphone_toolbar_icons/arrowdown.png"
        height: 100
        width: 1000
    }*/



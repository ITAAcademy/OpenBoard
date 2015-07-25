import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtGraphicalEffects 1.0

import "Block" as ContentBlock
import "ToolBar" as ContentToolBar

Rectangle {
    id: frama
    color: "dimgrey"
  //  width: 1000 ///main222.width + 20
  // height: 500 //main222.height + 20
    //anchors.margins : 20
z: -150
radius: 10
MouseAreaForWindowDraging{
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
anchors.fill: parent
anchors.margins:  20
radius: 10
    color: "gray"
    id:main222

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
   onSelectedBlockColChanged: {

   }
   onSelectedBlockIndexChanged: {

   }

   property  bool needToLightSelected : false
  property Repeater p_rep_columns
    property Item p_item_col
  property Item  p_trackbar
   property Item  p_scale_pointer

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
        playTimer.running = true;

         playTimer.start();


    }
    function pause()    {
     playTimer.stop()


    }
    function stop()    {
     playTimer.running = false
        scale_pointer.x = 0


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
       }



    Timer {
        id: playTimer
          interval: 1; running: false; repeat: true
          onTriggered: {
              scale_pointer.x +=1
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
            console.log(rec.x + " mapFromItem "  + rec.y)

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
                    console.log(" new division added " +  time_scale.tX)*/
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
           // console.log("XXXXXXXXXXXXXXXscroll.flickableItem.contentX " +scroll.flickableItem.contentX)
            var half_scale_pointer_width = -scale_pointer.width/2
            var zdvig = 20 - scroll.flickableItem.contentX
                if (zdvig < 0)
                 zdvig = -width/2//   zdvig = 0;


            if (x<zdvig)
            {
                scroll.flickableItem.contentX -= zdvig -x
                if (scroll.flickableItem.contentX < 0)
                        scroll.flickableItem.contentX = 0;
               x = zdvig
            }
            else
            {
                var temp = scroll.width -width/2  /// scroll.x + scroll.width - main222.p_trackbar.width*1.4
                if (x> temp)
                {
                    if (timeControll.getMaxTrackTime()  >= scroll.width)
                    {
                    scroll.flickableItem.contentX += x - temp
                    var sad = timeControll.getMaxTrackTime() - scroll.width + 17  // scroll.flickableItem.contentWidth - scroll.width + 10
                    if (scroll.flickableItem.contentX  >  sad)
                    {
                            scroll.flickableItem.contentX = sad;
                        timeControll.stop();
                    }


                    }
                    else
                        if (timeControll.getMaxTrackTime() <= scroll.width )
                        timeControll.stop();
                x = temp
                }
            }
            timeControll.setScalePointerPos(x-30)
            timeControll.calcPointedBlocks()
        }
        Rectangle{
            height:  frama.height - 190
            width: 1
            color: "#6E0000"
            x: scale_pointer.width/2

        }
        MouseArea {
            id: spMA
            anchors.fill: parent
            drag.target : scale_pointer
        }
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
             property int baba: scroll.flickableItem.contentWidth
              onHorizontalXChanged:  {
               time_scale.x = -horizontalX + 30
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
                    onWidthChanged: {
                        if (time_scale.width < width  )
                        {
                            time_scale.width = width  ;
                            time_scale_rep.model = time_scale.width/ time_scale.division
                        }
                        console.log("122  item_col.width=" + item_col.width)
                    }
                    Column {
                          id: columns
                          width:  timeControll.getMaxTestWidth()
                          property Repeater globalRep
                          spacing: 2
                          Repeater {
                          id: rep_columns
                          model: 1
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
                                  //  console.log("GGGGGGGGGG " + repka.itemAt(indexa).mX)
                                  // console.log("GGGGGGGGGG " + repka.itemAt(indexa).x)
                                   //main222.p_scale_pointer.x = repka.itemAt(indexa).x
                               }
                               function getBlockX (indexa)
                               {

                                     return repka.itemAt(indexa).mX
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
                                               item_col.width = timeControll.getMaxTrackTime()
                                                    model =  timeControll.getTrackSize(bar_track.mIndex)
                                               if (main222.needToLightSelected)
                                               {
                   rep_columns.itemAt(main222.selectedBlockCol).setColorize(main222.selectedBlockIndex,"#8000FF00")
                     main222.p_scale_pointer.x =main222.mX// rep_columns.itemAt(main222.selectedBlockCol).getBlockX(2)//main222.selectedBlockIndex)
                                               }
                                                   main222.needToLightSelected = false
                                               console.log("FFFFFFFFFFFFFF updateModel")
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
                                          //trackbar.globalRep = repka
                                         /*   console.log("item_col.p_columns.globalRep " + item_col.p_columns.globalRep)
                                           console.log("cool.repka " + cool.repka)
                                           item_col.p_columns.globalRep = cool.repka
                                           console.log("REPKA " + item_col.p_columns.globalRep)*/
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
                   // console.log(" timeControll.getMaxTestWidth() = " +  width)
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
    MouseArea {
        id: for_scrollview_zoom
        anchors.fill: parent
        visible: false
        onWheel: {

            if (wheel.angleDelta.y > 0)
            main222.scaling += 0.02
            else if (wheel.angleDelta.y < 0)
                main222.scaling -= 0.02
 console.log("wheel.angleDelta.y = " + wheel.angleDelta.y + " main222.scaling=" + main222.scaling)

   /*       item_col.scale +=  scaling
            time_scale.scale  +=scaling

            item_col.x+= scaling *300
            time_scale.x += scaling *1030

            toolbar_scroll.y += scaling *10// time_scale.height
             item_col.y+= scaling *100

*/


/*
            var temp = scaling * 1000
           // item_col.width += temp//
            item_col. childrenRect.width  += temp
           // item_col.height += temp //
            item_col. childrenRect.height += temp*/
        }
    }

 focus: true
    Keys.onPressed: {
        if (event.key === Qt.Key_Control) {
            console.log("ctrl pressed") }
     for_scrollview_zoom.visible = true;
    }
    Keys.onReleased: {
         for_scrollview_zoom.visible = false;
    }
    }

}

  /*

    Image {
        x: 30
        source: "qrc:/iphone_toolbar_icons/arrowdown.png"
        height: 100
        width: 1000
    }*/



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
     //timeControll.loadCurrentTextInTheFirstBlockWhenInit()
         p_context_menu.globalRep.updateModel();
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
   property Item selectedBlock: null
   property int selectedBlockCol : 0
   property int selectedBlockIndex : 0
    property real scaling :  timeControll.getScaleScrollChildren()
   property int minBlockWidth : 1000 / scaling
   property int isPlayPauseStop : 2
   // property int torepainting : 1
    property int saveScrollX : 0


   property  bool needToLightSelected : false
  property Repeater p_rep_columns
    property Item p_item_col
  property Item  p_trackbar
   property Item  p_scale_pointer
   property Item  p_context_menu

   property int mX : 0

   property int prevPlayTime : 0



focus: true    


    property bool ctrl_pressed : false
         Keys.onPressed: {
              console.log("AAAAAAAAAAAAAAAAAAAAA " + event.key)
          if(event.modifiers & Qt.ControlModifier) {
               main222.ctrl_pressed = true
              //console.log("AAAAAAAAAAAAAAAAAAAAA " + ctrl_pressed)

              if ((event.key === Qt.Key_S || event.key === 1067) && (event.modifiers & Qt.ShiftModifier))
                        timeControll.emitSaveProject();
              else
                  if ((event.key === Qt.Key_O  || event.key === 1065) && (event.modifiers & Qt.ShiftModifier)) //1065 - 'Щ'
                             timeControll.emitOpenProject();
                  else
                      if ((event.key === Qt.Key_N || event.key === 1058) && (event.modifiers & Qt.ShiftModifier))
                                 timeControll.emitNewProject();
                      else
                          if (event.key === 43)
                              timeControll.zoomPlus()
                          else
                              if (event.key === 45)
                                  timeControll.zoomMinus()
          }

      }
         Keys.onReleased: {
             //ctrl release
                 if( event.key === 16777249) {
                     main222.ctrl_pressed = false
                    //console.log("AAAAAAAAAAAAAAAAAAAAA " + ctrl_pressed)
                     }
             }


    function addTrack()     {
        timeControll.addNewTrack( )
    rep_columns.model +=1
    }

    function removeTrack()    {
        timeControll.removeLastTrack()
    rep_columns.model -=1
item_col.width = (timeControll.getMaxTrackTime() + 31) * main222.scaling
    }

    function play()    {
        if (isPlayPauseStop === 2)
            scroll.flickableItem.contentX = 0;
        else if (isPlayPauseStop === 1)
        {
             scale_pointer.x = timeControll.getPlayTime()/main222.scaling;
           scroll.flickableItem.contentX = main222.saveScrollX
        }
        main222.isPlayPauseStop = 0


        scroll.enabled = false
         scale_pointer.enabled = false
        tollbar.p_button_RemoveTrack.enabled = false
        tollbar.p_button_RemoveTrack.enabled = false

    }
    function pause()    {
        main222.saveScrollX = scroll.flickableItem.contentX
main222.isPlayPauseStop = 1

        scroll.enabled = true
       scale_pointer.enabled = true
       tollbar.p_button_RemoveTrack.enabled = true
       tollbar.p_button_RemoveTrack.enabled = true
    }
    function stop()    {
      //  scale_pointer.x =
main222.isPlayPauseStop = 2

        scroll.enabled = true
       scale_pointer.enabled = true
       tollbar.p_button_RemoveTrack.enabled = true
       tollbar.p_button_RemoveTrack.enabled = true
//scale_pointer.x = timeControll.getMaxTrackTime() + scale_pointer.width/2 - scroll.flickableItem.contentX;
    }

    function setScalePointerPos(xx)    {
        scale_pointer.x = xx

    }

    function updateTracksModel()
    {
        scaling = timeControll.getScaleScrollChildren()
        rep_columns.model = 0
         rep_columns.model =  timeControll.getTracksNumber()
        item_col.width = timeControll.getMaxTrackTime()
        if (main222.needToLightSelected)
        {
            rep_columns.itemAt(main222.selectedBlockCol).setColorize(main222.selectedBlockIndex,"#8000FF00")
        }
        main222.p_trackbar.globalRep.updateModel()

        //repka.updateModel();

    }

     Connections {
       target: timeControll

      onPlaySignal: {
            main222.play()
          scale_pointer.x = 0


       }
      onPauseSignal: {
            main222.pause()
       }
       onStopSignal: {
            main222.stop()


       }
       onSetScalePointerPosSignal: {
            main222.setScalePointerPos(value * main222.scaling)
       }

       onUpdateSignal:  {
           if (main222.isPlayPauseStop === 0 )
           {
               var play_time = timeControll.getPlayTime();
     scale_pointer.x += (play_time - main222.prevPlayTime)/main222.scaling;
               main222.prevPlayTime = play_time;
   //  (timeControll.getPlayTime() - scroll.flickableItem.contentX)/main222.scaling + 15 ;
               timeControll.calcPointedBlocksAtTime()
              // console.log("timer value: " +timeControll.getPlayTime())
           }
       }

       onUpdateModel: {
           /*rep_columns.model = 0
            rep_columns.model =  timeControll.getTracksNumber();
           item_col.width = timeControll.getMaxTrackTime()
           // main222.p_trackbar.globalRep.updateModel()

           //repka.updateModel();*/
           main222.scaling = timeControll.getScaleScrollChildren();
           main222.updateTracksModel();
           console.log("AAAAAAAAAAAAAAAAAA " +  main222.scaling)
       }


       onResetProjectSignel: {
timeControll.setScaleScrollChildren(0) //it have protection from small values
           main222.scaling = timeControll.getScaleScrollChildren();
          main222.selectedBlockCol = -1
            main222.selectedBlockIndex = -1
          // rep_columns.model = timeControll.getTracksNumber()
           console.log("1111111111111111111")
           // main222.p_trackbar.globalRep.updateModel()
           main222.p_scale_pointer.x = 26
       timeControll.setIsProjectChanged(false)

           main222.updateTracksModel()
       }


       }





    Rectangle {
        id: time_scale
        property int division : 50
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

                text: {
                    if (main222.scaling >= 10)
                         return Math.round(time_scale.division * index * main222.scaling)/1000 + " sec"
                    else
                        return Math.round(time_scale.division * index * main222.scaling) + " ms"

                }
                y:   0
                width:  time_scale.division
                height: time_scale.height/2
                 color: "white"
                 anchors.right: ver_line.left


                 //font { pixelSize: 10 }

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
                var contentWidth =   scroll.flickableItem.contentWidth - width/2
                if (x > contentWidth)
                    x = contentWidth
                else
                {


                var real_time = timeControll.getMaxTrackTime() / main222.scaling
               var temp = scroll.width-30    // real_time - scroll.flickableItem.contentX + width
                if (x  > temp )
                {
                  console.log("HAAAAAAAAAAA")

                    scroll.flickableItem.contentX += (x - temp)
                    var sad = real_time - scroll.width +50 // scroll.flickableItem.contentWidth - scroll.width + 10
                    if (scroll.flickableItem.contentX  >  sad)
                            scroll.flickableItem.contentX = sad;
                     x = temp
                  // timeControll.stop();
                   // main222.stop()
                }
            }

              /*  else
                {
                temp = scroll.width -width - 3  /// scroll.x + scroll.width - main222.p_trackbar.width*1.4
              //   console.log("10007")
                if (x> temp)
                {
                   // console.log("DAAAAAAAAAAAAAAAAAAAAAAAAAAAAAa")
                    if (real_time  >= scroll.width  )
                    {
                        // console.log("10008")
                    scroll.flickableItem.contentX += (x - temp)
                    var sad = real_time - scroll.width +17 // scroll.flickableItem.contentWidth - scroll.width + 10
                    if (scroll.flickableItem.contentX  >  sad)
                    {
                         //console.log("10009")
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
            }*/
            }

timeControll.setScalePointerPos((x  -20 + scroll.flickableItem.contentX)* main222.scaling);
         //   console.log("JJJJJJJJJJJJJJJJ " + timeControll.getScalePointerPos())
            if (main222.isPlayPauseStop !== 0)
            {
            timeControll.calcPointedBlocks();
               //console.log("AAAAAAAAAAAWWWWWWWWWWWWWWWWWWWWWWW")
                //console.log("getScalePointerPos = " + timeControll.getScalePointerPos())

            }

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
             //property int baba: scroll.flickableItem.contentWidth
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
                    property Item p_columns
                    property Item p_trackbar
                   // width: childrenRect.width
                    height: childrenRect.height
                    color: "gray"
                    onWidthChanged: {
                        if (time_scale.width < width  ) //1234
                        {
                            time_scale.width = width  ;
                            time_scale_rep.model = time_scale.width/ time_scale.division + 2
                        }
                         //console.log("122  item_col.width=" + item_col.width)
                    }
                    Column {
                          id: columns
                          width:  timeControll.getMaxTrackTime()
                          property Repeater globalRep
                          spacing: 2
                          Repeater {
                          id: rep_columns
                          model: timeControll.getTracksNumber()
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
        model = 0
        item_col.width = (timeControll.getMaxTrackTime()) / main222.scaling + 31
            //timeControll.update();
        model =  timeControll.getTrackSize(bar_track.mIndex)

        if (main222.needToLightSelected)
        {
            rep_columns.itemAt(main222.selectedBlockCol).setColorize(main222.selectedBlockIndex,"#8000FF00")
            // console.log("selectedBlockIndex=" + main222.selectedBlockIndex)
       // main222.p_scale_pointer.x =rep_columns.itemAt(main222.selectedBlockCol).getBlockX(main222.selectedBlockIndex)
       //main222.mX//


        }
        console.log("6666666666666666666")
        timeControll.calcPointedBlocks();
        console.log("77777777777777777" )
        timeControll.setIsProjectChanged(true)
    }
                                           delegate:
                                           ContentBlock.Block{
                                               id: cool
                                               globalRep : repka
                                               height:  100
                                               mIndex: index
                                                colIndex:  bar_track.mIndex
                                   width:  timeControll.getBlockTime(colIndex, mIndex) / main222.scaling
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

                                           /* var pnt2 = new Point(-1,-1)
                                           timeControll.setSelectedBlockPoint(pnt2)*/
                                          // main222.p_trackbar.globalRep.updateModel()
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
                   width =  timeControll.getMaxTrackTime() / main222.scaling
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



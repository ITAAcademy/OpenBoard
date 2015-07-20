import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtGraphicalEffects 1.0

import "Block" as ContentBlock
import "ToolBar" as ContentToolBar

Rectangle
{
    color: "gray"
    id:main222
    property int clicked_blockId : -1
    property int clicked_blockX : -1
    property int clicked_blockY : -1
    property int drop_blockX : -1
    property int drop_blockY : -1
    property int maIsPressed: 0
    property int dropEntered: 0
    property Item p_item_col

    function addTrack()     {
        console.log("  33333333333333333333333333333333333333333333333")
        timeControll.addNewTrack( )
    rep_columns.model +=1
    }

    function removeTrack()    {
        timeControll.removeLastTrack()
    rep_columns.model -=1
    }

    Row { //scroll + toolbar
        id: toolbar_scroll
        width: parent.width
        height: parent.height


      /*  ContentToolBar.MyScrollView{
            id: scroll
            width: toolbar_scroll.width - tollbar.width
            */
         ScrollView {
              id: scroll
              width: parent.width - tollbar.width
              height: parent.height
              horizontalScrollBarPolicy :Qt.ScrollBarAlwaysOn
              verticalScrollBarPolicy  :Qt.ScrollBarAlwaysOn
             /* Image {
                  width: 4000
                  height: 4000
                  source: "qrc:/E:/Users/Юрий/Desktop/--pNfOnpygs.png"
              }*/
            /*  Rectangle {
               id: time_scale_value
               property int mX: -30
               property int mY: -30
               x: mX
               y: mY
               z: 50
               visible: false
               width: 80
               height: 30
               color: "black"
               border {color: "white"; width: 2}
               Text {
                   anchors.verticalCenter:  time_scale_value.verticalCenter
                   anchors.horizontalCenter: time_scale_value.horizontalCenter
                   text: scrollMA.mouseX + " ms"
                    font { pixelSize: 14 }
                    color: "white"
               }
               Timer {
                   id: timer
                      interval: 500; running: true; //repeat: true
                      onTriggered: {
                          time_scale_value.visible = true;
                      }
                  }
               onMXChanged: {
                   timer.restart();
                   time_scale_value.visible = false;
               }
               onMYChanged: {
                   timer.restart();
                   time_scale_value.visible = false;
               }
              }
              MouseArea {
                  id: scrollMA
                  anchors.fill : parent
                  hoverEnabled: true
                  z: 20


                  onPositionChanged: {
                     time_scale_value.mX = scrollMA.mouseX
                       time_scale_value.mY = scrollMA.mouseY
                  }

              }*/
            on__HorizontalScrollBarChanged:   {
             console.log("333333333333333333333wqfqwegrfwfewq")
            }
            Component.onCompleted: {
                flickableItem.contentY = flickableItem.contentHeight / 2 - height / 2
                            flickableItem.contentX = flickableItem.contentWidth / 2 - width / 2
                //flickableItem.
                   }
              Rectangle {
                  id: time_scale
                  property int division : 50
                  width: 2000//item_col.width
                  height: item_col.height/10
                  color: "gray"

                  x: 0
                  y: main222.height -height - 20
                  z: 200
                  Rectangle {
                      id: hor_line
                  width: time_scale.width
                  height: time_scale.height/10
                  color: "blue"
                  y: time_scale.height/2
                  x:0
                  }
                  Repeater {
                      id: time_scale_rep
                      model: time_scale.width/ time_scale.division
                      delegate:
                      Rectangle{
                          width: time_scale.division

                          Rectangle {
                          id: ver_line
                          height: time_scale.height
                          width: hor_line.height
                          x: time_scale.division - width
                          color: "blue"
                          }
                      }
                  }

              }
              Rectangle {
                    id: item_col
                    property Item p_columns
                    property Item p_trackbar
                    width: childrenRect.width
                    height: childrenRect.height
                    onWidthChanged: {
                        if (width >  time_scale.width)
                        {
                            time_scale.width = width  ;
                            time_scale_rep.model = time_scale.width/ time_scale.division
                        }
                    }
                    Column {
                          id: columns
                          width:  timeControll.getMaxTestWidth()
                          property Repeater globalRep
                          spacing: 2
                          Repeater {
                          id: rep_columns
                          model: 1
                          delegate:
                               Row {
                               id: bar_track
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
                                     height: 200
                                     color: "gray"
                                     Row {
                                       id: blocks
                                       height: 220
                                       Repeater {
                                           id: repka
                                           property bool isDrag : false
                                           model:  timeControll.getTrackSize(trackbar.mIndex)//     bar_track.mIndex)
                                           function updateModel()      {
                                               model = model - 1;
                                               console.log("function updateModel()   ")
                                                    model =  timeControll.getTrackSize(bar_track.mIndex)

                                               }
                                           delegate:
                                           ContentBlock.Block{
                                               id: cool
                                               globalRep : repka
                                               height: 200
                                               mIndex: index
                                                colIndex:  bar_track.mIndex
                                               width:  timeControll.getBlockTime(colIndex, mIndex)

                                               title: timeControll.getBlockKey(colIndex,mIndex)

                                              /* time_scale_valueRecX : time_scale_value.mX
                                               time_scale_valueRecY : time_scale_value.mY*/

                                              /* p_mouse_area.onPositionChanged: {
                                                  time_scale_value.mX = scrollMA.mouseX
                                                    time_scale_value.mY = scrollMA.mouseY
                                               }*/
                                           }
                                           onModelChanged: {                                              
                                                  columns.width =  timeControll.getMaxTrackTime()
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
                                     Component.onCompleted: {
                                     /*    main_root.width = 4000// blocks.childrenRect.width
                                         main_root.height = 200// blocks.childrenRect.height*/
                                     }
                                          }
                                     Component.onCompleted: {
                                    trackbar.globalRep = repka
                                     }
                                 }
                                 }    //
                            }
                   onChildrenRectChanged:  {
                   width =  timeControll.getMaxTrackTime()
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

    }



  /*

    Image {
        x: 30
        source: "qrc:/iphone_toolbar_icons/arrowdown.png"
        height: 100
        width: 1000
    }*/



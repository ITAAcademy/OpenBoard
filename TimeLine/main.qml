import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtGraphicalEffects 1.0

import "Block" as ContentBlock
import "ToolBar" as ContentToolBar

Item
{
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
        timeControll.addNewColumn( )
    rep_columns.model +=1
    }

    function removeTrack()    {
        timeControll.removeLastColumn()
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
              Rectangle {
                    id: item_col
                    property Item p_columns
                    property Item p_trackbar
                    width: childrenRect.width
                    height: childrenRect.height
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
                               /*onIndexChanged: {
                                   console.log("ETO INDEX = " + index)
                               }
                               onMIndexChanged:  {
                                   console.log("ETO MINDEX = " + mIndex)
                                   console.log("ETO INDEX = " + index)
                               }*/
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
                                     Row {
                                       id: blocks
                                       height: 220
                                       Repeater {
                                           id: repka
                                           property bool isDrag : false
                                           model:  timeControll.getColumnSize(trackbar.mIndex)//     bar_track.mIndex)
                                           function updateModel()      {
                                               model = model - 1;
                                               console.log("function updateModel()   ")
                                                    model =  timeControll.getColumnSize(bar_track.mIndex)

                                               }
                                           delegate:
                                           ContentBlock.Block{
                                               id: cool
                                               globalRep : repka
                                               colIndex: trackbar.mIndex
                                               height: 200
                                               width: timeControll.getTestWidth(bar_track.mIndex, index)
                                               mIndex: index
                                               title: timeControll.getTest(trackbar.mIndex,index)
                                           }
                                           onModelChanged: {
                                                  columns.width =  timeControll.getMaxTestWidth()
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
                   width =  timeControll.getMaxTestWidth()
                    console.log(" timeControll.getMaxTestWidth() = " +  width)
                   }
                    } /* rep_columns end */
              }
              Component.onCompleted: {

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



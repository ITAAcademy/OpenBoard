import QtQuick 2.4
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0



Rectangle{
    id: root
   //; color: "red"// "#343434"
    property int mIndex
    property int colIndex
    property int xChange: 0
    property bool bChangeSize: false
    property string title:  "value"
    property Repeater globalRep
    property string colorKey : "green"
    property ColorOverlay p_color_overlay
    property bool double_click : false
    property Item p_trackbar
    property Item p_bar_track
    property Item  p_main222
    property Item  p_drag

    property int animation_scale_normal_toYpos : 0
    property int animation_scale_normal_toXpos : 0

    property real animation_scale_normal_FromScale : 0

    property int animation_scale_normal_FromYpos_cuz : 0
    property int animation_scale_normal_FromXpos_cuz  : 0
    property Item p_background_rec
    property ParallelAnimation p_animation_scale_normal
        property int anim_run_value : 0

    function animRunX(value)
    {
        anim_run_value = value
        animation_run_x.running = true
    }

    NumberAnimation on x {
        id: animation_run_x
        running: false;
        from: root.x
        to: root.x + root.anim_run_value
        duration: 200
    }

    RectangularGlow {
       id: shadow
       height: root.height
       width: root.width
      /* x:root.border.width*1.2
       y:x*/
       //anchors.right: root.right
       x:root.width -width -  4*root.border.width
        y: root.height -height -  4*root.border.width
       visible: false
       color: "black"
       opacity: 0.5
      // scale: 0.8
       z: 1
       glowRadius: 5
       spread: 0.00002
       // cornerRadius: shadow.radius + glowRadius
    }
   /* RectangularGlow {
          id: effect
          anchors.fill: shadow
          glowRadius: 10
          spread: 0.00002
          color: "black"
         // opacity: 0.5
          cornerRadius: shadow.radius + glowRadius
      }*/

    Rectangle
    {
        id: background_rec
        z: 2
        property real  border_width : 2
    // border { color: "white" ; width: 2 }
     height: root.height// - 2*background_rec.border.width
     width: root.width
     color: "green"
     Component.onCompleted: {
         root.p_background_rec = background_rec
     }


    Image {
        id: background
//         x:root.border.width + 1
//         y:x
         //anchors.margins: background_rec.border.width

        width: root.width; height: root.height
       fillMode: Image.TileHorizontally
       source: "qrc:/iphone_toolbar_icons/black_tree.png"
       visible: true


       Image {
           id: icon
           source:  "image://imageProvider/" + root.colIndex + "+" + root.mIndex + "+ " + (Math.round(Math.random(9999999) * 10000));
           width: background.width;
           height: background.height
          // x:root.border.width + 1
           //y:root.border.width + 1
           visible:  true
          // anchors.fill: parent

           ColorOverlay {
               id: icon_coloroverlay
                  anchors.fill: icon
                  source: icon
                  color: "#00000000"
                  z: 1
                  enabled: false
              }
           Rectangle {
               id: border_image
               width: background.width; height: background.height
               border.width:  background_rec.border_width  ;
             border.color: "white"
             color: "transparent"
               z: 2
           }
           Text {
               id: name
               anchors.margins: 3
               anchors.centerIn: border_image
              // x: icon.width/2 - width/2
               text: root.title
               font.pixelSize: 1
               color: "white"
               style: Text.Outline;
               styleColor: "black"
               onTextChanged: {
                   name.font.pixelSize = (root.width*1.2)/text.length;
                   if(name.font.pixelSize > root.height*0.7)
                       name.font.pixelSize = root.height*0.7

               }
               z: 3
           }

           //z:1
       }

    }
    onScaleChanged: {
        shadow.height  = root.height * scale
        shadow.width  = root.width * scale

    }
    NumberAnimation on scale {
        id:animation_scale_small;
         property int anim_time : 200
        running: false;
        to: 0.8;
        duration: anim_time
    }
    NumberAnimation on x {
        id: animation_scale_x;
        running: false;
        to: root.border.width  - width * 0.05;
        duration: animation_scale_small.anim_time
    }

    NumberAnimation on y {
        id: animation_scale_y;
        running: false;
        to: root.border.width  - height * 0.05;
        duration: animation_scale_x.duration
    }
    ParallelAnimation{
        id:animation_scale_normal;
        running: false;
        onStopped:  {
                root.globalRep.updateModel();
        }

        property int anim_time : 200
        Component.onCompleted: {
            p_animation_scale_normal = animation_scale_normal
        }

        NumberAnimation  {
            target: background_rec
            property: "scale"
            from: animation_scale_normal_FromScale;
            to: 1;
            duration: animation_scale_normal.anim_time
        }
        NumberAnimation  {
            target: root
            property: "x"
            from: animation_scale_normal_FromXpos_cuz
            to: animation_scale_normal_toXpos;
            duration: animation_scale_normal.anim_time
        }
        NumberAnimation  {
            target: root
            property: "y"
             from: animation_scale_normal_FromYpos_cuz
            to: animation_scale_normal_toYpos;
            duration: animation_scale_normal.anim_time
        }
    }


    }




    radius: 3
    clip: true
    color: "transparent"
    anchors.leftMargin: 15






    function updateTrackWhereIsBlock()
    {
        globalRep.updateModel()
    }



    function hideMenu()
    {
        context_menu.closeIt()
    }


    function repaint()
    {
        icon.source = "image://imageProvider/" + root.colIndex + "+" + root.mIndex + "+ " + Math.random(1000000);
    }


    // property Item  p_main222


 //   property int time_scale_valueRecX
   // property int time_scale_valueRecY
    /*radius: 0
    border.width: 0
    border.color: "green"
    anchors.topMargin: 0
    anchors.leftMargin: 0*/
z: 0
    onWidthChanged: {
        if (width < main222.minBlockWidth)
            width = main222.minBlockWidth

       /* if (width < height* timeControll.getScaleScrollChildren())
                icon.width = width;
        else*/
            icon.width = icon.height;

       /* var temp = width + timeControll.getBlockStartTime(colIndex,mIndex) > scroll.width
        if (temp)
           scroll.flickableItem.y = temp */

       // timeControll.setBlockTime(colIndex,mIndex,width)

        //// //console.log("333 timeControll.setBlockTime " + colIndex + " " + mIndex + " " + width)
         //timeControll.setBlockTime(mainwindow.columnIndex,mainwindow.blockIndex,block_width_value.value)
    }
    onXChanged: {
        timeControll.setBlockStartTime(root.colIndex,root.mIndex, x * main222.scaling)
    }





    Drag.active: mouseArea.drag.active
    Drag.hotSpot.x: 10
    Drag.hotSpot.y: 10
//onYChanged: y=0;

    MouseArea {
        id: mouseArea
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        drag.target: root
        property int oldMouseX
        property bool isDragged : drag.active
        anchors.fill: parent
        enabled: !globalRep.isDrag
        hoverEnabled: true

        onIsDraggedChanged:  {

           if (isDragged)
            {
                 cursorShape = Qt.OpenHandCursor
                 animation_scale_small.running = true
                 animation_scale_x.running = true
                 animation_scale_y.running = true
                 shadow.visible = true
            }
            else
            {


                if(root.p_main222.needUpdateModelWhereBlockDroped)
                {
                    root.p_main222.dropEnteredBlockItemGlobalRep.updateModel();
                    root.p_main222.needUpdateModelWhereBlockDroped = false
                }
                 //globalRep.updateModel();
                 //var sel_blocka = root.p_main222.selectedBlock

                root.animation_scale_normal_FromXpos_cuz = root.x
                root.animation_scale_normal_FromYpos_cuz = root.y

                root.animation_scale_normal_FromScale = background_rec.scale

                if (main222.dropEnteredBlockIndex !== -1)
                {
                    var zdvig = 0;
                    if (main222.doZdvigWhenNormalAnim)
                        zdvig =  main222.dropEnteredBlock.width //666
                root.animation_scale_normal_toXpos = main222.dropEnteredBlock.x +
                                    main222.zdvigWhenNormalAnim
                root.animation_scale_normal_toYpos = main222.dropEnteredBlock.y
                }
//                root.animation_scale_normal_toXpos = -100
//                root.animation_scale_normal_toYpos = 50


                root.p_bar_track.z += 200 //888
                root.z += 200
                //if in one tracks
               // globalRep.moveBlocksForAnim(root.mIndex,divider.pos_to_append.y,-1,root.width) //899

                animation_scale_normal.running = true

//function moveBlocksForAnim( from, to,  left_right,  value)

                root.p_bar_track.z -= 200 //888
                root.z -= 200


//root.p_main222.root_isDragChanged = true;
            }


        }

        Timer {
            id: double_click_timer
               interval: 250; running: false; repeat: false
               onTriggered: root.double_click = false
           }

        onMouseXChanged: {
           // if (context_menu.visible === false) //123rr

            {
            if(globalRep.isDrag === false &&  mouseX > root.width * 0.9) //mouseX < root.width * 0.1 ||/
            {
                cursorShape = Qt.SizeHorCursor;
//            drop.visible = false;
//                drop.enabled = false;
            //    root.Drag.active =  false
                //console.log("eeeeeeeeeeeeeeeeeeeeeeeeeeee")

              }
            else
            {
                cursorShape = Qt.ArrowCursor;
 //console.log("ttttttttttttttttttttttttttt")
             //drop.enabled = true;
              //   drop.visible = true;
              //  root.Drag.active =  mouseArea.drag.active
            }

            xChange = oldMouseX - mouseX;

            if(bChangeSize)
            {
                root.width -= xChange;
                //timeControll.setTestWidth(bar_track.index,root.width, mIndex);

            }
            oldMouseX = mouseX;
            }
        }


       onPressed: {
            main222.dropEntered = 0
           root.animation_scale_normal_toXpos = root.x
           root.animation_scale_normal_toYpos = root.y
           divider.y = (root.height + main222.p_columns.spacing) * root.colIndex
                   + time_scale.height - scroll.flickableItem.contentY
          divider.x =  root.x + root.width - divider.width/2 + tollbar.width

           divider.pos_to_append.x = root.colIndex
           divider.pos_to_append.y =  root.mIndex

           main222.dropEnteredBlockIndex = -1

           timeControll.setSelectedBlockPoint(root.colIndex,root.mIndex);

           main222.selectedBlockCol = root.colIndex
           main222.selectedBlockIndex = root.mIndex

          main222.selectedBlock = root;
           context_menu.globalRep = root.globalRep

           // console.log("AAAAAAAAAAAAAAAAAA "+ main222.selectedBlockCol +" " + main222.selectedBlockIndex)
            if(main222.selectedBlock !== null)
                main222.selectedBlock.hideMenu();
            timeControll.emitFocusFoundSignal();
            //console.log("AAAAAAAAAAAAAAA " + timeControll.getBlockStartTime(root.colIndex,root.mIndex))
             main222.p_scale_pointer.x = mouseX + root.x - scroll.flickableItem.contentX + main222.p_scale_pointer.width //1234

            main222.p_scale_pointer.x+=1


            main222.needToLightSelected = true
            for (var y=0; y< rep_columns.model; y++)
                 rep_columns.itemAt(y).abortColorize()

            icon_coloroverlay.color = "#8000FF00"


           // blocks.itemAt(i).icon_coloroverlay.color = "#00000000"
            //columns.childAt()
            // //console.log("onPressed: mIndex="+mIndex+" colIndex="+ colIndex + " time = " + timeControll.getBlockTime(colIndex,mIndex))
            if (mouse.button == Qt.RightButton)
            {
               context_menu.showIt(main222.p_scale_pointer.x, mouseY + root.colIndex * (root.height + 2)
                                 - scroll.flickableItem.contentY,root)
                drag.target = null
            }
        else
            {
                if (root.double_click )
                {
                    //context_menu.show(-1000, -1000,root.globalRep)
                   context_menu.showEditBlock()
                   root.double_click = false
                }
                else
                {
                     root.double_click = true
                    double_click_timer.running = true

                    context_menu.closeIt()
                drag.target = root
    // //console.log("onPressed");
            drop.visible = false;
             drop.enabled = false;
            if( mouseX > root.width * 0.9)
            {
                bChangeSize = true;
                mouseArea.drag.target = null
            }
            else
            {
            globalRep.isDrag = true;                

                //root.border.color  = "transparent"





              /*   mouseY + root.colIndex * (root.height + 2)
                                                 - scroll.flickableItem.contentY  */

                 main222.maIsPressed = 1
                main222.clicked_blockId = root.mIndex
                main222.clicked_blockX = root.x
                main222.clicked_blockY = root.y
                root.z += 200
                 root.p_bar_track.z += 200
                //main222.p_trackbar_which_block_dragged = root.p_trackbar
                //globalRep.z += 200

            }
            }
        }
        }
        onReleased: {
//root.border.color = "white"
            main222.p_scale_pointer.x = mouseX + root.x - scroll.flickableItem.contentX + main222.p_scale_pointer.width //1234
           // animation_scale_normal.running = true


            if (globalRep.isDrag)
            {
                       root.p_bar_track.z -= 200 //888
                //main222.p_trackbar_which_block_dragged
                root.globalRep.z -= 200
              divider.visible = false
              //  if (main222.dropEnteredBlockIndex !== -1)
                {
                   if (main222.dropEntered)
                    {
                        //timeControll.reverseBlocks(root.colIndex,root.mIndex,main222.clicked_blockId)
       /* if (main222.selectedBlockIndex ===  divider.pos_to_append.y - 1 && !main222.left_rigth_entered)
          console.log("main222.selectedBlockIndex ===  divider.pos_to_append.y - 1 && main222.left_rigth_entered)")
*/
                       var track_size =  timeControll.getTrackTime(root.colIndex)

                           var out_console = true
                main222.zdvigWhenNormalAnim =  0

           if ( main222.selectedBlockIndex + 1 === divider.pos_to_append.y)
           {
               if (main222.block_zayshow_sprava)
               {
                   if (main222.left_rigth_entered)
                   {
                       if (main222.exitedFromDropArea)
                       {
                           if(out_console) console.log("555555555555555555 ok")
                           root.globalRep.moveBlockForAnim(divider.pos_to_append.y,-root.width)
                       }
                       else
                       {
                           if(out_console) console.log("6666666666666666666 ok")
                           root.globalRep.moveBlockForAnim(divider.pos_to_append.y,-root.width)
                       }
                   }
                   else
                   {
                       if (main222.exitedFromDropArea)
                       {
                           if(out_console) console.log("777777777777777 ok")
                           //root.globalRep.moveBlockForAnim(root.mIndex,-root.width)
                           divider.pos_to_append.y -=1
                           main222.zdvigWhenNormalAnim = -root.width
                       }
                       else
                       {
                           if(out_console) console.log("RRRRRRRRRRRRRRRRRRRRRRR ok")
                           //root.globalRep.moveBlockForAnim(divider.pos_to_append.y,-root.width)
                           divider.pos_to_append.y -=1
                           main222.zdvigWhenNormalAnim = -root.width
                       }
                   }
               }
               else //ZAYSHOW ZLIVA
               {
                   if (main222.left_rigth_entered)
                   {
                       if (main222.exitedFromDropArea)
                       {
                           if(out_console) console.log("888888888888888 ok")
                           root.globalRep.moveBlockForAnim(divider.pos_to_append.y,-root.width)
                       }
                       else
                       {
                           if(out_console) console.log("OOOOOOOOOOOOOO ok")
                              root.globalRep.moveBlockForAnim(divider.pos_to_append.y,-root.width)
                           //main222.zdvigWhenNormalAnim = root.width
                          //
                       }
                   }
                   else
                   {
                       if (main222.exitedFromDropArea)
                       {
                           if(out_console) console.log("PPPPPPPPPPPPPP ok")
                           divider.pos_to_append.y -= 1
                           main222.zdvigWhenNormalAnim = -root.width
                       }
                       else
                       {
                           if(out_console) console.log("SSSSSSSSSSSSSSSSSSSS ok")
                         divider.pos_to_append.y -=1
                           main222.zdvigWhenNormalAnim = -root.width
                       }
                   }
               }
           }
           else
           if (main222.selectedBlockIndex < divider.pos_to_append.y)
           {
               if (main222.block_zayshow_sprava)
               {
                   if (main222.left_rigth_entered)
                   {
                       if (main222.exitedFromDropArea)
                       {
                           if(out_console) console.log("111111111111111 ok")
                           root.globalRep.moveBlocksForAnim(root.mIndex, divider.pos_to_append.y,-root.width)
                       }
                       else
                       {
                           if(out_console) console.log("2222222222222222 ok")
                           root.globalRep.moveBlocksForAnim(root.mIndex, divider.pos_to_append.y,-root.width)

                       }
                   }
                   else
                   {
                       if (main222.exitedFromDropArea)
                       {
                           if(out_console) console.log("33333333333333333 has declared top")
                       }
                       else
                       {
                           if(out_console) console.log("TTTTTTTTTTTTTTTTTTT ok")
                           root.globalRep.moveBlocksForAnim(root.mIndex, divider.pos_to_append.y,-root.width)
                       }
                   }
               }
               else
               {
                   if (main222.left_rigth_entered)
                   {
                       if (main222.exitedFromDropArea)
                       {
                           if(out_console) console.log("4444444444444444444 ok")
                           main222.zdvigWhenNormalAnim = -root.width
                           root.globalRep.moveBlocksForAnim(root.mIndex,
                                             divider.pos_to_append.y,-root.width)
                       }
                       else
                       {
                           if(out_console) console.log("UUUUUUUUUUUUUUUUUUU ok")
                           //ok
                           root.globalRep.moveBlocksForAnim(root.mIndex,divider.pos_to_append.y,-root.width)
                       }
                   }
                   else
                   {
                       if (main222.exitedFromDropArea)
                       {
                           if(out_console) console.log("VVVVVVVVVVVVVVVVVV ok")
                           divider.pos_to_append.y -=1
                           root.globalRep.moveBlocksForAnim(root.mIndex, divider.pos_to_append.y,-root.width)
                           main222.zdvigWhenNormalAnim = -root.width
                       }
                       else
                       {
                           if(out_console) console.log("WWWWWWWWWWWWWWWWWWWW ok")
                           divider.pos_to_append.y -=1
                           main222.zdvigWhenNormalAnim = -root.width
                           root.globalRep.moveBlocksForAnim(root.mIndex,divider.pos_to_append.y,-root.width)
                       }
                   }
               }
           }
           else
           if (main222.selectedBlockIndex === divider.pos_to_append.y)
           {
               if (main222.block_zayshow_sprava)
               {
                   if (main222.left_rigth_entered)
                   {
                       if (main222.exitedFromDropArea)
                       {
                           if(out_console) console.log("9999999999999999")
                       }
                       else
                       {
                           if(out_console) console.log("AAAAAAAAAAAAAAAA")
                       }
                   }
                   else
                   {
                       if (main222.exitedFromDropArea)
                       {
                           if(out_console) console.log("BBBBBBBBBBBBBBBBBB")
                       }
                       else
                       {
                           if(out_console) console.log("XXXXXXXXXXXXXXXXXXXXXX")
                       }
                   }
               }
               else //zayshow zliva
               {
                   if (main222.left_rigth_entered)
                   {
                       if (main222.exitedFromDropArea)
                       {
                           if(out_console) console.log("YYYYYYYYYYYYYYYYYYYY")
                       }
                       else
                       {
                           if(out_console) console.log("ZZZZZZZZZZZZZZZZ")
                       }
                   }
                   else
                   {
                       if (main222.exitedFromDropArea)
                       {
                           if(out_console) console.log("!!!!!!!!!!!!!!!!!!!!!!!!")
                       }
                       else
                       {
                           if(out_console) console.log("@@@@@@@@@@@@@@@@@@@")
                       }
                   }
               }
           }
           else
           if (main222.selectedBlockIndex === divider.pos_to_append.y + 1)
           {
               if (main222.block_zayshow_sprava)
               {
                   if (main222.left_rigth_entered)
                   {
                       if (main222.exitedFromDropArea)
                       {
                           if(out_console) console.log("DDDDDDDDDDDDDDDDD ok")
                           main222.zdvigWhenNormalAnim = root.width
                           divider.pos_to_append.y +=1
                       }
                       else
                       {
                           if(out_console) console.log("EEEEEEEEEEEEEEEE ok")
                            divider.pos_to_append.y +=1
                           main222.zdvigWhenNormalAnim = root.width
                       }
                   }
                   else
                   {
                       if (main222.exitedFromDropArea)
                       {
                           if(out_console) console.log("FFFFFFFFFFFFFFFF ok")
                           root.globalRep.moveBlockForAnim(divider.pos_to_append.y,root.width)
                           //main222.zdvigWhenNormalAnim = root.width
                       }
                       else
                       {
                           if(out_console) console.log("#################### ok")
                           //main222.zdvigWhenNormalAnim = root.width
                           root.globalRep.moveBlockForAnim(divider.pos_to_append.y, root.width)
                       }
                   }
               }
               else
               {
                   if (main222.left_rigth_entered)
                   {
                       if (main222.exitedFromDropArea)
                       {
                           if(out_console) console.log("GGGGGGGGGGGGGGGGGGG ok")
                           main222.zdvigWhenNormalAnim = root.width
                           divider.pos_to_append.y +=1
                       }
                       else
                       {
                           if(out_console) console.log("$$$$$$$$$$$$$$$$$$$ ok")
                           divider.pos_to_append.y +=1
                           main222.zdvigWhenNormalAnim = root.width
                       }
                   }
                   else
                   {
                       if (main222.exitedFromDropArea)
                       {
                           if(out_console) console.log("%%%%%%%%%%%%%%%")
                           main222.zdvigWhenNormalAnim = root.width
                       }
                       else
                       {
                           if(out_console) console.log("^^^^^^^^^^^^^^^^ ok")
                           root.globalRep.moveBlockForAnim(divider.pos_to_append.y,root.width)
                       }
                   }
               }
           }
           else
           if (main222.selectedBlockIndex > divider.pos_to_append.y )
           {
               if (main222.block_zayshow_sprava)
               {
                   if (main222.left_rigth_entered)
                   {
                       if (main222.exitedFromDropArea)
                       {
                           if(out_console) console.log("HHHHHHHHHHHHHHHHHH ok")
                           divider.pos_to_append.y +=1
                           main222.zdvigWhenNormalAnim = root.width
                           root.globalRep.moveBlocksForAnim( divider.pos_to_append.y,root.mIndex,root.width)
                       }
                       else
                       {
                           if(out_console) console.log("IIIIIIIIIIIIIIIIIIIIIII ok")
                           divider.pos_to_append.y +=1
                           main222.zdvigWhenNormalAnim = root.width
                           root.globalRep.moveBlocksForAnim( divider.pos_to_append.y,root.mIndex,root.width)
                       }
                   }
                   else
                   {
                       if (main222.exitedFromDropArea)
                       {
                           if(out_console) console.log("JJJJJJJJJJJJJJJJJJJJ ok")
                           root.globalRep.moveBlocksForAnim(divider.pos_to_append.y,root.mIndex,root.width)
                       }
                       else
                       {
                           if(out_console) console.log("MMMMMMMMMMMMMMM ok")
                           root.globalRep.moveBlocksForAnim(divider.pos_to_append.y,root.mIndex,root.width)
                           //ok
                       }
                   }
               }
               else
               {
                   if (main222.left_rigth_entered)
                   {
                       if (main222.exitedFromDropArea)
                       {
                           if(out_console) console.log("NNNNNNNNNNNNNNNNNNNNNNNNNNN ok")
                           divider.pos_to_append.y += 1
                           main222.zdvigWhenNormalAnim = root.width
                           root.globalRep.moveBlocksForAnim( divider.pos_to_append.y,root.mIndex,root.width)
                       }
                       else
                       {
                           if(out_console) console.log("&&&&&&&&&&&&&&&&&&&&&& ok")
                           divider.pos_to_append.y += 1
                           main222.zdvigWhenNormalAnim = root.width
                           root.globalRep.moveBlocksForAnim( divider.pos_to_append.y,root.mIndex,root.width)
                       }
                   }
                   else  // move from right to left, zayshow zliva, main222.selectedBlockIndex > divider.pos_to_append.y
                   {
                       if (main222.exitedFromDropArea)
                       {
                           if(out_console) console.log("********************* ok")
                           root.globalRep.moveBlocksForAnim( divider.pos_to_append.y,root.mIndex,root.width)
                       }
                       else
                       {
                           if(out_console) console.log("(((((((((((()))))))))))) ok")
                           root.globalRep.moveBlocksForAnim( divider.pos_to_append.y,root.mIndex,root.width)
                       }
                   }
               }
           }






           /* if (main222.selectedBlockIndex > divider.pos_to_append.y  && main222.left_rigth_entered)
                divider.pos_to_append.y += 1*/
            if (main222.selectedBlockCol === main222.dropEnteredTrackIndex)
            {
                  timeControll.moveBlockFromTo(main222.selectedBlockCol,
                                         main222.selectedBlockIndex,  divider.pos_to_append.y);
                //console.log("11111111111111111111111111111111")
                main222.selectedBlockIndex =  divider.pos_to_append.y
               // frama.p_main222.selectedBlockCol = root.colIndex
            }
            else
            {
                //divider.pos_to_append.y +=2
                timeControll.moveBlockFromTo(main222.selectedBlockCol,
                  main222.selectedBlockIndex,main222.dropEnteredTrackIndex,  divider.pos_to_append.y);

                main222.needUpdateModelWhereBlockDroped = true
                //console.log("22222222222222222222222222222222222222")
                 main222.selectedBlockIndex =  divider.pos_to_append.y //333
                frama.p_main222.selectedBlockCol = main222.dropEnteredTrackIndex
            }



            timeControll.setSelectedBlockPoint(main222.selectedBlockCol,main222.selectedBlockIndex)

            }
                }
                //globalRep.updateModel();
                 globalRep.isDrag = false
            }
            else
             if(bChangeSize)
            {
                mouseArea.drag.target = root;
                 timeControll.setBlockTime(colIndex, mIndex,root.width * main222.scaling);
                // item_col.width = timeControll.getMaxTrackTime()// item_col.childrenRect.width             

                 bChangeSize = false;
    ///console.log("2222222222222");
            }

             drop.visible = true;
             drop.enabled = true;
            shadow.visible = false


             cursorShape = Qt.ArrowCursor;


        }
        onEntered: {
           // // //console.log(mouseX + " YY " + mouseY)
        }
    }






    DropArea {
        id: drop
        enabled : true
        visible: true
         anchors.fill: parent
    onEntered: {
        main222.exitedFromDropArea = false
         main222.dropEnteredBlockIndex = root.mIndex
        main222.dropEnteredTrackIndex = root.colIndex
        main222.dropEnteredBlock = root


        main222.dropEnteredBlockItemGlobalRep = root.globalRep
        main222.left_rigth_entered = false
        main222.dropEntered = 1
        var temp = main222.selectedBlock.x - root.x - root.width/2
        if (temp > 0 )
            main222.block_zayshow_sprava = true
        else
            main222.block_zayshow_sprava = false
        divider.pos_to_append.x = root.colIndex



    }
    onExited: {
        main222.exitedFromDropArea = true
        if (root.mIndex === 1)
            main222.dropEnteredBlockIndex = main222.selectedBlockIndex
        icon_coloroverlay.color = "#00000000"

            }
    onPositionChanged: {
          {
            divider.visible = true
            var temp = main222.selectedBlock.x - root.x - root.width/2
            var move_y_pos = (root.height + main222.p_columns.spacing) * root.colIndex
                    + time_scale.height - scroll.flickableItem.contentY

              if (temp > 0  )
              {
                //main222.block_zayshow_sprava = true
                    //divider.x = root.x + root.width - divider.width/2 + tollbar.width
                 /* divider.y = root.height + columns.spacing) * root.colIndex
                          + time_scale.height - scroll.flickableItem.contentY*/


                 divider.moveTo(root.x + root.width - divider.width/2 + tollbar.width,
                           move_y_pos )

                  main222.left_rigth_entered = true
                  divider.pos_to_append.y = root.mIndex
                 // console.log("onPositionChanged: right " + divider.pos_to_append.y)
              }
              else
              {
                      //main222.block_zayshow_sprava = false
                  //divider.x = root.x - divider.width/2 + tollbar.width
                     divider.moveTo(root.x - divider.width/2 + tollbar.width,
                               move_y_pos )

                main222.left_rigth_entered = false
                divider.pos_to_append.y = root.mIndex
                //console.log("onPositionChanged: left " + divider.pos_to_append.y)

              }
          }
    }

    }
    Component.onCompleted: {
        root.p_color_overlay = icon_coloroverlay
    }
}



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
    property int type : timeControll.getBlockTypeIdInt(colIndex,mIndex)
    onTypeChanged: {
        if (type == 5)
        {
            drop.visible = false
            background_rec.visible = 1 //-=-=
            background_rec.enabled = true
            icon_coloroverlay.visible = false
            mouseArea.enabled = false
        }
        else
        {
            drop.visible = true
            background_rec.visible = true //-=-=
            background_rec.enabled = true
            icon_coloroverlay.visible = true
            mouseArea.enabled = true
        }

    }
    property color  p_border_color
    onP_border_colorChanged: {
        border_image.border.color = p_border_color
    }

    property int animation_scale_normal_toYpos : 0
    property int animation_scale_normal_toXpos : 0

    property Item  p_divider
    property real animation_scale_normal_FromScale : 0

    property int animation_scale_normal_FromYpos_cuz : 0
    property int animation_scale_normal_FromXpos_cuz  : 0
    property Item p_background_rec
    property ParallelAnimation p_animation_scale_normal
    property Item p_icon_coloroverlay
    property int anim_run_value : 0

    Component.onCompleted: {
        //console.log(" Component.onCompleted"                    )
        /*type = timeControll.getBlockTypeId(colIndex,mIndex)
        console.log("type = " + type)*/
        root.p_color_overlay = icon_coloroverlay
    }

    function animRunX(value)
    {
        console.log("function animRunX(value) = " +root.anim_run_value)
        root.anim_run_value = value
        animation_run_x.running = true //9999
    }




    /* NumberAnimation on x {
        id: animation_run_x
        running: false;
        from: root.x
        to: root.x + root.anim_run_value
        duration: 200
    }*/

    ParallelAnimation {
        id: animation_run_x

        running: false;
        NumberAnimation  {
            target: root
            property: "x"
            id: animation_run_xX
            from: root.x
            to: root.anim_run_value
            duration: 200
        }
        /* NumberAnimation  {
              target: root
              property: "y"
              running: false;
              from: root.y
              to: main222.dropEnteredBlockY
              duration: 200
          }*/
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
            width: root.width; height: root.height
            fillMode: Image.TileHorizontally
            source: "qrc:/iphone_toolbar_icons/black_tree.png"
            visible: true

            Image {
                id: icon
                source:  "image://imageProvider/" + root.colIndex + "+" + root.mIndex + "+ " + (Math.round(Math.random(9999999) * 10000));
                width: background.width;
                height: background.height
                visible:  true


                onSourceChanged: {
                    gc();
                }

                Component.onCompleted: {
                    root.p_icon_coloroverlay = icon_coloroverlay
                }

            }
            ColorOverlay {
                id: icon_coloroverlay
                anchors.fill: icon
                source: icon
                color: "#00000000"
                enabled: false

            }
            Text {
                id: name
                anchors.margins: root.height/5
                //anchors.centerIn: border_image
                anchors.left: border_image.left
                anchors.verticalCenter: border_image.verticalCenter
                // x: icon.width/2 - width/2
                text: root.title
                font.pixelSize : root.height/4
                color: "white"
                style: Text.Outline;
                styleColor: "black"
                onTextChanged: {

                    // name.font.pixelSize = (root.width*1.2)/text.length;
                    /*if(name.font.pixelSize > root.height*0.7)
                   name.font.pixelSize = root.height*0.7*/

                }
            }
            Rectangle {
                id: border_image
                width: background.width; height: background.height
                border.width:  background_rec.border_width  ;
                border.color: "white"
                color: "transparent"

                Component.onCompleted: {
                    //root.p_border_color = border.color
                }
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
            onStarted: {
                /*root.p_main222.p_toolbar .p_button_RemoveTrack.enabled = false
            root.p_main222.p_toolbar .p_button_AddTrack.enabled = false
            root.p_main222.p_toolbar .p_button_play.enabled = false
             for (var i=0; i< root.p_main222.p_rep_columns.count; i++)
                     root.p_main222.p_rep_columns.itemAt( i).enableTrackbarsButtons(false)*/
            }

            onStopped:  {
                console.log("animation_scale_normal   onStopped")
                root.p_bar_track.z -= 200
                root.globalRep.z -= 200
                //
                if(root.p_main222.needUpdateModelWhereBlockDroped)
                {
                    root.p_main222.dropEnteredBlockItemGlobalRep.updateModel();
                    root.p_main222.needUpdateModelWhereBlockDroped = false
                }
                root.globalRep.updateModel();
                /*root.p_main222.p_toolbar.p_button_RemoveTrack.enabled = true
            root.p_main222.p_toolbar.p_button_AddTrack.enabled = true
             root.p_main222.p_toolbar.p_button_play.enabled = true
            for (var i=0; i< root.p_main222.p_rep_columns.count; i++)
                    root.p_main222.p_rep_columns.itemAt( i).enableTrackbarsButtons(true)*/
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
                duration: animation_scale_small.anim_time
            }
            /*NumberAnimation  {
            target: root
            property: "x"
            from: animation_scale_normal_FromXpos_cuz
            to: animation_scale_normal_toXpos;
            duration: animation_scale_small.anim_time
        }*/
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
        type = timeControll.getBlockTypeId(colIndex,mIndex)
        //console.log("onWidthChanged    type = "  +type)
       /* if (root.type == 5)
        {
             console.log("onWidthChanged   type == 5")
            if (width == 0)
            {
                //destroy
            }
        }
        else
        {
             console.log("onWidthChanged  type != 5")
            if (width < main222.minBlockWidth)
                width = main222.minBlockWidth
        }*/

        //console.log("width = " + width)
        icon.width = icon.height;
        timeControll.setBlockTime(colIndex, mIndex,root.width * main222.scaling);
        // timeControll.createEmptyBlock(root.colIndex, root.mIndex)
    }
    onXChanged: {
        // timeControll.setBlockStartTime(root.colIndex,root.mIndex, x * main222.scaling)
        // timeControll.createEmptyBlock(root.colIndex, root.mIndex)
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
        property bool isDrag : drag.active;
        anchors.fill: parent
        enabled: !globalRep.isDrag
        hoverEnabled: true

        onIsDragChanged:  {
            console.log("mouseArea   onIsDragChanged")

            if (isDrag)
            {
                cursorShape = Qt.OpenHandCursor
                animation_scale_small.running = true
                animation_scale_x.running = true
                animation_scale_y.running = true //99999999
                shadow.visible = true
            }
            else
            {
                console.log("onIsDragChanged")
                root.animation_scale_normal_FromXpos_cuz = root.x
                root.animation_scale_normal_FromYpos_cuz = root.y

                root.animation_scale_normal_FromScale = background_rec.scale

                if (main222.dropEnteredBlockIndex !== -1)
                {
                    var zdvig = 0;
                    if (main222.doZdvigWhenNormalAnim)
                        zdvig =  main222.dropEnteredBlock.width //666

                    var num_of_blocks_beetwen = main222.dropEnteredBlock.colIndex - root.colIndex
                    var tempo_y_zdvig = (root.height+ main222.p_columns.spacing ) *num_of_blocks_beetwen
                    root.animation_scale_normal_toYpos = tempo_y_zdvig
                }

                root.animation_scale_normal_toXpos =root.x - scroll.flickableItem.contentX //main222.dropEnteredBlock.x  + main222.zdvigWhenNormalAnim
                if (main222.able_create_empty_block)
                {
                    console.log("main222.exitedFromDropArea = true         createEmptyBlock")
                    timeControll.setBlockStartTime(root.colIndex, root.mIndex, root.x  * main222.scaling)

                    //timeControll.createEmptyBlock(root.colIndex, root.mIndex)
                }
                main222.able_create_empty_block = true


                root.p_bar_track.z += 200 //888
                root.z += 200

                animation_scale_normal.running = true //9999999

                //function moveBlocksForAnim( from, to,  left_right,  value)

                root.p_bar_track.z -= 200 //888
                root.z -= 200
                //root.p_main222.root_isDragChanged = true;
                //console.log("onIsDragChanged end ------------------------------")
            }

            // root.globalRep.updateModel()
        }

        Timer {
            id: double_click_timer
            interval: 250; running: false; repeat: false
            onTriggered: root.double_click = false
        }

        onMouseXChanged: {
            // if (context_menu.visible === false) //123rr
            /*if(timeControll.getCurent_group())
                return;*/
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
                    //console.log(xChange);
                    if(timeControll.getCurent_group())
                        root.width += timeControll.tryResizeMemberInCurentGroup(-xChange*main222.scaling, root.colIndex, root.mIndex)/main222.scaling;
                    else
                        root.width -= xChange;
                    //timeControll.setTestWidth(bar_track.index,root.width, mIndex);

                }
                oldMouseX = mouseX;
            }
        }


        onPressed: {
            //main222.dropedtoDropArea = false
            console.log("onPressed   mIndex = " + root.mIndex)
            main222.dropEntered = 0
            //root.animation_scale_normal_toXpos = root.x
            root.animation_scale_normal_toYpos = root.y
            divider.y = (root.height + main222.p_columns.spacing) * root.colIndex
                    + time_scale.height - scroll.flickableItem.contentY
            divider.x =  root.x + root.width - divider.width/2 + tollbar.width - scroll.flickableItem.contentX  //1234

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
                    if (!main222.ctrl_pressed)
                        context_menu.showEditBlock()
                    root.double_click = false
                }
                else
                {
                    root.double_click = true
                    double_click_timer.running = true

                    context_menu.closeIt()
                    if (!main222.ctrl_pressed && !timeControll.getCurent_group())
                        drag.target = root
                    else
                        drag.target = null
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

            drop.visible = !timeControll.getCurent_group(colIndex, mIndex);
            drop.enabled = drop.visible;

            if (globalRep.isDrag)
            {
                divider.visible = false
                if (main222.dropEntered  && !main222.exitedFromDropArea)
                {
                    //timeControll.reverseBlocks(root.colIndex,root.mIndex,main222.clicked_blockId)
                    /* if (main222.selectedBlockIndex ===  divider.pos_to_append.y - 1 && !main222.left_rigth_entered)
          console.log("main222.selectedBlockIndex ===  divider.pos_to_append.y - 1 && main222.left_rigth_entered)")
*/
                    var track_size =  root.globalRep.count

                    var track_size_drop_in =  main222.dropEnteredBlock.globalRep.count

                    var out_console = true
                    main222.zdvigWhenNormalAnim =  0


                    if ( main222.selectedBlockIndex + 1 === divider.pos_to_append.y)
                    {
                        if (main222.block_zayshow_sprava)
                        {
                            if (main222.left_rigth_entered)
                            {
                                if (main222.selectedBlockCol === main222.dropEnteredTrackIndex)
                                {
                                    if(out_console) console.log("555555555555555555 ok +")
                                    // root.globalRep.moveBlockForAnim(divider.pos_to_append.y,-root.width)
                                    main222.zdvigWhenNormalAnim = main222.dropEnteredBlock.width - root.width
                                    var begini = root.mIndex
                                    if (begini > divider.pos_to_append.y )
                                        begini = divider.pos_to_append.y ;
                                    root.globalRep.moveBlocksForAnim(begini ,
                                                                     timeControll.lastNotEmptyBlockIndexBeginFrom(root.colIndex,root.mIndex) - 1,root.width)
                                }
                                else
                                {
                                    if(out_console) console.log("555555555555555555____  OK +")
                                    divider.pos_to_append.x = main222.dropEnteredBlock.colIndex
                                    divider.pos_to_append.y = main222.dropEnteredBlock.mIndex +1
                                    main222.zdvigWhenNormalAnim = (main222.dropEnteredBlock.width)// + root.width)/2
                                    main222.dropEnteredBlock.globalRep.moveBlocksForAnim(
                                                divider.pos_to_append.y,track_size_drop_in - 1,root.width)
                                }


                            }
                            else
                            {
                                if (  main222.exitedFromDropArea)
                                {
                                    if (main222.selectedBlockCol === main222.dropEnteredTrackIndex)
                                    {
                                        if(out_console) console.log("777777777777777 ok +")
                                        // root.globalRep.moveBlockForAnim(root.mIndex,-root.width)
                                        divider.pos_to_append.y = main222.dropEnteredBlock.mIndex - 1// -=1
                                        main222.zdvigWhenNormalAnim = -root.width
                                        /*main222.dropEnteredBlock.globalRep.moveBlocksForAnim(
                                  divider.pos_to_append.y,track_size_drop_in - 1,root.width)*/
                                    }
                                    else
                                    {
                                        if(out_console) console.log("77777777777777777__ ok +")
                                        divider.pos_to_append.x = main222.dropEnteredBlock.colIndex
                                        divider.pos_to_append.y = main222.dropEnteredBlock.mIndex
                                        main222.zdvigWhenNormalAnim = main222.dropEnteredBlock.width -  root.width
                                        main222.dropEnteredBlock.globalRep.moveBlocksForAnim(
                                                    divider.pos_to_append.y,track_size_drop_in - 1,root.width)
                                    }
                                }
                                else
                                {
                                    if (main222.selectedBlockCol === main222.dropEnteredTrackIndex)
                                    {
                                        if(out_console) console.log("RRRRRRRRRRRRRRRRRRRRRRR ok +")
                                        //root.globalRep.moveBlockForAnim(divider.pos_to_append.y,-root.width)
                                        divider.pos_to_append.y -=1
                                        main222.zdvigWhenNormalAnim = -(main222.dropEnteredBlock.width + root.width)/2
                                    }
                                    else
                                    {
                                        if(out_console) console.log("RRRRRRRRRRRRRRRRRRRRRRR____ ok + ") //++++++++++++++++
                                        divider.pos_to_append.x = main222.dropEnteredBlock.colIndex
                                        divider.pos_to_append.y = main222.dropEnteredBlock.mIndex
                                        // main222.zdvigWhenNormalAnim = main222.dropEnteredBlock.width - root.width
                                        // main222.zdvigWhenNormalAnim = -(main222.dropEnteredBlock.width + root.width)/2
                                        main222.dropEnteredBlock.globalRep.moveBlocksForAnim(
                                                    divider.pos_to_append.y,track_size_drop_in - 1,root.width)
                                    }
                                }
                            }
                        }
                        else //ZAYSHOW ZLIVA
                        {
                            if (main222.left_rigth_entered)
                            {
                                if (main222.selectedBlockCol === main222.dropEnteredTrackIndex)
                                {
                                    if(out_console) console.log("888888888888888 ok ++")
                                    // root.globalRep.moveBlockForAnim(divider.pos_to_append.y,-root.width)
                                    main222.zdvigWhenNormalAnim = main222.dropEnteredBlock.width -  root.width
                                    var drop_block_x = main222.dropEnteredBlock.x
                                    var drop_block_x_width = main222.dropEnteredBlock.x - root.width
                                    main222.dropEnteredBlock.animRunX(drop_block_x_width)
                                    root.animRunX(drop_block_x/*+ main222.dropEnteredBlock.width*/)

                                }
                                else
                                {
                                    if(out_console) console.log("88888888888888888888____  ok +")
                                    divider.pos_to_append.x = main222.dropEnteredBlock.colIndex
                                    divider.pos_to_append.y = main222.dropEnteredBlock.mIndex + 1
                                    main222.zdvigWhenNormalAnim = main222.dropEnteredBlock.width
                                    main222.dropEnteredBlock.globalRep.moveBlocksForAnim(
                                                divider.pos_to_append.y,track_size_drop_in - 1,root.width)
                                }

                            }
                            else
                            {
                                if (main222.selectedBlockCol === main222.dropEnteredTrackIndex)
                                {
                                    if(out_console) console.log("PPPPPPPPPPPPPP ok ++")
                                    divider.pos_to_append.y -= 1

                                    drop_block_x = main222.dropEnteredBlock.x
                                    root.animRunX(main222.dropEnteredBlock.x - root.width )
                                }
                                else
                                {
                                    if(out_console) console.log("PPPPPPPPPPPPPPPPPP____   ok + ")
                                    divider.pos_to_append.x = main222.dropEnteredBlock.colIndex
                                    divider.pos_to_append.y = main222.dropEnteredBlock.mIndex
                                    main222.dropEnteredBlock.globalRep.moveBlocksForAnim(
                                                divider.pos_to_append.y,track_size_drop_in - 1,root.width) //=====================
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
                                    if (main222.selectedBlockCol === main222.dropEnteredTrackIndex)
                                    {
                                        if(out_console) console.log("111111111111111 ok +")
                                        main222.zdvigWhenNormalAnim = main222.dropEnteredBlock.width - root.width
                                        root.globalRep.moveBlocksForAnim(root.mIndex, divider.pos_to_append.y,-root.width)
                                    }
                                    else
                                    {

                                        divider.pos_to_append.x = main222.dropEnteredBlock.colIndex
                                        divider.pos_to_append.y = main222.dropEnteredBlock.mIndex + 1
                                        main222.zdvigWhenNormalAnim = main222.dropEnteredBlock.width // root.width
                                        main222.dropEnteredBlock.globalRep.moveBlocksForAnim(
                                                    divider.pos_to_append.y,track_size_drop_in - 1,root.width)
                                        var ind_from = 0 //root.mIndex
                                        var ind_to = root.mIndex -1 //track_size_drop_in - 2
                                        if(out_console) console.log("1111111111111111111____ ok +") ///0091
                                        // root.globalRep.moveBlocksForAnim(ind_from, ind_to,-root.width)
                                        //root.globalRep.moveTrackForAnim(root.width)
                                    }
                                }
                                else
                                {
                                    if (main222.selectedBlockCol === main222.dropEnteredTrackIndex)
                                    {
                                        if(out_console) console.log("33333333333333333 ok + ")
                                        divider.pos_to_append.y = main222.dropEnteredBlock.mIndex -1
                                        main222.zdvigWhenNormalAnim = -(main222.dropEnteredBlock.width + root.width)/2
                                        root.globalRep.moveBlocksForAnim(root.mIndex, divider.pos_to_append.y,-root.width)
                                    }
                                    else
                                    {
                                        if(out_console) console.log("33333333333333333333____ ok +") //99909
                                        divider.pos_to_append.x = main222.dropEnteredBlock.colIndex
                                        divider.pos_to_append.y =  main222.dropEnteredBlock.mIndex
                                        main222.dropEnteredBlock.globalRep.moveBlocksForAnim(
                                                    divider.pos_to_append.y ,track_size_drop_in - 1,root.width)
                                    }
                                }
                            }
                            else
                            {
                                if (main222.left_rigth_entered)
                                {
                                    if (main222.selectedBlockCol === main222.dropEnteredTrackIndex)
                                    {
                                        if(out_console) console.log("4444444444444444444 ok + ")
                                        main222.zdvigWhenNormalAnim =  main222.dropEnteredBlock.width - root.width
                                        root.globalRep.moveBlocksForAnim(root.mIndex,
                                                                         divider.pos_to_append.y,-root.width)
                                    }
                                    else
                                    {
                                        if(out_console) console.log("4444444444444444444444____  ok + ")
                                        divider.pos_to_append.x = main222.dropEnteredBlock.colIndex
                                        divider.pos_to_append.y = main222.dropEnteredBlock.mIndex + 1
                                        main222.dropEnteredBlock.globalRep.moveBlocksForAnim(
                                                    divider.pos_to_append.y,track_size_drop_in - 1,root.width)
                                        main222.zdvigWhenNormalAnim = main222.dropEnteredBlock.width // root.width
                                    }

                                }
                                else
                                {
                                    if (main222.selectedBlockCol === main222.dropEnteredTrackIndex)
                                    {
                                        if(out_console) console.log("VVVVVVVVVVVVVVVVVV ok ++")
                                        divider.pos_to_append.y -=1
                                        // root.globalRep.moveBlocksForAnim(root.mIndex, divider.pos_to_append.y,-root.width)
                                        main222.zdvigWhenNormalAnim = - root.width //(main222.dropEnteredBlock.width - root.width)/2
                                        root.animRunX(root.x -root.width)

                                        // main222.zdvigWhenNormalAnim = main222.dropEnteredBlock.width - root.width

                                    }
                                    else
                                    {
                                        if(out_console) console.log("VVVVVVVVVVVVVVVVVVVVVVV____ ok + ")
                                        divider.pos_to_append.x = main222.dropEnteredBlock.colIndex
                                        divider.pos_to_append.y = main222.dropEnteredBlock.mIndex
                                        //  main222.zdvigWhenNormalAnim = main222.dropEnteredBlock.width // root.width
                                        main222.dropEnteredBlock.globalRep.moveBlocksForAnim(
                                                    divider.pos_to_append.y,track_size_drop_in - 1,root.width)
                                    }

                                }
                            }
                        }
                        else
                            if (main222.selectedBlockIndex === divider.pos_to_append.y)
                            {
                                //console.log("DDDDDDDDDDDDDAAAAAAAAAAAAAAAAAAAAAAAAAA 1")
                                if (main222.block_zayshow_sprava)
                                {
                                    //console.log("DDDDDDDDDDDDDAAAAAAAAAAAAAAAAAAAAAAAAAA 2")
                                    if (main222.left_rigth_entered)
                                    {
                                        //console.log("DDDDDDDDDDDDDAAAAAAAAAAAAAAAAAAAAAAAAAA 3")
                                        if (main222.selectedBlockCol === main222.dropEnteredTrackIndex)
                                        {
                                            if(out_console) console.log("9999999999999999 hz")
                                            divider.pos_to_append.y = main222.dropEnteredBlock.mIndex + 1
                                            main222.zdvigWhenNormalAnim = main222.dropEnteredBlock.width
                                        }
                                        else
                                        {
                                            if(out_console) console.log("99999999999999999____ ok +")
                                            divider.pos_to_append.x = main222.dropEnteredBlock.colIndex
                                            divider.pos_to_append.y = main222.dropEnteredBlock.mIndex + 1
                                            main222.zdvigWhenNormalAnim = root.width //main222.dropEnteredBlock.width

                                        }

                                    }
                                    else
                                    {
                                        if (main222.selectedBlockCol === main222.dropEnteredTrackIndex)
                                        {
                                            if(out_console) console.log("BBBBBBBBBBBBBBBBBB")
                                        }
                                        else
                                        {
                                            if(out_console) console.log("BBBBBBBBBBBBBBBBBB____ ")
                                            divider.pos_to_append.x = main222.dropEnteredBlock.colIndex
                                            main222.dropEnteredBlock.globalRep.moveBlocksForAnim(
                                                        divider.pos_to_append.y,track_size_drop_in - 1,root.width)
                                        }

                                    }
                                }
                                else //zayshow zliva
                                {
                                    if (main222.left_rigth_entered)
                                    {
                                        if (main222.selectedBlockCol === main222.dropEnteredTrackIndex)
                                        {
                                            if(out_console) console.log("YYYYYYYYYYYYYYYYYYYY")
                                        }
                                        else
                                        {
                                            if(out_console) console.log("YYYYYYYYYYYYYYYYYYYYY____ ok +")
                                            //main222.zdvigWhenNormalAnim = (main222.dropEnteredBlock.width -  root.width)/2
                                            divider.pos_to_append.x = main222.dropEnteredBlock.colIndex
                                            //divider.pos_to_append.y = main222.dropEnteredBlock.mIndex
                                            divider.pos_to_append.y = main222.dropEnteredBlock.mIndex + 1
                                            main222.zdvigWhenNormalAnim = main222.dropEnteredBlock.width //(root.width + main222.dropEnteredBlock.width)/2
                                            main222.dropEnteredBlock.globalRep.moveBlocksForAnim(
                                                        divider.pos_to_append.y,track_size_drop_in - 1,root.width)
                                        }

                                    }
                                    else
                                    {
                                        if (main222.selectedBlockCol === main222.dropEnteredTrackIndex)
                                        {
                                            if(out_console) console.log("!!!!!!!!!!!!!!!!!!!!!!!!")
                                        }
                                        else
                                        {
                                            if(out_console) console.log("!!!!!!!!!!!!!!!!!!!!!!!!____  crash")
                                            /*
                               divider.pos_to_append.x = main222.dropEnteredBlock.colIndex
                              divider.pos_to_append.y = main222.dropEnteredBlock.mIndex

                               main222.dropEnteredBlock.globalRep.moveBlocksForAnim(
                                            divider.pos_to_append.y,track_size_drop_in - 1,root.width)*/

                                            divider.pos_to_append.x = main222.dropEnteredBlock.colIndex
                                            // divider.pos_to_append.y = main222.dropEnteredBlock.mIndex +1 //!!!!!!
                                            main222.dropEnteredBlock.globalRep.moveBlocksForAnim(
                                                        divider.pos_to_append.y,track_size_drop_in - 1,root.width)
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
                                            if (main222.selectedBlockCol === main222.dropEnteredTrackIndex)
                                            {
                                                if(out_console) console.log("DDDDDDDDDDDDDDDDD ok ++") //0-0-0
                                                main222.zdvigWhenNormalAnim = main222.dropEnteredBlock.width //   root.width
                                                divider.pos_to_append.y +=1
                                                //root.animRunX(0)
                                                root.animRunX(main222.dropEnteredBlock.x + main222.dropEnteredBlock.width)
                                            }
                                            else
                                            {
                                                if(out_console) console.log("DDDDDDDDDDDDDDDDDDDD____ ok + ")
                                                divider.pos_to_append.x = main222.dropEnteredBlock.colIndex
                                                divider.pos_to_append.y = main222.dropEnteredBlock.mIndex + 1
                                                main222.zdvigWhenNormalAnim = main222.dropEnteredBlock.width // root.width
                                                main222.dropEnteredBlock.globalRep.moveBlocksForAnim(
                                                            divider.pos_to_append.y,track_size_drop_in - 1,root.width)
                                            }
                                        }
                                        else
                                        {
                                            if (main222.selectedBlockCol === main222.dropEnteredTrackIndex)
                                            {
                                                if(out_console) console.log("FFFFFFFFFFFFFFFF ok ++")
                                                //root.globalRep.moveBlockForAnim(divider.pos_to_append.y,root.width)
                                                root.animRunX(main222.dropEnteredBlock.x /*+ main222.dropEnteredBlock.width*/)
                                                main222.dropEnteredBlock.animRunX(main222.dropEnteredBlock.x + root.width)
                                            }
                                            else
                                            {
                                                if(out_console) console.log("FFFFFFFFFFFFFFFFFF____ ok +")
                                                divider.pos_to_append.x = main222.dropEnteredBlock.colIndex
                                                divider.pos_to_append.y = main222.dropEnteredBlock.mIndex
                                                main222.dropEnteredBlock.globalRep.moveBlocksForAnim(
                                                            divider.pos_to_append.y,track_size_drop_in - 1,root.width)
                                            }

                                        }
                                    }
                                    else
                                    {
                                        if (main222.left_rigth_entered)
                                        {
                                            if (main222.selectedBlockCol === main222.dropEnteredTrackIndex)
                                            {
                                                if(out_console) console.log("GGGGGGGGGGGGGGGGGGG ok +")
                                                main222.zdvigWhenNormalAnim = main222.dropEnteredBlock.width // root.width
                                                divider.pos_to_append.y +=1
                                            }
                                            else
                                            {
                                                if(out_console) console.log("GGGGGGGGGGGGGGGGGG____ ok")
                                                divider.pos_to_append.x = main222.dropEnteredBlock.colIndex
                                                divider.pos_to_append.y = main222.dropEnteredBlock.mIndex + 1
                                                main222.zdvigWhenNormalAnim = main222.dropEnteredBlock.width // root.width
                                                main222.dropEnteredBlock.globalRep.moveBlocksForAnim(
                                                            divider.pos_to_append.y,track_size_drop_in - 1,root.width)
                                            }

                                        }
                                        else
                                        {
                                            if (main222.selectedBlockCol === main222.dropEnteredTrackIndex)
                                            {
                                                if(out_console) console.log("^^^^^^^^^^^^^^^^ ok")
                                                root.globalRep.moveBlockForAnim(divider.pos_to_append.y,root.width)
                                            }
                                            else
                                            {
                                                if(out_console) console.log("^^^^^^^^^^^^^^^^^^^____ ok +")
                                                divider.pos_to_append.x = main222.dropEnteredBlock.colIndex
                                                //divider.pos_to_append.y = main222.dropEnteredBlock.mIndex
                                                main222.dropEnteredBlock.globalRep.moveBlocksForAnim(
                                                            divider.pos_to_append.y,track_size_drop_in - 1,root.width)
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
                                                if (main222.selectedBlockCol === main222.dropEnteredTrackIndex)
                                                {
                                                    if(out_console) console.log("HHHHHHHHHHHHHHHHHH ok ++")
                                                    divider.pos_to_append.y +=1
                                                    main222.zdvigWhenNormalAnim = main222.dropEnteredBlock.width // root.width
                                                    root.animRunX(main222.dropEnteredBlock.x + main222.dropEnteredBlock.width)
                                                    //root.globalRep.moveBlocksForAnim( divider.pos_to_append.y,root.mIndex,root.width)
                                                }
                                                else
                                                {
                                                    if(out_console) console.log("HHHHHHHHHHHHHHHHHHHHHHHH____ ok +")
                                                    divider.pos_to_append.x = main222.dropEnteredBlock.colIndex
                                                    divider.pos_to_append.y = main222.dropEnteredBlock.mIndex + 1
                                                    main222.zdvigWhenNormalAnim =  main222.dropEnteredBlock.width // root.width
                                                    main222.dropEnteredBlock.globalRep.moveBlocksForAnim(
                                                                divider.pos_to_append.y,track_size_drop_in - 1,root.width)
                                                }


                                            }
                                            else
                                            {
                                                if (main222.selectedBlockCol === main222.dropEnteredTrackIndex)
                                                {
                                                    if(out_console) console.log("JJJJJJJJJJJJJJJJJJJJ ok ++ ")
                                                    //root.globalRep.moveBlocksForAnim(divider.pos_to_append.y,root.mIndex,root.width)
                                                    drop_block_x = main222.dropEnteredBlock.x
                                                    /*   root.animRunX(drop_block_x)
                                                    //root.globalRep .itemAt(main222.dropEnteredBlockIndex).animRunX( root.x  ) /// + main222.dropEnteredBlock.width)
                                                    root.globalRep .itemAt(main222.dropEnteredBlockIndex).animRunX( main222.dropEnteredBlock.x  + root.width)*/

                                                    var begini = root.mIndex
                                                    if (begini > divider.pos_to_append.y )
                                                        begini = divider.pos_to_append.y ;
                                                    root.globalRep.moveBlocksForAnim(begini ,
                                                                                     timeControll.lastNotEmptyBlockIndexBeginFrom(root.colIndex,root.mIndex) - 1,root.width)

                                                    /*  root.globalRep.moveBlocksForAnim(root.mIndex,
                                                                                     divider.pos_to_append.y,-root.width)*/
                                                }
                                                else
                                                {
                                                    if(out_console) console.log("JJJJJJJJJJJJJJJJJJJ____  ok crash ")
                                                    /* divider.pos_to_append.x = main222.dropEnteredBlock.colIndex
                               divider.pos_to_append.y = main222.dropEnteredBlock.mIndex
                               main222.dropEnteredBlock.globalRep.moveBlocksForAnim(
                                          divider.pos_to_append.y,track_size_drop_in - 1,root.width)
                               */
                                                    divider.pos_to_append.x = main222.dropEnteredBlock.colIndex
                                                    // divider.pos_to_append.y = main222.dropEnteredBlock.mIndex
                                                    main222.dropEnteredBlock.globalRep.moveBlocksForAnim(
                                                                divider.pos_to_append.y,track_size_drop_in - 1,root.width)
                                                }

                                            }
                                        }
                                        else
                                        {
                                            if (main222.left_rigth_entered)
                                            {
                                                if (main222.selectedBlockCol === main222.dropEnteredTrackIndex)
                                                {
                                                    if(out_console) console.log("NNNNNNNNNNNNNNNNNNNNNNNNNNN ok")
                                                    divider.pos_to_append.y += 1
                                                    main222.zdvigWhenNormalAnim = main222.dropEnteredBlock.width // root.width
                                                    root.globalRep.moveBlocksForAnim( divider.pos_to_append.y,root.mIndex,root.width)
                                                }
                                                else
                                                {
                                                    if(out_console) console.log("NNNNNNNNNNNNNNNNNNNNNNNNNNN____ ok")
                                                    divider.pos_to_append.x = main222.dropEnteredBlock.colIndex
                                                    divider.pos_to_append.y = main222.dropEnteredBlock.mIndex + 1
                                                    main222.zdvigWhenNormalAnim = main222.dropEnteredBlock.width // root.width
                                                    main222.dropEnteredBlock.globalRep.moveBlocksForAnim(
                                                                divider.pos_to_append.y,track_size_drop_in - 1,root.width)
                                                }

                                            }
                                            else  // move from right to left, zayshow zliva, main222.selectedBlockIndex > divider.pos_to_append.y
                                            {
                                                if (main222.selectedBlockCol === main222.dropEnteredTrackIndex)
                                                {
                                                    if(out_console) console.log("********************* ok")
                                                    root.globalRep.moveBlocksForAnim( divider.pos_to_append.y,root.mIndex,root.width)
                                                }
                                                else
                                                {
                                                    if(out_console) console.log("*********************____ ok +")
                                                    divider.pos_to_append.x = main222.dropEnteredBlock.colIndex
                                                    //divider.pos_to_append.y = main222.dropEnteredBlock.mIndex// +1
                                                    main222.dropEnteredBlock.globalRep.moveBlocksForAnim(
                                                                divider.pos_to_append.y,track_size_drop_in - 1,root.width)
                                                }
                                            }

                                        }
                                    }





                    if (main222.selectedBlockCol === main222.dropEnteredBlock.colIndex)
                    {
                        if (!main222.exitedFromDropArea)
                        {
                            console.log("move blcok from to")
                            timeControll.moveBlockFromTo(main222.selectedBlockCol,main222.selectedBlockIndex,  divider.pos_to_append.y );
                            main222.able_create_empty_block = false
                            root.animation_scale_normal_toXpos = root.x - scroll.flickableItem.contentX
                        }
                        // root.animation_scale_normal_toXpos = root.x - scroll.flickableItem.contentX //+ main222.p_scale_pointer.width
                        console.log(" root.animation_scale_normal_toXpos =  " +  root.animation_scale_normal_toXpos)


                        root.p_main222.selectedBlockIndex =  root.p_divider.pos_to_append.y

                    }
                    else
                    {

                        /*  timeControll.moveBlockFromTo(root.colIndex, root.mIndex,
                                     divider.pos_to_append.x,  divider.pos_to_append.y);*/

                        main222.needUpdateModelWhereBlockDroped = true

                        main222.selectedBlockIndex =  divider.pos_to_append.y //333
                        frama.p_main222.selectedBlockCol = main222.dropEnteredTrackIndex
                        //
                        //console.log(" rizni !!!!!!!!!!!!!!!!!!!!!!!!!!")
                    }




                    timeControll.setSelectedBlockPoint(main222.selectedBlockCol,main222.selectedBlockIndex)
                }
                root.globalRep.isDrag = false
            }
            else
                if(bChangeSize)
                {
                    mouseArea.drag.target = root;

                    if(!timeControll.getCurent_group())
                        timeControll.setBlockTime(colIndex, mIndex,root.width * main222.scaling);
                    else
                        root.width = timeControll.getBlockTime(root.colIndex, root.mIndex)/main222.scaling;

                    /*  timeControll.setBlockTime(colIndex, mIndex,root.width * main222.scaling);
                 timeControll.createEmptyBlock(root.colIndex, root.mIndex)*/

                    // item_col.width = timeControll.getMaxTrackTime()// item_col.childrenRect.width

                    bChangeSize = false;
                    if(!timeControll.getCurent_group())
                        if (root.p_main222.dovodka_block)

                        {
                            timeControll.attachBlock(root.colIndex, root.mIndex , 50)
                            console.log("dovodka finish")
                        }
                    root.globalRep.updateModel();
                    ///console.log("2222222222222");
                }


            shadow.visible = false


            cursorShape = Qt.ArrowCursor;


        }
        onEntered: {
            // // //console.log(mouseX + " YY " + mouseY)
        }
    }






    DropArea {
        id: drop
        enabled : !timeControll.getCurent_group(colIndex, mIndex)
        visible: !timeControll.getCurent_group(colIndex, mIndex)
        anchors.fill: parent
        onEntered: {


           // console.log("mamamamammaa   entered, mIndex = " + root.mIndex)
            main222.exitedFromDropArea = false
            main222.dropEnteredBlockIndex = root.mIndex
            main222.dropEnteredTrackIndex = root.colIndex
            main222.dropEnteredBlock = root
            main222.dropEnteredBlockItemGlobalRep = root.globalRep
            main222.left_rigth_entered = false
            main222.dropEntered = 1
            var t_tempo = root.x
            var temp = main222.selectedBlock.x - root.x - root.width/2
            if (temp > 0 )
            {
                main222.block_zayshow_sprava = true
                t_tempo = root.width
            }
            else
            {
                main222.block_zayshow_sprava = false
            }


            divider.x = t_tempo - divider.width/2 + tollbar.width - scroll.flickableItem.contentX

            divider.pos_to_append.x = root.colIndex
            divider.visible = true


        }
        onExited: {
            divider.visible = false
            main222.exitedFromDropArea = true
            if (root.mIndex === 1)
                main222.dropEnteredBlockIndex = main222.selectedBlockIndex
            icon_coloroverlay.color = "#00000000"

        }
        onPositionChanged: {
            {

                var temp = main222.selectedBlock.x - root.x - root.width/2
                var move_y_pos = (root.height + main222.p_columns.spacing) * root.colIndex
                        + time_scale.height - scroll.flickableItem.contentY
                var move_x_pos  = root.x  - divider.width/2 + tollbar.width - scroll.flickableItem.contentX
                if (temp > 0  )
                {

                    // divider.moveTo(move_x_pos  + root.width, move_y_pos )
                    divider.x= move_x_pos  + root.width,
                            main222.left_rigth_entered = true
                    divider.pos_to_append.y = root.mIndex
                    // console.log("onPositionChanged: right " + divider.pos_to_append.y)
                }
                else
                {
                    //    divider.moveTo(move_x_pos, move_y_pos )
                    divider.x= move_x_pos
                    main222.left_rigth_entered = false
                    divider.pos_to_append.y = root.mIndex
                    //console.log("onPositionChanged: left " + divider.pos_to_append.y)

                }
            }
        }

    }
    /* Component.onCompleted: {
        root.p_color_overlay = icon_coloroverlay
    }*/
}



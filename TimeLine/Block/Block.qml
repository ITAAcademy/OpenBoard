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
    radius: 3
    clip: true
    color: "transparent"
    anchors.leftMargin: 15
    border { color: "white" ; width: 2 }





    function hideMenu()
    {
        context_menu.visible = false;
    }
    function showMenu()
    {
        context_menu.visible = true;

    }

    function repaint()
    {
        icon.source = "image://imageProvider/" + root.colIndex + "+" + root.mIndex + "+ " + Math.random(1000000);
    }


     property Item  p_main222


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
onYChanged: y=0;

    MouseArea {
        id: mouseArea
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        drag.target: root
        property int oldMouseX
        anchors.fill: parent
        enabled: !globalRep.isDrag
        hoverEnabled: true

        Timer {
            id: double_click_timer
               interval: 250; running: false; repeat: false
               onTriggered: root.double_click = false
           }

        onMouseXChanged: {
            if (context_menu.visible === false)
            {
            if(globalRep.isDrag === false &&  mouseX > root.width * 0.9) //mouseX < root.width * 0.1 ||/
            {
                cursorShape = Qt.SizeHorCursor;
//            drop.visible = false;
//                drop.enabled = false;
            //    root.Drag.active =  false
              }
            else
            {
                cursorShape = Qt.ArrowCursor;

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
            if(main222.selectedBlock !== null)
                main222.selectedBlock.hideMenu();
            timeControll.emitFocusFoundSignal();
            //console.log("AAAAAAAAAAAAAAA " + timeControll.getBlockStartTime(root.colIndex,root.mIndex))
             main222.p_scale_pointer.x = mouseX + root.x - scroll.flickableItem.contentX + main222.p_scale_pointer.width //1234
            timeControll.setSelectedBlockPoint(root.colIndex,root.mIndex);
            main222.p_scale_pointer.x+=1
            main222.selectedBlock = root;

            main222.needToLightSelected = true
            for (var y=0; y< rep_columns.model; y++)
                 rep_columns.itemAt(y).abortColorize()
            main222.selectedBlockCol = root.colIndex
            main222.selectedBlockIndex = root.mIndex
            icon_coloroverlay.color = "#8000FF00"  //1234
           // blocks.itemAt(i).icon_coloroverlay.color = "#00000000"
            //columns.childAt()
            // //console.log("onPressed: mIndex="+mIndex+" colIndex="+ colIndex + " time = " + timeControll.getBlockTime(colIndex,mIndex))
            if (mouse.button == Qt.RightButton)
            {
               context_menu.show(main222.p_scale_pointer.x, mouseY + root.colIndex * (root.height + 2)
                                 - scroll.flickableItem.contentY,root.globalRep)
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

                context_menu.visible = false
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
                 main222.maIsPressed = 1
                main222.clicked_blockId = root.mIndex
                main222.clicked_blockX = root.x
                main222.clicked_blockY = root.y
                root.z += 200
            }
            }
            // //console.log("   root.z= " +   root.z)
        }
        }
        onReleased: {
           // main222.p_scale_pointer.x = mouseX + root.x
            if (context_menu.visible === false)
            {
            // //console.log("RELEASE");
            if (globalRep.isDrag)
                       root.z -= 200
 globalRep.isDrag = false
            if(bChangeSize)
            {
                mouseArea.drag.target = root;
                 timeControll.setBlockTime(colIndex, mIndex,root.width * main222.scaling);

                // item_col.width = timeControll.getMaxTrackTime()// item_col.childrenRect.width
                // //console.log("118 item_col.width="+  item_col.width )
                // //console.log("119 timeControll.getMaxTrackTime="+  timeControll.getMaxTrackTime() )
                 globalRep.updateModel();

            }
             bChangeSize = false;

            if (root.p_main222.maIsPressed && root.p_main222.dropEntered === 0) {
                root.x = main222.clicked_blockX
                root.y = main222.clicked_blockY
        // if (globalRep.isDrag)
            //   rep_columns.itemAt(main222.selectedBlockCol).setColorize(main222.selectedBlockIndex,"#8000FF00")

            }
         root.p_main222.maIsPressed = 0
             drop.visible = true;
             drop.enabled = true;
//globalRep.updateModel()

// //console.log(" reles  root.z= " +   root.z)
        }
        }
        onEntered: {
           // // //console.log(mouseX + " YY " + mouseY)
        }
    }

    Image {
         parent : root
        id: background
       anchors.fill: parent
       anchors.margins: 3

       fillMode: Image.TileHorizontally
       source: "qrc:/iphone_toolbar_icons/black_tree.png"
       visible: true

    }

    Image {
        id: icon

        //anchors.fill: parent
      //  source: "qrc:/Block/file.png"
        source:  "image://imageProvider/" + root.colIndex + "+" + root.mIndex + "+ " + (Math.round(Math.random(9999999) * 10000));
        height: root.height - root.border.width*2 - 1
        width: height
        x:root.border.width + 1
        y:root.border.width + 1
        visible:  true
       /* onSourceChanged: {
            if (main222.selectedBlockCol === root.colIndex &&
                    main222.selectedBlockIndex === root.mIndex)
          //console.log("  AAAAAAAAAAAAAAAAAA " + root.colIndex + " " + root.mIndex);
        }*/


            // timeControll.getBlockIcon(colIndex,mIndex)
    }






       /* OpacityMask {
            source: background
            maskSource: root
            anchors.fill: root

        }*/

    ColorOverlay {
        id: icon_coloroverlay
           anchors.fill: icon
           source: icon
           color: "#00000000"
       }

    Text {
        id: name
        anchors.margins: 3
        anchors.centerIn: parent
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
    }
    DropArea {
        id: drop
        enabled : true
        visible: true
         anchors.fill: parent
    onEntered: {
        main222.dropEntered = 1
     icon_coloroverlay.color = "#80900000"

    }
    onExited: {
         // //console.log( " DropArea onExited main_root.maIsPressed="+main222.maIsPressed)
        icon_coloroverlay.color = "#00000000"
 main222.dropEntered = 0
        if (main222.maIsPressed === 0)        {
            timeControll.reverseBlocks(root.colIndex,root.mIndex,main222.clicked_blockId)
            main222.selectedBlockCol = root.colIndex
            main222.selectedBlockIndex = root.mIndex
              globalRep.updateModel();
        }
            }
    }
    Component.onCompleted: {
        root.p_color_overlay = icon_coloroverlay
    }
}



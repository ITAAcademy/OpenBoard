import QtQuick 2.4
import QtGraphicalEffects 1.0



Rectangle{
    id: root
    color: "#343434"
    property Repeater globalRep
    property string colorKey : "green"
    property int minWidth : 20
    /*radius: 0
    border.width: 0
    border.color: "green"
    anchors.topMargin: 0
    anchors.leftMargin: 0*/
z: 0
    onWidthChanged: {
        if (width < minWidth)
            width = minWidth
    }

    ContextMenu {
        id: context_menu
        x: 20
        y: 30
        z: 500
        visible: false
        columnIndex : root.colIndex
        blockIndex: root.mIndex
        onXChanged: {
            if (x > root.width - width)
                x = root.width - width;
            else if (x < 0 )
                x = 0;
        }
        globalRep: root.globalRep
        minBlockWidth : root.minWidth
    }

    property int mIndex: 0
    property int colIndex: 0
    property int xChange: 0
    property bool bChangeSize: false
    property string title: "value"
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
            if (mouse.button == Qt.RightButton)
            {
                context_menu.visible = true
                context_menu.x = mouseX
                drag.target = null
            }
        else
            {
                context_menu.visible = false
                drag.target = root
    console.log("onPressed");
            drop.visible = false;
             drop.enabled = false;
            if(/*mouseX < root.width * 0.1 ||*/ mouseX > root.width * 0.9)
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

            console.log("   root.z= " +   root.z)
        }
        }
        onReleased: {
            if (context_menu.visible === false)
            {
            console.log("RELEASE");
            if (globalRep.isDrag)
                       root.z -= 200
             globalRep.isDrag = false
            if(bChangeSize)
            {
                mouseArea.drag.target = root;
                 timeControll.setTestWidth(bar_track.index, mIndex,root.width);
            }
             bChangeSize = false;

            if (main222.maIsPressed && main222.dropEntered === 0) {
                root.x = main222.clicked_blockX
                root.y = main222.clicked_blockY

            }
         main222.maIsPressed = 0
           /* if(bChangeSize)
            {
                timeControll.addNewTest("vasia");
               globalRep.updateModel();
               timeControll.removeLastTest();
              globalRep.updateModel();

            }*/



           drop.visible = true;
             drop.enabled = true;
//globalRep.updateModel()

console.log(" reles  root.z= " +   root.z)
        }
        }
        onEntered: {
            console.log(mouseX + " YY " + mouseY)
        }

    }
    Image {
        id: icon
        anchors.fill: parent
        source: "qrc:/Block/file.png"
    }
    ColorOverlay {
        id: icon_coloroverlay
           anchors.fill: icon
           source: icon
           color: "#00000000"
       }
    Text {
        id: name
        color: "#FFFF00"
        anchors.fill: parent
        text: root.title
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
         console.log( " DropArea onExited main_root.maIsPressed="+main222.maIsPressed)
        icon_coloroverlay.color = "#00000000"
         main222.dropEntered = 0
        if (main222.maIsPressed === 0)        {
            timeControll.reverseTests(bar_track.index,root.mIndex,clicked_blockId)
           /* repka.itemAt(clicked_blockId).x = root.x
            repka.itemAt(clicked_blockId).y = root.y
            root.x = clicked_blockX
            root.y = clicked_blockY*/
            globalRep.updateModel();

              console.log( "reverseTests")
        }

            }
    }
}



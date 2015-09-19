import QtQuick 2.4
import QtGraphicalEffects 1.0
import QtQuick.Controls 1.2
import QtQuick.Window 2.2
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.2

ApplicationWindow  {
    id: contextMenuFrame
    
    property Repeater globalRep
    property int blockIndex: 0
    property int columnIndex: 0
    property var p_window
    property var p_window3
    property point coordinates
    property bool animatedMenuShowed  : false
    property bool contextMenuShowed  : false
    property var lastObj: null
    property var lastObj2: null
    property var lastObj3: null
    function closeIt()
    {
        //console.log("11111111 ")
        if (p_window)
        {
            if (p_window.p_window3)
            {
                //console.log("11111111   animatedMenuShowed")
                p_window.p_window3.closeIt()
                animatedMenuShowed = false
            }
            //closeAnimateMenu()
            //console.log("111111111111111111111111111")
            p_window.destroy();
            if(lastObj != null)
                lastObj.destroy();
            if(lastObj2 != null)
                lastObj2.destroy();
            if(lastObj3 != null)
                lastObj3.destroy();
            
        }
        appen_block_items.visible = false
    }
    
    function closeAnimateMenu()
    {
timeControll.emitHideEffects();
    }
    
    function showIt(a,b, globRepa)
    {
        var component = Qt.createComponent("ContextMenu.qml")
        var window    = component.createObject(contextMenuItem)
        lastObj = window;
        window.animatedMenuShowed = animatedMenuShowed
        window.height = menuHolder.height + 20
        window.flags = Qt.MSWindowsFixedSizeDialogHint | Qt.CustomizeWindowHint | Qt.FramelessWindowHint
        var v_point = timeControll.getViewPosition()
        contextMenuFrame.globalRep = globRepa.globalRep
        window.show()
        var tint = main222.selectedBlockIndex
        window.blockIndex = tint
        window.x = a + v_point.x
        window.y = b + v_point.y
        window.columnIndex = main222.selectedBlockCol
        
        window.globalRep =  globRepa.globalRep
        window.minBlockWidth = context_menu.minBlockWidth
        p_window = window
        contextMenuShowed = true
        window.contextMenuShowed = true
        
        if (window.x < 5)
            window.x = 5;
        else
        {
            var screen_width =Screen.desktopAvailableWidth - window.width - 5
            if (window.x  > screen_width)
                window.x  = screen_width
        }
        if (window.y < 5)
            window.y = 5;
        else
        {
            var screen_height =Screen.desktopAvailableHeight - window.height - 5
            if (window.y  > screen_height)
                window.y  = screen_height
        }
        window.coordinates.x = window.x
        window.coordinates.y = window.y
        /* contextMenuFrame.coordinates.x = window.x
        contextMenuFrame.oordinates.y = window.y*/
        //console.log("ZZZZZZZZZAAAAAAAAAAAAAAAAAAAA " +window.coordinates.x +" "  + window.coordinates.y )
        
    }
    
    function showEditBlock()
    {
        var window2    = Qt.createComponent("EditBlock.qml").createObject(contextMenuItem)
        lastObj2 = window2;
        // window2.flags = Qt.MSWindowsFixedSizeDialogHint | Qt.CustomizeWindowHint | Qt.FramelessWindowHint
        window2.modality = Qt.WindowModal
        
        
        window2.blockIndex = main222.selectedBlockIndex//contextMenuFrame.blockIndex
        window2.columnIndex = main222.selectedBlockCol  // contextMenuFrame.columnIndex
        
        var temp = 400
        window2.maximumHeight = temp
        window2.maximumWidth = temp
        window2.minimumHeight = temp
        window2.minimumWidth = temp
        window2.selectedBlock = main222.selectedBlock
        
        window2.globalRep = contextMenuFrame.globalRep
        window2.minBlockWidth = contextMenuFrame.minBlockWidth
        var mouse_pos = timeControll.getMousePosition()
        window2.x = mouse_pos.x - temp/2
        window2.y = mouse_pos.y - temp/2
        if (window2.x < 30)
            window2.x = 30;
        else
        {
            var screen_width =Screen.desktopAvailableWidth - window2.width - 5
            if (window2.x  > screen_width)
                window2.x  = screen_width
        }
        if (window2.y < 50)
            window2.y = 50;
        else
        {
            var screen_height =Screen.desktopAvailableHeight - window2.height - 5
            if (window2.y  > screen_height)
                window2.y  = screen_height
        }
        
        window2.show()
    }
    
    function showAnimateBlockMenu()
    {
       timeControll.emitOpenEffects();
    }
    
    property int   minBlockWidth : 0
    Rectangle
    {
    id: contextMenuItem



  //  signal menuSelected(int index) // index{1: Select All, 2: Remove Selected}
    width: 150
    height: menuHolder.height + 20
    border { width: 2; color: "black" }
     color: "gray"
     property color text_color: "white"




     Rectangle {

         border {width: 5; color: "black" }
         x: parent.width*0.5
         y: but_append.y
         z: 5
         id: appen_block_items
         visible: false
         width: parent.width/2
         color: "gray"
         ContextButton {
             text_color: contextMenuItem.text_color
             x: parent.border.width*2
             y: parent.border.width*2
             width: parent.width*0.8
             color: parent.color
             id: but_app_left
             button_text: "left"
             height: parent.height/3
             onButtonClicked: {
                context_menu.closeIt()
                timeControll.addBlockAt(columnIndex,blockIndex);
                timeControll.updateBlocksStartTimesFrom(columnIndex,blockIndex - 1);
                appen_block_items.visible = false
                main222.needToLightSelected = false;
                contextMenuFrame.globalRep.updateModel();
                but_append.color = contextMenuItem.color
             }
         }
         ContextButton {
             x: parent.border.width*2
             y: parent.border.width*2 +but_app_left.height
             text_color: contextMenuItem.text_color
             width: parent.width*0.8
             color: parent.color
             id: but_app_right
             button_text: "right"
              height: parent.height/3
             onButtonClicked: {

                 context_menu.closeIt()
                timeControll.addBlockAt(columnIndex,blockIndex+1);
                 timeControll.updateBlocksStartTimesFrom(columnIndex,blockIndex - 1);
                  appen_block_items.visible = false
                 //closeAnimateMenu()
                 main222.needToLightSelected = false;
                 contextMenuFrame.globalRep.updateModel();
                  but_append.color = contextMenuItem.color
             }
         }
          height: but_edit.height*2.5
     }

    Column {
        id: menuHolder
        spacing: 1
        width: parent.width
        height: menuHolder.childrenRect.height
        anchors { verticalCenter: parent.verticalCenter; left: parent.left; leftMargin: 3 }
        ContextButton {
            text_color: contextMenuItem.text_color
            /*
           property color text_entered_color: "green"
           property color text_clicked_color: "red"*/
            color: contextMenuItem.color
            id: but_edit
           // enabled: false
            button_text: "Edit block"
            index: 1
            onButtonClicked: {
                context_menu.closeIt()
                context_menu.showEditBlock()
                 but_append.color = contextMenuItem.color
                appen_block_items.visible = false
                if(lastObj != null)
                    lastObj.destroy();
                if(lastObj2 != null)
                    lastObj2.destroy();
                if(lastObj3 != null)
                    lastObj3.destroy();
               // closeAnimateMenu()


            }
        }


        ContextButton {
            text_color: contextMenuItem.text_color
            color: contextMenuItem.color
            id: but_append
            enabled: !timeControll.getCurent_group() //@BAG@//NICOlas
            button_text: "Append block"
            index: 2

            onButtonClicked: {
                //closeAnimateMenu()
                appen_block_items.visible = !appen_block_items.visible
                if (appen_block_items.visible)
                     color = "darkgrey"
                else
                    color = contextMenuItem.color

            }
            height: but_edit.height*2.5
        }
        
        Column {
            id: menuHolder
            spacing: 1
            width: parent.width
            height: menuHolder.childrenRect.height
            anchors { verticalCenter: parent.verticalCenter; left: parent.left; leftMargin: 3 }
            ContextButton {
                text_color: contextMenuItem.text_color
                /*
           property color text_entered_color: "green"
           property color text_clicked_color: "red"*/
                color: contextMenuItem.color
                id: but_edit
                button_text: "Edit block"
                index: 1
                onButtonClicked: {
                    context_menu.closeIt()
                    context_menu.showEditBlock()
                    but_append.color = contextMenuItem.color
                    appen_block_items.visible = false
                    if(lastObj != null)
                        lastObj.destroy();
                    if(lastObj2 != null)
                        lastObj2.destroy();
                    if(lastObj3 != null)
                        lastObj3.destroy();
                    // closeAnimateMenu()
                    
                    
                }
            }
            
            
            ContextButton {
                text_color: contextMenuItem.text_color
                color: contextMenuItem.color
                id: but_append
                button_text: "Append block"
                index: 2
                
                onButtonClicked: {
                    //closeAnimateMenu()
                    appen_block_items.visible = !appen_block_items.visible
                    if (appen_block_items.visible)
                        color = "darkgrey"
                    else
                        color = contextMenuItem.color
                }
                
            }
            ContextButton {
                text_color: contextMenuItem.text_color
                color: contextMenuItem.color
                id: but_remove
                button_text: "Remove block"
                index: 2
                onButtonClicked: {
                    
                    context_menu.closeIt()
                    but_append.color = contextMenuItem.color
                    appen_block_items.visible = false
                    
                    var col= contextMenuItem.columnIndex;
                    var id = contextMenuItem.blockIndex;
                    timeControll.removeBlock(main222.selectedBlockCol,main222.selectedBlockIndex);
                    main222.needToLightSelected = false;
                    contextMenuFrame.globalRep.updateModel();
                    
                    
                    // //console.log(" contextMenuItem.visible = false;")
                }
            }
            ContextButton {
                text_color: contextMenuItem.text_color
                color: contextMenuItem.color
                id: but_loadFile
                button_text: "Load from file"
                index: 3
                onButtonClicked: {
                    context_menu.closeIt()
                    but_append.color = contextMenuItem.color
                    appen_block_items.visible = false
                    
                    /*var col= contextMenuItem.columnIndex;
                var id = contextMenuItem.blockIndex;*/
                    timeControll.loadFromFile();//removeBlock(col,id)
                    
                    // //console.log("AFTER 9999999999999999999999");
                    //main222.selectedBlock.repaint();
                    //contextMenuFrame. globalRep.updateModel();
                    
                    
                    
                }
            }
            ContextButton {
                text_color: contextMenuItem.text_color
                color: contextMenuItem.color
                id: but_loadlibrary
                button_text: "Load from library"
                index: 4
                onButtonClicked: {
                    context_menu.closeIt()
                    
                    but_append.color = contextMenuItem.color
                    appen_block_items.visible = false
                    timeControll.showF_manager()
                    timeControll.setPosDefaultF_manager()
                    
                }
            }
            ContextButton {
                text_color: contextMenuItem.text_color
                color: contextMenuItem.color
                id: but_animation
                button_text: "Animate block"
                index: 2
                
                onButtonClicked: {
                    
                    // animate_block_items.visible = !animate_block_items.visible

                    if (animatedMenuShowed)
                    {
                        closeAnimateMenu();

                    }
                    else
                    {
                        showAnimateBlockMenu();
                        context_menu.closeIt();
                    }
                    
                    /*  if (appen_block_items.visible)
                     color = "darkgrey"
                else
                    color = contextMenuItem.color*/
                }
                
            }
            ContextButton {
                text_color: contextMenuItem.text_color
                color: contextMenuItem.color
                id: but_convertToText
                button_text: "Convert to text block"
                index: 3
                onButtonClicked: {
                    context_menu.closeIt()
                    appen_block_items.visible = false
                    
                    /*var col= contextMenuItem.columnIndex;
                var id = contextMenuItem.blockIndex;*/
                    timeControll.convertCurentBlockToText();//removeBlock(col,id)
                    
                    // //console.log("AFTER 9999999999999999999999");
                    //main222.selectedBlock.repaint();
                    contextMenuFrame.globalRep.updateModel();
                    
                    
                    
                }
            }
        }
        
        
    }
}

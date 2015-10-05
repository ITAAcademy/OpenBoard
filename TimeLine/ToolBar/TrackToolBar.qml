import QtQuick 2.0



Rectangle {
    id: root_toolbar
    color: "black"
 property int colIndex : -1
    property Item  p_main222
     property Repeater globalRep
    property bool enableButtonsClick: true
    //anchors.left: parent.left
    height: parent.height
    //anchors.bottom: parent.bottom
    //anchors.top : parent.top
    Component.onCompleted: {

    }

    Column{
        parent: cool_main
        width: root_toolbar.width
        //x: widt
        y: ((mapFromItem(item_col, root_toolbar.parent.x, root_toolbar.parent.y).y + (height/4)))
        height: root_toolbar.height
        function restore()
        {
            parent = root_toolbar;
        }

        z: 100
        Buutton{
            id: butAddText
            title_text: ""
            height: parent.width*2/3
            width: height
          icon_source : "qrc:/iphone_toolbar_icons/bittorrent_plus.png"
          //
          ma_enabled :root_toolbar.enableButtonsClick
            onClicked: {
                main222.needToLightSelected = false
               // for (var i=0; i< 30; i++)
                {
                var ss = main222.blocks_num
                    timeControll.setCurentBlock(root_toolbar.colIndex,-1)
                   timeControll.addNewBlock(colIndex)
                    console.log("DDDDDDDDDDDDAAAAAAAAAAAAAAAAAAA             colIndex  = " + colIndex)
                     globalRep.updateModel()
              /*if (timeControll.addNewBlockFromLibrary(bar_track.mIndex,"Block_" + ss))
              {
                main222.blocks_num +=1
                    globalRep.updateModel()
              }*/
             }
            }
        }
        Buutton{
            id: butAdd
            title_text: ""
           height: parent.width*2/3
            width: height
          icon_source : "qrc:/iphone_toolbar_icons/blue_library.png"
          //
          ma_enabled :root_toolbar.enableButtonsClick
            onClicked: {
                main222.needToLightSelected = false
               // for (var i=0; i< 30; i++)
                {
                var ss = main222.blocks_num
                    timeControll.setCurentBlock(root_toolbar.colIndex,-1)
                    timeControll.setLoadF_manager(true)
                    timeControll.showF_manager()
                    timeControll.setPosDefaultF_manager()
              /*if (timeControll.addNewBlockFromLibrary(bar_track.mIndex,"Block_" + ss))
              {
                main222.blocks_num +=1
                    globalRep.updateModel()
              }*/
             }
            }
        }
        Buutton{
            id: butRemove
            title_text: ""
           height: parent.width*2/3
            width: height
            icon_source : "qrc:/iphone_toolbar_icons/delete.png"
            ma_enabled : root_toolbar.enableButtonsClick
            onClicked: {
                main222.needToLightSelected = false;
              //  rep_columns.itemAt( main222.selectedBlockIndex).abortColorize()
               // if ( main222.selectedBlockIndex != -1)
                    if(main222.selectedBlock !== null)
                {
                    main222.selectedBlockIndex = -1
                    main222.selectedBlockCol = -1
                    var color = "#00000000"
                    root_toolbar.p_main222.selectedBlock.p_icon_coloroverlay.color = color
                }
               if (timeControll.removeLastBlock(root_toolbar.colIndex))
                  globalRep.updateModel()

            }
        }
    }
}


import QtQuick 2.0



Rectangle {
    id: root
    color: "black"
    property int num : 0
     property Repeater globalRep
    //anchors.left: parent.left
    height: parent.height
    //anchors.bottom: parent.bottom
    //anchors.top : parent.top
    Column{
        width: parent.width
        height: parent.height
        Buutton{
            id: butAdd
            title_text: ""
            height: parent.width
            width: parent.width
          icon_source : "qrc:/iphone_toolbar_icons/plus.png"
            onClicked: {
                var ss = num
               timeControll.addNewBlock(bar_track.mIndex,"vasia" + ss);
                num +=1
                // item_col.globalRep.updateModel() ;
                globalRep.updateModel()

               /* item_col.p_columns.columns.globalRep.updateModel();
                 item_col.p_columns.rep_columns.globalRep.updateModel();*/
               // main222.p_item_col.p

               /* var timeControlWidth = blocks.childrenRect.width                    //timeControll.getTestWidth()
                console.log("time " + timeControlWidth)
                if (timeControll.getTestWidth() >= scroll.width)
                track.width  = timeControll.getTestWidth();
                console.log("track " +  track.width)
                 globalRep.updateModel() ;
                 console.log(track.width)*/
              //  console.log("CLICK2 bar_track.index = " + bar_track.mIndex)
            }
        }
        Buutton{
            id: butRemove
            title_text: ""
            height: parent.width
            width: parent.width
          icon_source : "qrc:/iphone_toolbar_icons/delete.png"
            onClicked: {
                if ( timeControll.removeLastBlock(trackbar.mIndex))
                {
                    globalRep.updateModel()

                // track.width -=track.height

                /*    var timeControlWidth =blocks.childrenRect.width //  timeControll.getTestWidth() //
                    if (timeControlWidth >= scroll.width)
                    track.width  = timeControlWidth;
                    else  track.width = scroll.width ;
*/
                   /* if (track.width < scroll.width)
                        track.width = scroll.width*/
                  //  item_col.globalRep.updateModel();
                    // item_col.p_columns.columns.globalRep.updateModel();

                }
               // scroll.moveSliderFor(-1 )
                console.log("CLICK2")
            }
        }
    }
}

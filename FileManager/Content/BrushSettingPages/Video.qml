import QtQuick 2.0
import QtGraphicalEffects 1.0
import QtQuick.Controls 1.2
Rectangle {
    id: root
    color: "transparent"
//    anchors.fill: parent
    height: parent.height
    width: parent.width
    property string cLoaderName: "loader"
    property int last_click_index : -1
     property Item p_rep

    ScrollView
    {
        id: scroll
      //  contentItem: pages
        //verticalScrollBarPolicy: Qt.ScrollBarAlwaysOn
        width: parent.width
        height: parent.height
    Column{
        id: view
        //anchors.fill: parent
       // rows: rep.model/4;
       // columns: 4; spacing: 20;

        Repeater{
            id: rep
            Component.onCompleted: {
                p_rep = rep
            }
            model: brushControll.getVideoStackSize()
            function abortBorders()
            {
                for (var i=0;  i< rep.count; i++)
                {
                    rep.itemAt(i).border.color = "#DDDDDD"
                    rep.itemAt(i).border.width = 0
                }
            }
            delegate:
            Rectangle{
                id: brush
                 property string filename : brushControll.getVideoStackAt(index)
                MouseArea{
                    id: img_MA
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked:
                    {
                        rep.abortBorders()
                        border.color = "aqua"
                        border.width = 6
                        if (root.last_click_index == brush.mIndex  && double_click_timer.running)
                        {

                            brushControll.setFilePathName(finishFileName)
                             brushControll.hide()

                           root.last_click_index = -1
                        }
                        else
                        {
                            root.last_click_index = brush.mIndex
                            double_click_timer.running = true
                        }
                        root.update();
                    }
                    onEntered: {

                        if ( brush.border.width == 0)
                        brush.border.width = 4;
                    }
                    onExited: {
                         if ( brush.border.width == 4)
                        brush.border.width = 0;
                    }
                }

                height: 50
                width: root.width - 20
                color: "transparent"
                border.color: "#DDDDDD"
                border.width: 0
                radius: 10
                property int mIndex: index
                    Image{
                    id: img

                    height: parent.height
                    width: height
                    antialiasing: true
                    source: "qrc:/Content/Video.png"


                        Text{
                            text : brushControll.getVideoStackOnlyFilenameAt(index)
                            //width: brush.width -img.height
                            x: img.height
                            y: (img.height - height)/2
                            color: "white";
                            font { pointSize: 9}
                            //height: img.height
                            //anchors.left: img.right
                        }
                    }

                }
            }
    }

    }
}




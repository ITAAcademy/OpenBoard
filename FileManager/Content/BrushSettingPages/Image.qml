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
    Grid{
        id: view
        //anchors.fill: parent
        rows: rep.model/4;
        columns: 4; spacing: 20;

        Repeater{
            id: rep
            Component.onCompleted: {
                p_rep = rep
            }
            model: brushControll.getImageStackSize()
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
                width: 50
                height: 50
                color: "transparent"
                border.color: "#DDDDDD"
                border.width: 0
                //radius: 10
                 property string filename : brushControll.getImageStackAt(index)
                property int mIndex: index
                    Image{
                    id: img

                    anchors.fill: parent
                    anchors.margins: 2
                    antialiasing: true
                    source: "image://" + root.cLoaderName +"/a"+ index

                        MouseArea{
                            anchors.fill: parent
                            hoverEnabled: true
                            onClicked:
                            {
                                rep.abortBorders()
                                border.color = "aqua"
                                border.width = 15
                                finishFileName = filename
                               // brushControll.setCurentBrush(brush.mIndex);
                                root.update();
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
                            }
                            onEntered: {
                                brush.border.width += 12;
                            }
                            onExited: {
                                brush.border.width -= 12;
                            }
                        }
                    }
                }
            }
    }
    }
}


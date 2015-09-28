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
    signal update
    onUpdate: {
        show_brush_image.update();
        //console.log("update brush");
    }
    Component.onCompleted: {
        root.update();
    }

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
            model: brushControll.getBrushCount()
            delegate:
            Rectangle{
                id: brush
                width: 50
                height: 50
                color: "transparent"
                border.color: "#DDDDDD"
                border.width: 0
                radius: 10
                clip: true
                property int mIndex: index
                    Image{
                    id: img

                    anchors.fill: parent
                    antialiasing: true
                    source: "image://" + root.cLoaderName +"/a"+ index

                        MouseArea{
                            anchors.fill: parent
                            hoverEnabled: true
                            onClicked:
                            {
                                brushControll.setCurentBrush(brush.mIndex);
                                root.update();
                            }
                            onEntered: {
                                brush.border.width = 2;
                            }
                            onExited: {
                                brush.border.width = 0;
                            }
                        }
                    }
                }
            }
    }
    }
}


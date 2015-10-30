import QtQuick 2.0
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.2
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
        property int borderSize: 5
        style: ScrollViewStyle{
            scrollBarBackground : Rectangle{
                implicitHeight: scroll.borderSize
                implicitWidth: scroll.borderSize
                x:1
                color: "#333"
            }
            decrementControl :
                Rectangle{
                height: 0
                width: 20
                color: "transparent"
            }
            incrementControl  :
                Rectangle{
                implicitHeight: 0
                implicitWidth: 0
                color: "transparent"
            }
            corner  :
                Rectangle{
                implicitHeight: scroll.borderSize
                implicitWidth: scroll.borderSize
                x:1
                color: "#333"
            }
            handle:
                Rectangle{
                color: "#555"
                y: scroll.borderSize/2
                x: scroll.borderSize/2
                implicitHeight: scroll.borderSize/2
                radius: 10
                implicitWidth: implicitHeight
            }
        }
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


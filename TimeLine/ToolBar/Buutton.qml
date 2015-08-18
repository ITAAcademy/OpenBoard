import QtQuick 2.0
import QtGraphicalEffects 1.0

Rectangle {
    id:root
    width: parent.width
    height: 20
    property string title_text: "value"
    property string icon_source: "qrc:/Block/file.png"
    signal clicked;
    border.color: "#FF0000"
    border.width : 0;
    radius: 10
    antialiasing: true

    Image {
        id: icon
        anchors.fill: parent
        anchors.margins: 5
        width: parent.width - 5
        height: parent.height
        source: root.icon_source
        Text {
            id: title
            anchors.centerIn:  parent
            text: title_text
            y: 10
        }
    }

    MouseArea{
        id: mouse
        z:20
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {
             root.color =  "black";
                        // //console.log("CLICK---");
        }
        onExited: {
            root.color =  "white";
        }
        onPressed:  {
            // //console.log("CLICK");
            context_menu.visible = false
            root.clicked();
        }
    }
}


import QtQuick 2.0

Rectangle {
    id:root
    width: parent.width
    height: 20
    property string title: "value"
    signal clicked;
    border.color: "#FF0000"
    radius: 10
    antialiasing: true
    Image {
        id: icon
        anchors.fill: parent
        anchors.margins: 5
        width: parent.width - 5
        height: parent.height
        source: "qrc:/Block/file.png"

        Text {
            id: title
            anchors.fill: parent
            text: root.title
            y: 10
        }
    }

    MouseArea{
        id: mouse
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {
            root.border.width = 5;
        }
        onExited: {
            root.border.width = 0;
        }
        onClicked: {
            console.log("CLICK");
            root.clicked();
        }
    }
}


import QtQuick 2.0
import QtGraphicalEffects 1.0

Item {
    id: root
    //width: parent.width * 0.8
    //x: parent.width*0.1
    height: 2
    //anchors.fill: parent
    anchors.right: parent.right
    anchors.left: parent.left
    anchors.horizontalCenter: parent.Center
   // anchors.margins: parent.width*0.1
    anchors.topMargin: 5
    anchors.bottomMargin: 5
    property color color: "#333333"
    smooth: true
    antialiasing: true
    RectangularGlow {
        id: effect
        anchors.fill: separator
        glowRadius: 3
        spread: 0.0001
        color: "white"
        cornerRadius: separator.radius + glowRadius
    }
    Rectangle{
        id: separator
        width: root.width
        height: 0
        color: root.color
    }
}


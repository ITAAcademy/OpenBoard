import QtQuick 2.0
import QtGraphicalEffects 1.0

Rectangle {
    id: root
    height: parent.height
    width: (parent.width - parent.x*2)/parent.count
    color: "#555555"
    radius: 10
    antialiasing: true
    smooth: true
    signal clicked
    border.color: "#888888"
    border.width: 0
    gradient: enter2;

    property string title : "value"
    RectangularGlow {
          id: effect
          anchors.fill: root
          glowRadius: 10
          spread: 0.00001
          color:  "white"
          visible: false
          cornerRadius: root.radius
      }
    Gradient{
        id: enter

        GradientStop { position: 0.0; color: "white" }
        GradientStop { position: 0.2; color: root.color }
        GradientStop { position: 0.80; color: root.color }
        GradientStop { position: 1.0; color: "white" }
    }
    Gradient{
        id: enter2

        GradientStop { position: 0.0; color: "white" }
        GradientStop { position: 0.10; color: root.color }
        GradientStop { position: 0.90; color: root.color }
        GradientStop { position: 1.0; color: "white" }
    }

    MouseArea
    {
        anchors.fill: parent
        hoverEnabled: true
        onClicked: {
            root.clicked()
        }
        onEntered:
        {
            root.gradient = enter;
            effect.visible = true;
        }
        onExited:
        {
            root.gradient = enter2;
            effect.visible = false;
        }
    }
    Text {
        id: title
        color: "white"
        font.pixelSize: 14
        //anchors.fill: parent
        anchors.centerIn: parent
        text: root.title
        style: Text.Outline;
        styleColor: "black"
    }
}


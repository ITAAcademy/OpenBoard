import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.3
import QtGraphicalEffects 1.0

Item{
    id: root
    property string name: "value"
    property bool checkable: false
    property bool checked: false
    property color mColor: "#333333"
    property bool small: false

    property real value: 1
    property real maximum: 1
    property real minimum: 0
    property int xMax: size.width - handle.width - 4
    property int  glowRadius: 3
    onValueChanged: { handle.x = 2 + (root.value - root.minimum) * root.xMax / (root.maximum - root.minimum);}
    signal release;
 Row{
     width: parent.width
     height: parent.height
     spacing: 10
     Text{
         id: name
         text: root.name
         width: 60
         color: "white"
         font.pixelSize: 14
         style: Text.Outline;
         styleColor: "black"
     }
/*
     Slider{
         id: size
         width: root.width - 60
         maximumValue: root.max
         property int glowRadius: 10
         MouseArea{
             id : mouse
             anchors.fill: size
             hoverEnabled: true
             onExited: {
                 to.start();
                 mouse.enabled = true;
             }
             onEntered: from.start();
         }
         NumberAnimation { id: to; target: size; property: "glowRadius"; to: 10; duration: 200 }
         NumberAnimation { id: from; target: size; property: "glowRadius"; to: 0; duration: 200 }
         style: SliderStyle {
                 groove: Rectangle {
                     id: rect
                     implicitWidth: 200
                     implicitHeight: 8
                     color: "gray"
                     radius: 8
                          RectangularGlow {
                           id: effect
                           anchors.fill: rect
                           glowRadius: root.glowRadius
                           spread: 0.2
                           color: "white"
                           cornerRadius: rect.radius + glowRadius
                       }
                 }
                 handle: Rectangle {
                     id:rect2
                     anchors.centerIn: parent
                     color: control.pressed ? "white" : "lightgray"
                     border.color: "gray"
                     border.width: 2
                     implicitWidth: 34
                     implicitHeight: 34
                     radius: 100


                     RectangularGlow {
                           id: effect2
                           anchors.fill: rect2
                           glowRadius: 10
                           spread: 0.2
                           color: "white"
                           cornerRadius: rect2.radius + glowRadius
                       }
                 }
             }
     }
     */
     Item {
         id: size; width: root.width - name.width*2; height: root.height
         NumberAnimation { id: to; target: root; property: "glowRadius"; to: 8; duration: 200 }
         NumberAnimation { id: from; target: root; property: "glowRadius"; to: 3; duration: 200 }

         Rectangle {
          id: rect
          anchors.centerIn: size
          anchors.top: size.Top
          anchors.bottom: size.Bottom
          width: parent.width
          height: parent.height/4
          color: "gray"
          radius: 8
          RectangularGlow {
            id: effect
            anchors.fill: rect
            glowRadius: root.glowRadius
            spread: 0.2
            color: mColor
            cornerRadius: rect.radius + glowRadius
            }
         }
         Rectangle {
             id: handle; smooth: true
             z: 1
             x: 2 + (root.value - root.minimum) * root.xMax / (root.maximum - root.minimum); width: size.height; height: size.height; radius: 100
             gradient: Gradient {
                 GradientStop { position: 0.0; color: "lightgray" }
                 GradientStop { position: 1.0; color: "gray" }
             }
             RectangularGlow {
                   id: effect2
                   anchors.fill: handle
                   glowRadius: root.glowRadius
                   spread: 0.2
                   color: if (!checkable) "white"; else "#CC0000"
                   cornerRadius: handle.radius + root.glowRadius
               }
             MouseArea {
                 id: mouse_drag
                 anchors.fill: parent; drag.target: parent
                 hoverEnabled: true
                 drag.axis: Drag.XAxis; drag.minimumX: 2; drag.maximumX: root.xMax+2
                 onPositionChanged: { root.value = (root.maximum - root.minimum) * (handle.x-2) / root.xMax + root.minimum; }
                 property bool enter: false
                 onExited: {
                     if(pressed == false)
                        from.start();
                 }
                 onEntered:{
                     to.start();
                 }
                 onReleased: {
                     from.start();
                     root.release();
                     //console.log("LOGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG");
                 }
                 onDoubleClicked: {
                     if(checkable)
                     {
                        root.checked = !root.checked
                        if(root.checked)
                            effect2.color = "green";
                         else
                            effect2.color = "#CC0000";
                     }
                 }
             }
         }
     }
     Text {
         id: size_value
         text: if(small) root.value.toFixed(2);else Math.round(root.value)
         width: 30
         color: "white"
         font.pixelSize: 14
         style: Text.Outline;
         styleColor: "black"
     }
    }
 Component.onCompleted: {
    root.xMax = size.width - handle.width - 4;
    handle.x = 2 + (root.value - root.minimum) * root.xMax / (root.maximum - root.minimum);
 }
}


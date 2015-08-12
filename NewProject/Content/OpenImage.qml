import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import QtQuick.Dialogs 1.2
import QtGraphicalEffects 1.0

Rectangle{
    id: root
    width: parent.width
    height: 80
    property string title: "value"
    border.width: 0
    function getFilePath()
    {
        return openfile.text;
    }
    signal pathChange;

    gradient: Gradient {
        GradientStop {
            position: 0.00;
            color: "transparent";
        }
        GradientStop {
            position: 0.02;
            color: "#ffffff";
        }
        GradientStop {
            position: 0.05;
            color: "transparent";
        }
        GradientStop {
            position: 0.95;
            color: "transparent";
        }
        GradientStop {
            position: 0.98;
            color: "#ffffff";
        }
        GradientStop {
            position: 1.0;
            color: "transparent";
        }
    }
    Row{
        spacing: 25
        anchors.fill: parent
        Rectangle
        {
            id: image_rect
            y: parent.height/2 - height/2
            width: parent.height
            height: width
            RectangularGlow {
                id: effect
                visible: true
                anchors.fill: image_rect
                glowRadius: 10
              //  scale: root.scale
                spread: 0.000001
                z: -100
                color: "white"
                cornerRadius: image_rect.radius + glowRadius

                //privat

            }
            Image {
                id: firstImage
                anchors.fill: parent
                anchors.margins: 0
                source: openfile.text
            }
        }
        TextField {
            id: openfile
            y: parent.height/2 - height/2
            width: parent.width - firstImage.width - parent.spacing*3 - load.width - root.parent.maxTextWidth
            height: parent.height/2
            font.pixelSize: height*0.45
            style: TextFieldStyle {
                textColor: "white"
                background: Rectangle {
                    radius: 2
                    implicitWidth: control.width
                    implicitHeight: control.height
                    border.color: "white"
                    border.width: 1
                    color: "#333333"
                }
            }
            onTextChanged:
            {

            }
        }
        Image {
            id: load
            source: "qrc:/Content/Button_3.png"
            width: parent.height/2
            height: width
            y: parent.height/2 - height/2
            transform: Rotation {id: rotation_load; origin.x: load.width/2; origin.y: load.height/2; angle: 180}
            property string getLoadFileName: "  "
            MouseArea{
                anchors.fill: parent
                hoverEnabled: true
                onEntered: {
                    load.scale = 1.5;
                }
                onExited: {
                    load.scale = 1.0;
                }
                onClicked: {
                    load.getLoadFileName = projectControll.fileDialog(0);
                    openfile.text = "file:///" + load.getLoadFileName;
                    root.pathChange();
                }
            }
        }
        Text {
            id: name
            color: "white"
            height: paintedHeight
            y: parent.height/2 - height/2
            text: root.title
            font.pixelSize: parent.height*0.45
            Component.onCompleted: {
                if(name.paintedWidth > root.parent.maxTextWidth)
                    root.parent.maxTextWidth = name.paintedWidth;
            }

/*
            MouseArea{
                anchors.fill: parent
                hoverEnabled: true
                onEntered: {
                    name.scale = 1.2;
                }
                onExited: {
                    name.scale = 1.0;
                }
                onClicked: {
                    fileDialog.open();
                }
            }
            */
        }
   }
}

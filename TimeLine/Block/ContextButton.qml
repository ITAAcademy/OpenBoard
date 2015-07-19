import QtQuick 2.4
import QtGraphicalEffects 1.0


Rectangle {
    id: contextButtonItem
    property string button_text;
    property bool clicked;
    property int index;
    property string target;
    property bool enable: true;
    signal buttonClicked;
    height: 25
    width: parent.width - 5
    color: "white"
     property color text_color: "white"
    property color text_entered_color: "green"
    property color text_clicked_color: "red"

    function viewButtonHovered() {

    }



    function viewButtonExited() {


    }
    Rectangle {
        id: viewButton;
        height: vButton.height + 4
        width: parent.width
        color: contextButtonItem.color

        Text {
            id: vButton
            text: qsTr(button_text)
            color: contextButtonItem.text_color
            width: parent.width
            anchors { verticalCenter: parent.verticalCenter; left: parent.left; leftMargin: 10 }
            font { pixelSize: 14 }
        }
        MouseArea {
            hoverEnabled: enable
            anchors.fill: parent
            enabled: enable
            onClicked:  {
                viewButton.state = "clicked";
                buttonClicked();
            }
            onEntered: {
                 viewButton.state = "hovered";
                viewButtonHovered();
            }
            onExited: {
                 viewButton.state = "normal";
                viewButtonExited();
            }
        }
        states: [
            State {
                name: "clicked";
                PropertyChanges { target: vButton; color: contextButtonItem.text_clicked_color }
            },
            State {
                name: "hovered";
                PropertyChanges { target: vButton; color: contextButtonItem.text_entered_color }
            },
            State {
                name: "normal";
                PropertyChanges { target: vButton; color: contextButtonItem.text_color }
            }
        ]
    }
}

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
    property color button_highlited :  "darkgrey"
    property color button_normal :  "grey"
    property color button_disabled :  "lightgray"

    function viewButtonHovered() {

    }



    function viewButtonExited() {


    }

    onEnabledChanged: {
        if (enabled)
            viewButton.state = "normal";
        else
            viewButton.state = "disabled";
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
            hoverEnabled: true
            anchors.fill: parent
            enabled: true
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
                name: "hovered";
                PropertyChanges { target: contextButtonItem; color: button_highlited } //contextButtonItem.text_entered_color }
            },
            State {
                name: "normal";
                PropertyChanges { target: contextButtonItem; color: button_normal }
            },
            State{
                name: "disabled"
                PropertyChanges { target: vButton; color: button_disabled }
            }

        ]
    }
}

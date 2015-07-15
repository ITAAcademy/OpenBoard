import QtQuick 2.4

Rectangle{
    id: root
    color: "#343434"
    radius: 0
    border.width: 2
    border.color: "#000000"
    anchors.topMargin: 0
    anchors.leftMargin: 0
    property int mIndex: 0
    property int xChange: 0
    property bool bChangeSize: false
    property string title: "value"
    MouseArea {
        id: mouseAreaLeft

        property int oldMouseX

        anchors.fill: parent
        hoverEnabled: true
        onMouseXChanged: {
            if(mouseX < root.width * 0.1 || mouseX > root.width * 0.9)
            {
                cursorShape = Qt.SizeHorCursor;
            }
            else
                cursorShape = Qt.ArrowCursor;

            xChange = oldMouseX - mouseX;

            if(bChangeSize)
            {
                root.width -= xChange;
                timeControll.setTestWight(root.width, mIndex);
            }
            oldMouseX = mouseX;

        }
        onPressed: {
            if(mouseX < root.width * 0.1 || mouseX > root.width * 0.9)
            {
                bChangeSize = true;
            }
        }
        onReleased: {
            bChangeSize = false;
        }
    }
    Image {
        id: icon
        anchors.fill: parent
        source: "qrc:/Block/file.png"
    }
    Text {
        id: name
        color: "#FFFF00"
        anchors.fill: parent
        text: root.title
    }

}


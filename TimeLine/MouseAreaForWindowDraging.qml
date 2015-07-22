import QtQuick 2.0

MouseArea
{
    z: -149
    anchors.fill: parent
    property bool isMoved :false
     height : 5
     width: 5
    onPressed: {
     isMoved =true
        timeControll.setPrevMousePosition(mouseX, mouseY)
    }

    function moving()  {
       // if (isMoved )
        {
          timeControll.moveWindow(mouseX, mouseY)

       }
    }

    onMouseXChanged: moving()
    onMouseYChanged: moving()
    onReleased: isMoved =false
    }

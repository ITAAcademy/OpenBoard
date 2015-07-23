import QtQuick 2.0

MouseArea
{
    z: -149
    anchors.fill: parent
    property bool isMoved :false
    property bool isChangingSize :false
     height : 5
     width: 5
    hoverEnabled: true
    onPressed: {
     isMoved =true

        timeControll.setPrevMousePosition(mouseX, mouseY)
    }
   /* onMouseXChanged: {
        if(globalRep.isDrag === false &&  mouseX > root.width * 0.9) //mouseX < root.width * 0.1 ||/
        {
            cursorShape = Qt.SizeHorCursor;
          }
        else
        {
            cursorShape = Qt.ArrowCursor;
*/
    function moving()  {
        {
            if ( isMoved )
          timeControll.moveWindow(mouseX, mouseY)
       }
    }
    onPositionChanged : {
        moving()
        if (Math.abs(mouseX-5) <=5 || Math.abs(mouseX-parent.width) <=5 )
            if(Math.abs(mouseY-5) <=5 || Math.abs(mouseY-parent.height) <=5 )
            {
                isChangingSize = true
                cursorShape = Qt.SizeHorCursor
            }

    }

/*
    onMouseXChanged: moving()
    onMouseYChanged: moving()
*/
    onReleased: isMoved =false
    }

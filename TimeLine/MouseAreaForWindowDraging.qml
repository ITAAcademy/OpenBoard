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
    acceptedButtons: Qt.LeftButton | Qt.RightButton
    onPressed: {
        if (Qt.LeftButton)
        {
            main222.p_context_menu.visible = false
             //console.log("mouseX ="+mouseX+" mouseY ="+mouseY)
     isMoved =true
            timeControll.setPrevMousePosition(mouseX, mouseY)

       // timeControll.setPrevMousePosition(mouseX, mouseY)
        }
        else
        {
            //show context menu
           // main222.p_context_menu.visible = true

            main222.p_context_menu.x = mouseX
             main222.p_context_menu.y = mouseY

        }
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

    onPositionChanged : {
         if ( isMoved )
         {
       timeControll.moveWindow()
         // console.log("mouseX ="+mouseX+" mouseY ="+mouseY)
         }

       /* if (Math.abs(mouseX-5) <=5 || Math.abs(mouseX-parent.width) <=5 )
            if(Math.abs(mouseY-5) <=5 || Math.abs(mouseY-parent.height) <=5 )
            {
                isChangingSize = true
                cursorShape = Qt.SizeHorCursor
            }*/

    }

/*
    onMouseXChanged: moving()
    onMouseYChanged: moving()
*/
    onReleased: {
        isMoved =false
    }
}

import QtQuick 2.0

MouseArea
{
    id: mainMA
    z: -149
    anchors.fill: parent
    property bool isMoved :false
    property bool isChangingWidthLeft :false
    property bool isChangingWidthRight :false
    property bool isChangingHeightUp :false
    property bool isChangingHeightDown :false
     height : 5
     width: 5
    hoverEnabled: true
    acceptedButtons: Qt.LeftButton | Qt.RightButton
    onPressed: {
        if (Qt.LeftButton)
        {
            prompterControll.setFramaMousePosition(mouseX, mouseY)
            prompterControll.setPrevMousePosition()
            var div=5
            if (mouseX <=div )
            {
                isChangingWidthLeft = true
                mainMA.z = 5000
            }
            else
                if (mouseX >= parent.width - div)
            {
                isChangingWidthRight = true
                     mainMA.z = 5000
            }


           else
                if (mouseY <=div )
                {
                    isChangingHeightUp  = true
                     mainMA.z = 5000
                }
                else
                     if ( mouseY >= parent.height - div )
                     {
                         isChangingHeightDown  = true
                          mainMA.z = 5000
                     }
                else    isMoved =true
        }
        else
        {

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
        }
    }*/

    onPositionChanged : {
        if ( isMoved )
        {
            prompterControll.moveWindow()
            // // //console.log("mouseX ="+mouseX+" mouseY ="+mouseY)
        }
        else
            if (isChangingWidthLeft )
            {
                prompterControll.resizeWindowWidth(true)
            }
            else
                if (isChangingWidthRight )
                {
                    prompterControll.resizeWindowWidth(false)
                }
                else
                    if (isChangingHeightUp)
                    {
                        prompterControll.resizeWindowHeight(true)
                    }
                    else
                        if (isChangingHeightDown)
                        {
                            prompterControll.resizeWindowHeight(false)
                        }
                        else
                        {
                            var div=5
                            if (mouseX <=div || mouseX >= parent.width - div )
                            {
                                cursorShape = Qt.SizeHorCursor
                            }
                            else
                                if (mouseY <=div || mouseY >= parent.height - div )
                                {
                                    cursorShape = Qt.SizeVerCursor
                                }
                                else
                                {
                                    isChangingHeightUp = isChangingHeightDown  = isChangingWidthLeft  = isChangingWidthRight = false
                                    cursorShape = Qt.ArrowCursor
                                }
                        }


    }
    onReleased: {
        isMoved =false
         isChangingHeightUp = isChangingHeightDown  = isChangingWidthLeft  = isChangingWidthRight = false
         mainMA.z = -149
    }
}

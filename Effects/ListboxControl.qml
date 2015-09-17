import QtQuick 2.4

Rectangle {
    width: 100
    height: 32
    color: root.color
    id: listboxControl
    property Listbox target: null

    Row
    {
        Rectangle{
            color: root.color
            height:32
            width:32
            id:imgRect1
            Image{
                anchors.fill: parent
                id: imgAddEffect
                source: "qrc:/Content/plus_button_32.png"
                MouseArea
                {
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked:
                    {
                        effectsControll.addEffect("roma",1,1);
                        //brushControll.setCurentBrush(brush.mIndex);
                        root.update();
                    }
                    onEntered: {
                        imgRect1.border.width=2;
                    }
                    onExited: {
                        imgRect1.border.width=0;
                    }
                }
            }

        }
        Rectangle{
            color: root.color
            height:32
            width:32
            id:imgRect2
            Image{
                id: imgRemoveEffect
                source: "qrc:/Content/cancel_32.png"
                MouseArea
                {
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked:
                    {
                        //brushControll.setCurentBrush(brush.mIndex);
                        effectsControll.removeEffect(target.getSelectedIndex())
                        target.decSelectedIndex();
                        root.update();
                    }
                    onEntered: {
                        imgRect2.border.width=2;
                    }
                    onExited: {
                        imgRect2.border.width=0;
                    }
                }
            }
        }
    }



}


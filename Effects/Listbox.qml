import QtQuick 2.4


Rectangle
{

    property alias listBox : listBox
    property alias model : listBox.model
    property alias delegate : listBox.delegate
    function getListBox(){
        return listBox;
    }

    function getSelectedIndex(){
        return listBox.currentIndex;
    }
    function updateEffectBody(){

    }

    function decSelectedIndex(){
        if (listBox.currentIndex==-1)return;
        listBox.currentIndex=listBox.currentIndex-1;
        console.log("listBox:"+listBox.currentIndex);
    }

    border.width : 0
    border.color : Theme.secondaryHighlightColor//"green"//"#FFFF00"
    //color : Theme.secondaryHighlightColor
    color:root.color
    radius : 4

    ListView
    {
        highlightFollowsCurrentItem: true
        focus: true
        id: listBox
        property int current : 0
        function setAtBegin()
        {
            positionViewAtIndex(0, ListView.Beginning)
            return true
        }

        function setInMid(nr)
        {
            positionViewAtIndex (nr , ListView.Center)
            current = nr
            return true
        }
        onCurrentIndexChanged:
        {
            //listBox.currentIndex=index
            effectsControll.setCurrentEffectIndex(currentIndex);
            console.log("test:"+listBox.currentIndex);
        }
        property int listViewNr : 0
        anchors.margins : 4
        anchors.top : parent.top//oKbutton.bottom
        anchors.left : parent.left
        anchors.right : parent.right
        anchors.bottom : parent.bottom
        clip: true
        model: myModel

        delegate: Rectangle {
            property bool isCurrent : (myModel.index === 1);
            height: 25
            border.width: 0.7
            width: 100
            color: ListView.isCurrentItem?"darkgrey":"grey"
            border.color: Qt.lighter(color, 1.1)
            Text {
                text: modelData
                color: "white"
                font.pixelSize: 14
                style: Text.Outline;
                styleColor: "black"
                horizontalAlignment : Text.AlignHCenter

            }
            MouseArea{

                //  hoverEnabled: false
                anchors.fill: parent
                onClicked:
                {
                    listBox.currentIndex=index
                    effectsControll.setCurrentEffectIndex(index);
                    console.log("test:"+listBox.currentIndex);
                }

            }

        }


    }
    Rectangle{
        height: parent.height
        width: 2
        color: "#333"
        anchors.right: parent.right

    }
}

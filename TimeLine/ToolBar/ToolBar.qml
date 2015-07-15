import QtQuick 2.0

Rectangle {
    id: root
    property Repeater globalRep
    Column{
        width: parent.width
        height: parent.height
        Button{
            id: newElement
            title: "Add"
            height: 50
            width: parent.width
            onClicked: {
                timeControll.addNewTest("vasia");
                if(globalRep != 0)
                    globalRep.model = timeControll.getTestSize();
                console.log("CLICK2")
            }
        }
    }
}


import QtQuick 2.0

Rectangle {
    id: root
    color: "gray"
    property Repeater globalRep
    Column{
        width: parent.width
        height: parent.height
     /*   Buutton{
            id: butAdd
            title_text: ""
            height: parent.width
            width: parent.width
          icon_source : "qrc:/iphone_toolbar_icons/plus.png"

            onClicked: {
               timeControll.addNewTest("vasia");
                 repka.updateModel() ;
                console.log("CLICK2")
            }
        }*/
        Buutton{
            id: butRemoveTrack
            title_text: ""
            height: parent.width
            width: parent.width
          icon_source : "qrc:/iphone_toolbar_icons/delete.png"
            onClicked: {
                main222.removeTrack();
            }
        }

        Buutton{
            id: butAddTrack
            title_text: ""
            height: parent.width
            width: parent.width
          icon_source : "qrc:/iphone_toolbar_icons/eject.png"
          rotation: 180
            onClicked: {
                    main222.addTrack() ;
            }
        }

    }
}


import QtQuick 2.0

Rectangle {
    id: root
    color: "gray"
   // onHeightChanged: // console.log("HEIGHT  toolbar = " + height)
    property Repeater globalRep
    property Buutton p_button_RemoveTrack
    property Buutton p_button_AddTrack

    property Buutton p_button_play
    property Buutton p_button_pause
    property Buutton p_button_stop
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
                // console.log("CLICK2")
            }
        }*/
        Buutton{
            id: butRemoveTrack
            title_text: ""
            height: parent.width
            width: parent.width
          icon_source : "qrc:/iphone_toolbar_icons/delete.png"
          Component.onCompleted: {
              root.p_button_RemoveTrack = butRemoveTrack
          }
            onClicked: {
                main222.needToLightSelected = false
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
          Component.onCompleted: {
              root.p_button_AddTrack = butAddTrack
          }
            onClicked: {

                //for (var i = 0; i< 15; i++)
                {
                    main222.needToLightSelected = false;
                    main222.addTrack() ;
                 //  console.log("AAAAAAAAAAAAding track : "  + timeControll.getTracksNumber())
                }
            }
        }
        Buutton{
            id: butPlay
            title_text: ""
            height: parent.width
            width: parent.width
          icon_source : "qrc:/iphone_toolbar_icons/playG.png"
            onClicked: {
                    timeControll.emitPlaySignal()
            }
            Component.onCompleted: {
                root.p_button_play = butPlay
            }
        }
        Buutton{
            id: butPause
            title_text: ""
            height: parent.width
            width: parent.width
          icon_source : "qrc:/iphone_toolbar_icons/pauseG.png"
            onClicked: {
                    timeControll.emitPauseSignal()
            }
            Component.onCompleted: {
                root.p_button_pause = butPause
            }
        }
        Buutton{
            id: butStop
            title_text: ""
            height: parent.width
            width: parent.width
          icon_source : "qrc:/iphone_toolbar_icons/stopG.png"
            onClicked: {
                    timeControll.emitStopSignal()
            }
            Component.onCompleted: {
                root.p_button_stop = butStop
            }
        }

    }
}


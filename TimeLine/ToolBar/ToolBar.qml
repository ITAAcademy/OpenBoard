import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.2

Rectangle {
    id: root
    color: "#222"
   // onHeightChanged: // //console.log("HEIGHT  toolbar = " + height)
    property Repeater globalRep
    property Buutton p_button_RemoveTrack
    property Buutton p_button_AddTrack

    property Buutton p_button_play
    property Buutton p_button_pause
    property Buutton p_button_stop
    property CheckBox p_chb_dovodka
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
                // //console.log("CLICK2")
            }
        }*/
        CheckBox {
            id: chb_dovodka
            enabled: true
            height: parent.width
            width: parent.width
            checked: false
            property string p_chb_image_source
            onCheckedChanged: {
                main222.dovodka_block = chb_dovodka.checked
              /*  if (chb_dovodka.cheked)
                    chb_dovodka.p_chb_image_source = "qrc:/iphone_toolbar_icons/ttHousehold-Tape-Measure-2-icon (2).png"
                else
                    chb_dovodka.p_chb_image_source = "qrc:/iphone_toolbar_icons/ttHousehold-Tape-Measure-2-icon (1).png"
          */  }

            style: CheckBoxStyle {
                      indicator: Rectangle {
                              implicitWidth: chb_dovodka.width
                              implicitHeight: chb_dovodka.height
                              radius: 3
                              border.color: chb_dovodka.activeFocus ? "yellow" : "black"
                              border.width: 1
                              Image {
                                  id: chb_image_off
                                  visible: !control.checked
                                  source: "qrc:/iphone_toolbar_icons/ttHousehold-Tape-Measure-2-icon (1).png"
                                  anchors.margins: 4
                                  anchors.fill: parent
                              }
                              Image {
                                  id: chb_image
                                  visible: control.checked
                                  source: "qrc:/iphone_toolbar_icons/ttHousehold-Tape-Measure-2-icon (2).png"
                                  anchors.margins: 4
                                  anchors.fill: parent
                              }
                      }
                  }

            Component.onCompleted: {
                root.p_chb_dovodka = chb_dovodka
            }
        }
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
                 //  //console.log("AAAAAAAAAAAAding track : "  + timeControll.getTracksNumber())
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
            enabled: false
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
            enabled: false
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

       /* Buutton{
            id: butRecDrsaw
            enabled: true
            title_text: ""
            height: parent.width
            width: parent.width
          icon_source : "qrc:/iphone_toolbar_icons/stopG.png"
            onClicked: {
                     //raw_wnd.visible= !draw_wnd.visible
                //var rec = timeControll.getYellowRect()
                  main222.drawYellowRectangle(50,50,400,250)
            }
            Component.onCompleted: {
                root.p_button_stop = butStop
            }
        }*/

    }
}


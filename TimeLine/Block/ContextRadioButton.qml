import QtQuick 2.4
import QtGraphicalEffects 1.0
import QtQuick.Controls 1.2
import QtQuick.Window 2.2
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.2

   RadioButton {
    //property string text_val : "text"
             id: root_rb;
            style: RadioButtonStyle {
                id: rb_style
                  indicator: Rectangle {
                           implicitWidth: 16
                           implicitHeight: 16
                           radius: 9
                           border.color: "gray"
                           border.width: 1
                           Rectangle {
                               anchors.fill: parent
                               visible: control.checked
                               color: "#555"
                               radius: 9
                               anchors.margins: 4
                           }
                   }
                  label: Item {
                      x: 10
                       implicitWidth: text.implicitWidth + 2
                       implicitHeight: text.implicitHeight
                      Rectangle {
                           anchors.fill: text
                           anchors.margins: -1
                           anchors.leftMargin: -3
                           anchors.rightMargin: -3
                           visible: root_rb.activeFocus
                           height: 6
                           radius: 3
                           color: "#224f9fef"
                           border.color: "#47b"
                           opacity: 0.6
                       }
                       Text {
                           id: text
                           width: root_rb.width
                          text: root_rb.text
                           font.pixelSize : 14
                           anchors.centerIn: parent
                           color: "white"
                           renderType: Text.NativeRendering
                       }
                   }
               }

        }

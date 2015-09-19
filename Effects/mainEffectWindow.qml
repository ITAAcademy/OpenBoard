import QtQuick 2.4
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0

import "Content" as Content
import "Content/BrushSettingPages" as SettingPages

Rectangle{

    property real blockTime
     function setBlockTime(val){
         blockTime=val;
         console.log("setBlockTime:"+blockTime);
     }
     Connections {
            target: effectsControll

           onSetBlockTimeSignal: setBlockTime(val);

     }

    id: root
    width: 300
    height: 400
    //anchors.margins: 25
    border.width: 10
    border.color: "#333333"
    color: "#777777"
    radius: 10
    smooth: true
     property bool isEffectAlpha : (combo.currentText==="Alpha");

    property bool isEmptyList : (listBox.listBox.count==0);
    property bool isNonSelected : (listBox.listBox.currentIndex==-1);
    Row{
         y:listBox.border.width*2
        Column{
            id:firstColumn
            ListboxControl{
                id:listControl
                width:listBox.width
                height:32
                border.width:2
                target: listBox
            }
            Listbox{
                id:listBox
                width: root.width / 3
                y:listControl.y+listControl.height
                height: root.height-(listControl.y+listControl.height)-root.border.width

                Connections {
                      target: listBox.listBox
                      onCurrentIndexChanged: {
                          effectsPanelAlpha.setTimeSliderValue1(effectsControll.getCurrentEffectProperty("alpha_start_time"));
                        effectsPanelAlpha.setTimeSliderValue2(effectsControll.getCurrentEffectProperty("alpha_end_time"));
                          effectsPanelAlpha.setInverstion(effectsControll.getCurrentEffectProperty("alpha_inversion"));
                          combo.currentIndex=effectsControll.getCurrentEffectProperty("effect_type");
                          //effectsControll.setCurrentEffectProperty("effect_type",currentIndex)
                      }
                  }
            }
        }
        Column
        {
            height:parent.height-root.border.width
            width:root.width-root.border.width
        ComboBox{
            id: combo
            width:root.width-firstColumn.width-border.width
            height:25
            y: root.border.width
            model: ListModel {

                  id: cbItems
                  ListElement { text: "Alpha"; color: "Yellow" }
                  ListElement { text: "Blur"; color: "Green" }
                  ListElement { text: "Other"; color: "Brown" }

              }
            onCurrentIndexChanged:{
                effectsControll.setCurrentEffectProperty("effect_type",currentIndex)
                console.log("onPressedChanged");
            }

        }


            SettingPages.EffectAlpha{
                id:effectsPanelAlpha
                y:listBox.border.width
                color: root.color
                width:parent.width-firstColumn.width
                height:parent.height-combo.height
                visible:isEffectAlpha && !isEmptyList && !isNonSelected

            }
        }



    }
}




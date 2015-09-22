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
    function loadEffectParams(){
        var startTime  = effectsControll.getCurrentEffectProperty("start_time")
       var endTime=effectsControll.getCurrentEffectProperty("end_time")
        var inversion=effectsControll.getCurrentEffectProperty("inversion")
        var effectType=effectsControll.getCurrentEffectProperty("effect_type")
        console.log("current index changed");
        console.log("startTime:"+startTime);
        console.log("endTime:"+endTime);
        console.log("inversion:"+inversion);
        console.log("effectType:"+effectType);
        combo.currentIndex=effectType;
        console.log("secondColumn.comboEffectType:"+effectType);

        switch(effectType)
        {
        case 0:
            //default:
            console.log("case 0");

            effectsPanelAlpha.setStartTime(startTime);
            effectsPanelAlpha.setEndTime(endTime);
            effectsPanelAlpha.setInverted(inversion);
            break;
         case 1:
            console.log("case 1");

            effectsPanelSpin.setStartTime(startTime);
            effectsPanelSpin.setEndTime(endTime);
            effectsPanelSpin.setInverted(inversion);
            break;
         case 2:
             effectsPanelPixelization.setStartTime(startTime);
             effectsPanelPixelization.setEndTime(endTime);
             effectsPanelPixelization.setInverted(inversion);
             break;

        }
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
    property bool isEffectAlpha : (combo.currentIndex===0);
    property bool isEffectSpin : (combo.currentIndex===1);
    property bool isEffectPixelization : (combo.currentIndex===2);

    property bool isEmptyList : (listBox.listBox.count==0);
    property bool isNonSelected : (listBox.listBox.currentIndex==-1);



    Row{
        width: root.width-root.border.width
        x:root.border.width
        y:root.border.width
        Column{
            width:root.width/3
            id:firstColumn
            ListboxControl{
                id:listControl
                // width:listBox.width
                height:32
                border.width:2
                target: listBox
            }
            Listbox{
                id:listBox
                width: firstColumn.width
                y:listControl.y+listControl.height
                height: root.height-(listControl.y+listControl.height)-root.border.width*2
               /* property double startTime
                property double endTime
                property double inversion
                property double effectType*/

                Connections {
                    target: listBox.listBox
                    onCurrentIndexChanged: {

                       loadEffectParams()

                        //effectsControll.setCurrentEffectProperty("effect_type",currentIndex)
                    }
                }
            }
        }
        Column
        {
            id:secondColumn
            property  int comboEffectType: combo.currentIndex
            height:parent.height-root.border.width
            width:root.width-firstColumn.width-root.border.width*2
            // width:root.width-root.border.width
            ComboBox{
                id: combo
                height:25
                y: root.border.width
                width:secondColumn.width
                model: ListModel {

                    id: cbItems
                    ListElement { text: "Alpha"; color: "Yellow" }
                    ListElement { text: "Spin"; color: "Green" }
                    ListElement { text: "Pixelization"; color: "Brown" }

                }
                onCurrentIndexChanged:{
                    effectsControll.setCurrentEffectProperty("effect_type",combo.currentIndex)
                    loadEffectParams()
                    console.log("onPressedChanged:"+combo.currentIndex );
                }

            }


            SettingPages.EffectAlpha{
                id:effectsPanelAlpha
                y:listBox.border.width
                color: root.color
                width:secondColumn.width
                height:parent.height-combo.height
                visible:isEffectAlpha && !isEmptyList && !isNonSelected

            }
            SettingPages.EffectSpin{
                id:effectsPanelSpin
                y:listBox.border.width
                color: root.color
                width:secondColumn.width
                height:parent.height-combo.height
                visible:isEffectSpin && !isEmptyList && !isNonSelected

            }
            SettingPages.EffectPixelization{
                id:effectsPanelPixelization
                y:listBox.border.width
                color: root.color
                width:secondColumn.width
                height:parent.height-combo.height
                visible:isEffectPixelization && !isEmptyList && !isNonSelected

            }
        }



    }
}




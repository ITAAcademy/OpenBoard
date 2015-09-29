import QtQuick 2.4
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.2

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
        var count = effectsControll.getCurrentEffectProperty("count");
        var elementSize = effectsControll.getCurrentEffectProperty("elementSize");
        console.log("current index changed");
        console.log("startTime:"+startTime);
        console.log("endTime:"+endTime);
        console.log("inversion:"+inversion);
        console.log("effectType:"+effectType);
        console.log("count:"+count);
        combo.currentIndex=effectType;
        console.log("secondColumn.comboEffectType:"+effectType);

        switch(effectType)
        {
        case 0:
            //default:
            effectsPanelAlpha.setStartTime(startTime);
            effectsPanelAlpha.setEndTime(endTime);
            effectsPanelAlpha.setInverted(inversion);
            break;
        case 1:
            effectsPanelSpin.setStartTime(startTime);
            effectsPanelSpin.setEndTime(endTime);
            effectsPanelSpin.setInverted(inversion);
            break;
        case 2:
            if (elementSize>effectsPanelPixelization.elementSizeSlider.maximum)
                elementSize = effectsPanelPixelization.elementSizeSlider.maximum
            if (elementSize<effectsPanelPixelization.elementSizeSlider.minimum)
                elementSize = effectsPanelPixelization.elementSizeSlider.minimum
            effectsPanelPixelization.setStartTime(startTime)
            effectsPanelPixelization.setEndTime(endTime)
            effectsPanelPixelization.setInverted(inversion)
            effectsPanelPixelization.setElementSize(elementSize)
            effectsControll.setCurrentEffectProperty("elementSize",elementSize)
            break;
        case 3:
             if (count>effectsPanelCircles.countSlider.maximum)
                 count = effectsPanelCircles.countSlider.maximum
             if (count<effectsPanelCircles.countSlider.minimum)
                 count = effectsPanelCircles.countSlider.minimum
            effectsPanelCircles.setStartTime(startTime)
            effectsPanelCircles.setEndTime(endTime)
            effectsPanelCircles.setInverted(inversion)
            effectsPanelCircles.setCount(count)
            effectsControll.setCurrentEffectProperty("count",count)

            break;
        case 4:
            effectsTurnthepage.setStartTime(startTime);
            effectsTurnthepage.setEndTime(endTime);
            effectsTurnthepage.setInverted(inversion);
            break;
        case 5:
            effectsRandomSquares.setStartTime(startTime);
            effectsRandomSquares.setEndTime(endTime);
            effectsRandomSquares.setInverted(inversion);
            break;
        case 6:
            effectsTreshold.setStartTime(startTime);
            effectsTreshold.setEndTime(endTime);
            effectsTreshold.setInverted(inversion);
        case 7:
            effectsSlide.setStartTime(startTime);
            effectsSlide.setEndTime(endTime);
            effectsSlide.setInverted(inversion);


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
    property bool isEffectCircles : (combo.currentIndex===3);
    property bool isEffectTurnthepage : (combo.currentIndex===4);
    property bool isEffectRandomSquares : (combo.currentIndex===5);
    property bool isEffectTreshold : (combo.currentIndex===6);
    property bool isEffectSlide : (combo.currentIndex == 7);

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
                        //  effectsControll.setCurrentEffectProperty("effect_type",currentIndex);
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
                height:listControl.height
                y: root.border.width
                width:secondColumn.width

                style: ComboBoxStyle {
                    id: comboBox

                    background: Rectangle {
                        id: rectCategory
                        color: "#333"
                    }
                    label: Text {
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        font.pointSize: 15
                        font.family: "Courier"
                        font.capitalization: Font.SmallCaps
                        color: "white"
                        text: control.currentText
                    }

                    // drop-down customization here
                    property Component __dropDownStyle: MenuStyle {
                        __maxPopupHeight: 600
                        __menuItemType: "comboboxitem"

                        frame: Rectangle {              // background
                            color: "#555"
                        }

                        itemDelegate.label:             // an item text
                                                        Text {
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                            font.pointSize: 15
                            font.family: "Courier"
                            font.capitalization: Font.SmallCaps
                            color: styleData.selected ? "gray" : "white"
                            text: styleData.text
                        }

                        itemDelegate.background: Rectangle {  // selection of an item
                            radius: 2
                            color: styleData.selected ? "darkGray" : "transparent"
                        }

                        __scrollerStyle: ScrollViewStyle { }
                    }
                }

                model: ListModel {

                    id: cbItems
                    ListElement { text: "Alpha"; color: "Yellow" }
                    ListElement { text: "Spin"; color: "Green" }
                    ListElement { text: "Pixelization"; color: "Brown" }
                    ListElement { text: "Circles"; color: "Green" }
                    ListElement { text: "Turn the page"; color: "Green" }
                    ListElement { text: "Random squares"; color: "Pink" }
                    ListElement { text: "Treshold"; color: "Pink" }
                    ListElement { text: "Slide"; color: "Yellow" }

                }
                onCurrentIndexChanged:{
                    effectsControll.setCurrentEffectProperty("effect_type",currentIndex);
                    loadEffectParams();
                    console.log("onPressedChanged");
                }
                /*Rectangle{
                    height: 3
                    width: parent.width
                    color: "white"
                    anchors.bottom: parent.bottom

                }*/

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
            SettingPages.EffectCircles{
                id:effectsPanelCircles
                y:listBox.border.width
                color: root.color
                width:secondColumn.width
                height:parent.height-combo.height
                visible:isEffectCircles && !isEmptyList && !isNonSelected

            }
            SettingPages.EffectTurnthepage{
                id:effectsTurnthepage
                y:listBox.border.width
                color: root.color
                width:secondColumn.width
                height:parent.height-combo.height
                visible:isEffectTurnthepage && !isEmptyList && !isNonSelected

            }
            SettingPages.EffectRandomsquares{
                id:effectsRandomSquares
                y:listBox.border.width
                color: root.color
                width:secondColumn.width
                height:parent.height-combo.height
                visible:isEffectRandomSquares && !isEmptyList && !isNonSelected

            }
            SettingPages.EffectTreshold{
                id:effectsTreshold
                y:listBox.border.width
                color: root.color
                width:secondColumn.width
                height:parent.height-combo.height
                visible:isEffectTreshold && !isEmptyList && !isNonSelected
            }
            SettingPages.EffectSlide{
                id:effectsSlide
                y:listBox.border.width
                color: root.color
                width:secondColumn.width
                height:parent.height-combo.height
                visible:isEffectSlide && !isEmptyList && !isNonSelected
            }
        }



    }
}




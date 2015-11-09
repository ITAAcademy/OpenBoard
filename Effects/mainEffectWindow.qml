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
    Connections{
        target:effectsControll
        onShowSignal: loadEffectParams();
    }

    function loadEffectParams(){
        var startTime  = effectsControll.getCurrentEffectProperty("start_time")
        var endTime=effectsControll.getCurrentEffectProperty("end_time")
        var inversion=effectsControll.getCurrentEffectProperty("inversion")
        var effectType=effectsControll.getCurrentEffectProperty("effect_type")
        var count = effectsControll.getCurrentEffectProperty("count");
        var elementSize = effectsControll.getCurrentEffectProperty("elementSize");
        var rotateAngle = effectsControll.getCurrentEffectProperty("rotate_angle");
        var moveDestinationX = effectsControll.getCurrentEffectProperty("move_destination_x");
        var moveDestinationY = effectsControll.getCurrentEffectProperty("move_destination_y");
        var isMove = effectsControll.getCurrentEffectProperty("moving");
        console.log("current index changed");
        console.log("startTime:"+startTime);
        console.log("endTime:"+endTime);
        console.log("inversion:"+inversion);
        console.log("effectType:"+effectType);
        console.log("count:"+count);
        combo.currentIndex=effectType;
        console.log("secondColumn.comboEffectType:"+effectType);
        effectsPanelAlpha.disable();
        effectsPanelSpin.disable();
        effectsPanelPixelization.disable();
        effectsPanelCircles.disable();
        effectsTurnthepage.disable();
        effectsRandomSquares.disable();
        effectsTreshold.disable();
        effectsSlide.disable();
        effectsTransformations.disable();
        switch(effectType)
        {
        case 0:
            console.log("effectsPanelAlpha");
            effectsPanelAlpha.enable();

            effectsPanelAlpha.setEndTime(endTime);
            effectsPanelAlpha.setStartTime(startTime);
            effectsPanelAlpha.setInverted(inversion);
            break;
        case 1:
            console.log("effectsPanelSpin");
            effectsPanelSpin.enable();
            effectsPanelSpin.setStartTime(startTime);
            effectsPanelSpin.setEndTime(endTime);
            effectsPanelSpin.setInverted(inversion);
            break;
        case 2:
            console.log("effectsPanelPixelization");
            effectsPanelPixelization.enable();
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
            console.log("effectsPanelCircles");
            effectsPanelCircles.enable();
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
            console.log("effectsTurnthepage");
            effectsTurnthepage.enable();
            effectsTurnthepage.setStartTime(startTime);
            effectsTurnthepage.setEndTime(endTime);
            effectsTurnthepage.setInverted(inversion);
            break;
        case 5:
            console.log("effectsRandomSquares");
            effectsRandomSquares.enable();
            effectsRandomSquares.setStartTime(startTime);
            effectsRandomSquares.setEndTime(endTime);
            effectsRandomSquares.setInverted(inversion);
            break;
        case 6:
            console.log("effectsTreshold");
            effectsTreshold.enable();
            effectsTreshold.setStartTime(startTime);
            effectsTreshold.setEndTime(endTime);
            effectsTreshold.setInverted(inversion);
            break;
        case 7:
            console.log("effectsSlide");
            effectsSlide.enable();
            effectsSlide.setStartTime(startTime);
            effectsSlide.setEndTime(endTime);
            effectsSlide.setInverted(inversion);
        break;
        case 8:
            console.log("effectsSlide");
            effectsTransformations.enable();
            effectsTransformations.setStartTime(startTime);
            effectsTransformations.setEndTime(endTime);
            effectsTransformations.setInverted(inversion);
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
    property bool isEffectAlpha : (combo.comboIndex==0);
    property bool isEffectSpin : (combo.comboIndex==1);
    property bool isEffectPixelization : (combo.comboIndex==2);
    property bool isEffectCircles : (combo.comboIndex==3);
    property bool isEffectTurnthepage : (combo.comboIndex==4);
    property bool isEffectRandomSquares : (combo.comboIndex==5);
    property bool isEffectTreshold : (combo.comboIndex==6);
    property bool isEffectSlide : (combo.comboIndex == 7);
    property bool isEffectTransformations : (combo.comboIndex == 8);


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
                        //TODO

                        loadEffectParams();
                        secondColumn.processZ();

                        //effectsControll.setCurrentEffectProperty("effect_type",currentIndex)
                    }
                }
            }
        }
        Column
        {
            id:secondColumn

            height:parent.height-root.border.width
            width:root.width-firstColumn.width-root.border.width*2
            // width:root.width-root.border.width
            ComboBox{
                id: combo
                height:listControl.height
                y: root.border.width
                width:secondColumn.width
                property int comboIndex;
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
                        text:  control.currentText
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
                            text:  styleData.text
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
                     ListElement { text: "Transformations"; color: "Yellow" }

                }
                onCurrentIndexChanged:{
                    //TODO
                    effectsControll.setCurrentEffectProperty("effect_type",currentIndex);
combo.comboIndex=currentIndex;
                    loadEffectParams();
                    secondColumn.processZ();

                    console.log("onPressedChanged");
                }
                /*Rectangle{
                    height: 3
                    width: parent.width
                    color: "white"
                    anchors.bottom: parent.bottom

                }*/

            }
            function processZ(){
               effectsPanelAlpha.z=0;
                effectsPanelSpin.z=0;
                effectsPanelPixelization.z=0;
                effectsPanelCircles.z=0;
                effectsTurnthepage.z=0;
                effectsRandomSquares.z=0;
                effectsTreshold.z=0;
                effectsSlide.z=0;
                effectsTransformations.z=0;
                if (isEffectAlpha)effectsPanelAlpha.z=1;
                else
                if (isEffectSpin)effectsPanelSpin.z=1;
                else
                if(isEffectPixelization)effectsPanelPixelization.z=1;
                else
                if(isEffectCircles)effectsPanelCircles.z=1;
                else
                if(isEffectTurnthepage)effectsTurnthepage.z=1;
                else
                if(isEffectRandomSquares)effectsRandomSquares.z=1;
                else
                if (isEffectTreshold)effectsTreshold.z=1;
                else
                if (isEffectSlide)effectsSlide.z=1;
                else if
                (isEffectTransformations)effectsSlide.z=1;
                else
                if (isEffectTransformations)effectsTransformations.z=1;
                console.log("effectsPanelAlpha.z:"+effectsPanelAlpha.z);
                console.log("effectsPanelSpin.z:"+effectsPanelSpin.z);
                console.log("effectsPanelPixelization.z:"+effectsPanelPixelization.z);

            }
Item{
    width:parent.width
    height:parent.height
            SettingPages.EffectAlpha{
                id:effectsPanelAlpha
                y:listBox.border.width
                color: root.color
                width:secondColumn.width
                height:parent.height
                visible:!isEmptyList && !isNonSelected
                enabled: false;
                function enable(){
                    enabled=true;
                }
                function disable(){
                    enabled=false;
                }

            }
            SettingPages.EffectSpin{
                id:effectsPanelSpin
                y:listBox.border.width
                color: root.color
                width:secondColumn.width
                height:parent.height
                visible:!isEmptyList && !isNonSelected
                enabled: false;
                function enable(){
                    enabled=true;
                }
                function disable(){
                    enabled=false;
                }

            }
            SettingPages.EffectPixelization{
                id:effectsPanelPixelization
                y:listBox.border.width
                color: root.color
                width:secondColumn.width
                height:parent.height
                visible:!isEmptyList && !isNonSelected
                enabled: false;
                function enable(){
                    enabled=true;
                }
                function disable(){
                    enabled=false;
                }
            }
            SettingPages.EffectCircles{
                id:effectsPanelCircles
                y:listBox.border.width
                color: root.color
                width:secondColumn.width
                height:parent.height
                visible:!isEmptyList && !isNonSelected
                enabled: false;
                function enable(){
                    enabled=true;
                }
                function disable(){
                    enabled=false;
                }
            }
            SettingPages.EffectTurnthepage{
                id:effectsTurnthepage
                y:listBox.border.width
                color: root.color
                width:secondColumn.width
                height:parent.height
                visible:!isEmptyList && !isNonSelected
                enabled: false;
                function enable(){
                    enabled=true;
                }
                function disable(){
                    enabled=false;
                }
            }
            SettingPages.EffectRandomsquares{
                id:effectsRandomSquares
                y:listBox.border.width
                color: root.color
                width:secondColumn.width
                height:parent.height
                visible:!isEmptyList && !isNonSelected
                enabled: false;
                function enable(){
                    enabled=true;
                }
                function disable(){
                    enabled=false;
                }
            }
            SettingPages.EffectTreshold{
                id:effectsTreshold
                y:listBox.border.width
                color: root.color
                width:secondColumn.width
                height:parent.height
                visible: !isEmptyList && !isNonSelected
                enabled: false;
                function enable(){
                    enabled=true;
                }
                function disable(){
                    enabled=false;
                }
            }
            SettingPages.EffectSlide{
                id:effectsSlide
                y:listBox.border.width
                color: root.color
                width:secondColumn.width
                height:parent.height
                visible:!isEmptyList && !isNonSelected
                enabled: false;
                function enable(){
                    enabled=true;
                }
                function disable(){
                    enabled=false;
                }
            }
            SettingPages.EffectSlide{
                id:effectsTransformations
                y:listBox.border.width
                color: root.color
                width:secondColumn.width
                height:parent.height
                visible:!isEmptyList && !isNonSelected
                enabled: false;
                function enable(){
                    enabled=true;
                }
                function disable(){
                    enabled=false;
                }
            }

}
        }



    }
}




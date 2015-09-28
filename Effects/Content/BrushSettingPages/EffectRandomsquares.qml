import QtQuick 2.0
import QtQuick.Controls 1.2


Rectangle {

    function getStartTime(){
        return doubleSliderTime.value1;
    }
    function setStartTime(n){
        doubleSliderTime.value1=n
    }
    function setEndTime(n){
        doubleSliderTime.value2=n
    }
    function setInverted(val){
        cbInversion.checked=val
    }

    //property alias inversion : cbInversion.checked
   // property alias sliderTimer : doubleSliderTime
    id: root
    width: parent.width
    height: parent.height
    //anchors.fill: parent
    color: "transparent"
    property string cLoaderName: "loader"
    signal update
    onUpdate: {
        //console.log("update brush");
    }
    Column{
        spacing:10
        width: parent.width
        y: 15
        property int fix_height: 26

        CheckBox {
            id:cbInversion
                text: qsTr("Inversion")
                checked: false
                onCheckedChanged: {
                    effectsControll.setCurrentEffectProperty("inversion",checked);
                }
            }

        DoubleSlider
        {
            id:doubleSliderTime
     width:root.width
     height:10
    name: "time"
    value1:0
    value2:0
  /*  onValue1Changed: {
        startTime=value1
    }
    onValue2Changed: {
        endTime=value2
    }*/
    onMouse_drag_left_signal: {
     effectsControll.setCurrentEffectProperty("start_time",value1);
}
    onMouse_drag_right_signal: {
     effectsControll.setCurrentEffectProperty("end_time",value2);
}
        }

    }
}


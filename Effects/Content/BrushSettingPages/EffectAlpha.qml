import QtQuick 2.0
import QtQuick.Controls 1.2


Rectangle {
    function setTimeSliderValue1(n){
        doubleSliderTime.value1=n;
    }
    function setTimeSliderValue2(n){
       doubleSliderTime.value2=n;
    }
    function setInverstion(istrue){
        cbInversion.checked=istrue;
    }

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
                checked: true
                onCheckedChanged: {
                    effectsControll.setCurrentEffectProperty("alpha_inversion",checked);
                }
            }

        DoubleSlider
        {
            id:doubleSliderTime
     width:root.width
     height:10
    name: "time"

        }

    }
}


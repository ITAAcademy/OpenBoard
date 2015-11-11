import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.3

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
    function setAngle(val){
        angleSlider.value1=val;
    }
    function setToXPos(n){
        posX.value=n;
    }
    function setToYPos(n){
        posY.value=n;
    }
    function setMoveToEnable(v){
        cbMoveToEnable.checked=v;
    }

    function resetToDefault(){
        setStartTime(0);
        setEndTime(0);
        setInverted(false);
        setAngle(0);
        setToXPos(0);
        setToYPos(0);
        setMoveToEnable(false);
    }

    //property alias inversion : cbInversion.checked
    // property alias sliderTimer : doubleSliderTime
    property alias angleSlider : angleSlider
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
        spacing:20
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

            onMouse_drag_left_signal: {
                effectsControll.setCurrentEffectProperty("start_time",value1);
            }
            onMouse_drag_right_signal: {
                effectsControll.setCurrentEffectProperty("end_time",value2);
            }
        }
        Column{



            FullSlider{
                name:"angle"
                id: angleSlider
                maximum:360
                width:root.width
                height:10
                minimum: 1
                value1: 1
                onMouse_drag_signal:  {
                    effectsControll.setCurrentEffectProperty("rotate_angle",value1);
                }
            }

            SpinBox {
                id: posX

                style: SpinBoxStyle{
                    background: Rectangle {
                        implicitWidth: 100
                        implicitHeight: 20
                        border.color: "dimgrey"
                        color: "#666"
                        radius: 2
                    }
                    textColor: "white"

                    horizontalAlignment: Qt.AlignLeft
                }
                minimumValue: 0
                stepSize : 1
                maximumValue: 640// maximum/1000
                width: 50
                decimals: 0
                font.pixelSize: 14
                value: 0
                onValueChanged: {
                    setToXPos(value);
                    effectsControll.setCurrentEffectProperty("to_x_pos",value);
                    //console.log(" GGGGGGGGGGGG  " + value)
                }

            }

            SpinBox {
                id: posY

                style: SpinBoxStyle{
                    background: Rectangle {
                        implicitWidth: 100
                        implicitHeight: 20
                        border.color: "dimgrey"
                        color: "#666"
                        radius: 2
                    }
                    textColor: "white"

                    horizontalAlignment: Qt.AlignLeft
                }
                minimumValue: 0
                stepSize : 1
                maximumValue: 640// maximum/1000
                width: 50
                decimals: 0
                font.pixelSize: 14
                value: 0
                onValueChanged: {
                    setToYPos(value);
                    effectsControll.setCurrentEffectProperty("to_y_pos",value);
                }

            }
            CheckBox {
                id:cbMoveToEnable
                text: qsTr("Moving")
                checked: false
                onCheckedChanged: {
                    effectsControll.setCurrentEffectProperty("move_to_enable",checked);
                }
            }
        }

    }
}


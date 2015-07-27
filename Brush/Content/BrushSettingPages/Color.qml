import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

Rectangle {
    id: root
    width: parent.width
    height: parent.height
    //anchors.fill: parent
    color: "transparent"
    property string cLoaderName: "loader"
    signal update
    onUpdate: {
        brushControll.setColor(Qt.hsla(h.value, s.value, l.value));
        show_brush_image.update();
    //    console.log("update color");
    }

    Column{
        width: parent.width
        y: 15
        property int fix_height: 26
        spacing: 15
        FullSlider{
            id: h
            width: parent.width
            height: parent.fix_height
            name: "Hue"
            maximum : 1
            value: 0.5
            small: true
            mColor: Qt.hsla(h.value, s.value, l.value)
            onValueChanged:{
                rgb.focus = false;
                root.update();
            }
            onRelease:
            {
                brushControll.update();
            }
        }
        FullSlider{
            id: s
            width: parent.width
            height: parent.fix_height
            name: "SAT"
            maximum: 1
            small: true
            value: 1
            mColor: h.mColor
            onValueChanged:{
                rgb.focus = false;
                root.update();
            }
            onRelease:
            {
                brushControll.update();
            }

        }
        FullSlider{
            id:l
            width: parent.width
            height: parent.fix_height
            name: "LIGHT"
            maximum: 1
            small: true
            value: 0.5
            mColor: h.mColor
            onValueChanged:{
                rgb.focus = false;
                root.update();
            }
            onRelease:
            {
                brushControll.update();
            }
        }
        TextField {
            id: rgb
            font.pixelSize: 14
            text: brushControll.toHex(Qt.hsla(h.value, s.value, l.value));
            style: TextFieldStyle {
                textColor: "white"
                background: Rectangle {
                    radius: 2
                    implicitWidth: 100
                    implicitHeight: 24
                    border.color: "#333"
                    border.width: 1
                    color: "#333333"
                }
            }
            onTextChanged:
            {
                if(rgb.focus === true && brushControll.isColorValid(text) === true)
                {
                    s.value = brushControll.getSaturation(text);
                    l.value = brushControll.getLightness(text);
                    h.value = brushControll.getHue(text);
                    brushControll.update();
                }
            }
        }
    }

    Component.onCompleted:
    {
        brushControll.setColor(Qt.hsla(h.value, s.value, l.value));
        brushControll.update();
        console.log("ooooooooooooooooooooooooooooo");
    }
}


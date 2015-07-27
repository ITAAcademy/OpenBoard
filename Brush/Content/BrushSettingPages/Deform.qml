import QtQuick 2.0
import QtQuick.Controls 1.2

Rectangle {
    id: root
    width: parent.width
    height: parent.height
    //anchors.fill: parent
    color: "transparent"
    property string cLoaderName: "loader"
    signal update
    onUpdate: {
        console.log("update brush");
    }
    Column{
        width: parent.width
        y: 15
        property int fix_height: 26
        spacing: 15
        FullSlider{
            width: parent.width
            height: parent.fix_height
            name: "Ѧ SIZE"
            maximum : 100
            value: 0
            onValueChanged:
            {
                brushControll.setSizeDelta(value);
                show_brush_image.update();
            }
        }
        FullSlider{
            width: parent.width
            height: parent.fix_height
            name: "Ѧ ANGLE"
            maximum: 360
            value: 0
            onValueChanged:
            {
                brushControll.setAngleDelta(value);
                show_brush_image.update();
            }

        }
        FullSlider{
            width: parent.width
            height: parent.fix_height
            name: "AFFINE"
            maximum: 10
            value: 0
            onValueChanged:
            {
                brushControll.setAffine(value);
                show_brush_image.update();
            }
        }
    }
}


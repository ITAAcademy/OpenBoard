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
        //console.log("update brush");
    }
    Column{
        width: parent.width
        y: 15
        property int fix_height: 26
        spacing: 15
        FullSlider{
            id: size
            width: parent.width
            height: parent.fix_height
            name: "SIZE"
            minimum: 1
            maximum : 100
            value: 50
            onValueChanged:
            {
                brushControll.setSize(value);
                show_brush_image.update();
            }
        }
        FullSlider{
            width: parent.width
            height: parent.fix_height
            name: "SMOOTH"
            maximum: 100
            value: 0
            onValueChanged:
            {
                brushControll.setBlur(value);
                show_brush_image.update();
            }
            onRelease:
            {
                brushControll.update();
            }

        }
        FullSlider{
            width: parent.width
            height: parent.fix_height
            name: "OPACITY"
            maximum: 100
            value: 100
            onValueChanged:
            {
               // show_brush_image.opacity = value/100;
                brushControll.setOpacity(value);
                show_brush_image.update();
            }
            onRelease:
            {
                brushControll.update();
            }
        }
    }
}


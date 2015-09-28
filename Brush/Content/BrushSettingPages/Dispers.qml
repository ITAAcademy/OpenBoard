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
        FullSliderBrush{
            width: parent.width
            height: parent.fix_height
            name: "DISPERS"
            maximum : 100
            value: 0
            onValueChanged:
            {
                brushControll.setDisepers(value);
                show_brush_image.update();
            }
        }
        FullSliderBrush{
            width: parent.width
            height: parent.fix_height
            name: "COUNT"
            maximum: 10
            value: 0
            onValueChanged:
            {
                brushControll.setCount(value);
                show_brush_image.update();
            }

        }
        FullSliderBrush{
            width: parent.width
            height: parent.fix_height
            name: "DELTA"
            maximum: 100
            value: 0
            checkable: true
            onValueChanged:
            {
                brushControll.setSizeMax(value);
                show_brush_image.update();
            }
        }
    }
}


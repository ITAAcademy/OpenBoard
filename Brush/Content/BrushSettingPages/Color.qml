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
        brushControll.setColor(Qt.hsla(h.value, u.value, e.value));
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
            mColor: Qt.hsla(h.value, u.value, e.value)
            onValueChanged: root.update();
        }
        FullSlider{
            id: u
            width: parent.width
            height: parent.fix_height
            name: "SAT"
            maximum: 1
            small: true
            value: 1
            mColor: h.mColor
            onValueChanged: root.update();

        }
        FullSlider{
            id:e
            width: parent.width
            height: parent.fix_height
            name: "LIGHT"
            maximum: 1
            small: true
            value: 0.5
            mColor: h.mColor
            onValueChanged: root.update();
        }
    }
    Component.onCompleted:
    {
        brushControll.setColor(Qt.hsla(h.value, u.value, e.value));
        console.log("ooooooooooooooooooooooooooooo");
    }
}


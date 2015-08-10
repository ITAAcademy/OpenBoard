import QtQuick 2.0
import QtGraphicalEffects 1.0

Rectangle {
    id: root
    height: 40
    width: menu.maxHorizontSize - 20
    x: (menu.maxHorizontSize - width)/2
    radius: 10
    border.color: "white"
    antialiasing: true
    smooth: true
    color: "transparent"
    signal clicked
    border.width: 0
    property string title: "value"
    property bool rotation_animation: true
    property bool checked: false
    property bool checkable: true

    function unCheck()
    {
        checked = false;
        effect.visible = false;
        exited.start();
        if(root.rotation_animation)
        {
            rotation_start.stop();
            rotation_end.start();
        }

    }
    function check()
    {
        checked = true;
        effect.visible = true;
        enter.start();
        if(root.rotation_animation)
        {
            rotation_end.start();
        }

    }

    RectangularGlow {
        id: effect
        visible: false
        anchors.fill: root
        glowRadius: 3
      //  scale: root.scale
        spread: 0.2
        color: "white"
        cornerRadius: root.radius + glowRadius
    }
    Image {
        id: part1
        source: "qrc:/Content/Button_1.png"
        anchors.fill: parent
        Image {
            id: part2
            property int marging: 5
            source: "qrc:/Content/Button_2.png"
            anchors.right: parent.right
            anchors.rightMargin: 10
            height: parent.height - marging
            y: marging/2
            width: height
            Image {
                id: part3
                source: "qrc:/Content/Button_3.png"
                anchors.fill: parent
                transform: Rotation {id: rotation_part_3; origin.x: part3.width/2; origin.y: part3.height/2; angle: 0}
            }
        }
    }

    MouseArea
    {
        id: menu_mouse
        anchors.fill: parent
        hoverEnabled: true
        property double scale_value: 1.2
        property int duration: 300
        property bool isFocus: false
        onClicked: {
            root.clicked()
            if(root.checkable)
            root.check();
        }
        onPressed: {
            effect.visible =true;
        }
        onReleased: {
            if(root.checkable === false || menu_mouse.isFocus == false && root.checked == false)
                effect.visible = false;
        }

        onEntered:
        {
            menu_mouse.isFocus = true;
            if(root.checkable == false || root.checked == false)
            {
                enter.start();
                if(root.rotation_animation)
                    rotation_start.start();
            }
        }
        onExited:
        {
            menu_mouse.isFocus = false;
            if(root.checkable == false || root.checked == false)
            {
                exited.start();
                if(root.rotation_animation)
                {
                    rotation_start.stop();
                    rotation_end.start();
                }
            }
        }
        NumberAnimation {id: enter; target: root; property: "scale"; to: menu_mouse.scale_value; duration: menu_mouse.duration }
        NumberAnimation {id: exited; target: root; property: "scale"; to: 1; duration: menu_mouse.duration }
        NumberAnimation {id: rotation_start; target: rotation_part_3; loops: Animation.Infinite; property: "angle"; duration: menu_mouse.duration*10; from: 0; to:360}
        NumberAnimation {id: rotation_end; target: rotation_part_3; property: "angle"; duration: 100; to:0}
    }
    Text {
        id: title
        color: "white"
        font.pixelSize: 14
        //anchors.fill: parent
        x: 10
        y: (parent.height - paintedHeight)/2
        text: root.title
        style: Text.Outline;
        styleColor: "black"
    }

}


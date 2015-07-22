import QtQuick 2.4
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0

import "Content" as Content
import "Content/BrushSettingPages" as SettingPages

Rectangle{
    id: root
    width: 300
    height: 400
    //anchors.margins: 25
    border.width: 10
    border.color: "#333333"
    color: "#777777"
    radius: 10
    smooth: true
/*
  //coner

    RectangularGlow {
        id: effect
        anchors.fill: root
        anchors.margins: 3
        glowRadius: 3
        spread: 0.01
        color: "#777777"
        cornerRadius: root.radius + glowRadius
    }
*/
    Image {
        id: skeen
        width: parent.width - root.border.width*2
        height: parent.height * 0.2
        source: "qrc:/Content/brush_skeen.png"
        visible: false
        //fillMode: Image.PreserveAspectCrop
        x: root.border.width
        y: root.border.width + 3

    }
    Image {
        id: show_brush_image
        width: parent.width - root.border.width*2
        height: parent.height * 0.2
        source: "image://loader/head"
        fillMode: Image.PreserveAspectFit
        x: root.border.width
        y: root.border.width + 3
        function update()
        {
            show_brush_image.source = "image://loader/h" + Math.round(Math.random()*10000);
        }

        Timer{
            interval: 500
            running: false
            repeat: true
            onTriggered: {
                show_brush_image.update();
            }
        }

    }
    Content.Separator{
        y: show_brush_image.height + show_brush_image.y + 5
    }

    Row{
        id: choice
        property int count: 5
        width: parent.width
        height: 25
        x: root.border.width
        y: show_brush_image.height + show_brush_image.y + 10
        function hideAll()
        {
            p_image.visible = false;
            p_body.visible = false;
            p_deform.visible = false;
            p_dispers.visible = false;
            p_color.visible = false;
        }

        Content.Button{
            id: image
            title: "Image"
            onClicked: {
                choice.hideAll();
                p_image.visible = true;
            }
        }
        Content.Button{
            id: image2
            title: "Body"
            onClicked: {
                choice.hideAll();
                p_body.visible = true;
            }
        }
        Content.Button{
            id: image3
            title: "Dispers"
            onClicked: {
                choice.hideAll();
                p_dispers.visible = true;
            }
        }
        Content.Button{
            id: image4
            title: "Color"
            onClicked: {
                choice.hideAll();
                p_color.visible = true;
            }
        }
        Content.Button{
            id: image5
            title: "Deform"
            onClicked: {
                choice.hideAll();
                p_deform.visible = true;
            }
        }
    }
    Content.Separator{
        y: choice.height + choice.y + 5
    }
    Item{
        id: pages
        width: parent.width - root.border.width*2
        x: root.border.width
        y: choice.height + choice.y + 15
        height: parent.height - y - 10
        //height: 200

        Component.onCompleted:
        {

        }

            SettingPages.Image{
                id: p_image
                x:5
            }
            SettingPages.Body{
                id: p_body
                x:5
                visible: false
            }

            SettingPages.Deform{
                id: p_deform
                x:5
                visible: false
            }
            SettingPages.Color{
                id: p_color
                x:5
                visible: false
            }
            SettingPages.Dispers{
                id: p_dispers
                x:5
                visible: false
            }

        }
    }

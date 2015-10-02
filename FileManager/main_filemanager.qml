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

    Content.MouseAreaForWindowDraging{
        id: draging_MA
        width: root.width
        height: 50

    }

    property string finishFileName : ""

    Timer {
        id : double_click_timer
           interval: 300; running: false;
       }

    RectangularGlow {
        id: effect
        anchors.fill: root
        anchors.margins: 3
        glowRadius: 3
        spread: 0.01
        color: "#777777"
        cornerRadius: root.radius + glowRadius
    }

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
        height: 0// parent.height * 0.2
        source: "image://loader/head"
        fillMode: Image.PreserveAspectFit
        antialiasing: true
        x: root.border.width
        y: root.border.width + 3
        visible: false

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
            p_image.p_rep.abortBorders()
            p_video.visible = false;
            p_video.p_rep.abortBorders()
            p_audio.visible = false;
            p_audio.p_rep.abortBorders()
            finishFileName = ""
        }

        Content.Button{
            id: image
            title: "Image"
            width : (parent.width - parent.x*2)/3
            onClicked: {
                choice.hideAll();
                p_image.visible = true;
            }
        }
        Content.Button{
            id: video
            title: "Video"
            width : image.width
            onClicked: {
                choice.hideAll();
                p_video.visible = true;
            }
        }
        Content.Button{
            id: audio
            title: "Audio"
            width : image.width
            onClicked: {
                choice.hideAll();
                p_audio.visible = true;
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
        height: parent.height - y - 50
        //height: 200

        Component.onCompleted:
        {

        }

            SettingPages.Image{
                id: p_image
                x:5
            }
            SettingPages.Video{
                id: p_video
                x:5
                visible: false
            }

            SettingPages.Audio{
                id: p_audio
                x:5
                visible: false
            }

    //    }

        }
    Content.Separator{
        y: pages.height + pages.y
    }
   // Row {


        Content.Button2{
            x: 20
            y: pages.height + pages.y + 5
            width : (parent.width - parent.x*2)/3
            id: b_ok
            title: "OK"

            onClicked: {

                brushControll.setFilePathName(finishFileName)
                brushControll.hide()

                //set file name
            }
        }
       Content.Button2{

           id: b_calnec
             y: b_ok.y

          x: pages.width - width
            title : "Cancel"
            width : b_ok.width
            onClicked: {
                ///close it
                finishFileName = ""
               // brushControll.setFilePathName(finishFileName)
                brushControll.hide()
            }
        }

       Connections{
           target: brushControll
           onUpdate:{
               p_image.update();
               p_audio.update();
               p_video.update();
           }
       }

       // }

}



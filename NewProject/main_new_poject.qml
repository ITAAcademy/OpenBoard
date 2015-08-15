import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Controls.Styles 1.2

import "Content" as Content
Rectangle{
    id: root
    anchors.fill: parent
    color: "#333333"
    property int project_state : -1
    Row{
        id: row
        spacing: 5
        anchors.margins: 10
        anchors.fill: parent
     //   clip: true
        Item{
            id: menu
            width: parent.width * 0.3
            height: parent.height
            property int maxHorizontSize: width
            ScrollView{
                width: menu.maxHorizontSize
                height: parent.height
                anchors.top: parent.top
                anchors.margins: 10
                Column
                {
                    id: my_col
                    spacing: 10
                    property int random_delta: 30 // cart by 10
                    function clean()
                    {
                        var obj = my_col.children;
                        for(var i = 0; i < obj.length; i++)
                        {
                            obj[i].unCheck();
                        }
                    }

                    Content.MenuItem{
                        id: m1
                        title: "New text video"
                        onClicked: {
                            my_col.clean();
                           // projectControll.setProjectState(0);
                            root.project_state = 0
                            content.next = c0;
                        }
                    }
                    Content.MenuItem{
                        id: m2
                        title: "New pro video"
                        onClicked: {
                            my_col.clean();
                            //projectControll.setProjectState(1);
                            root.project_state = 1
                            content.next = c1;
                        }
                    }
                    Content.MenuItem{
                        title: "New empty project"
                        onClicked: {
                            my_col.clean();
                           // projectControll.setProjectState(2);
                            root.project_state = 2
                            content.next = c2;
                        }
                    }
                    Content.MenuItem{
                        title: "New modeal animation"
                        onClicked: {
                            my_col.clean();
                           // projectControll.setProjectState(3);
                            root.project_state = 3
                            content.next = c3;
                        }
                    }
                    Content.MenuItem{
                        title: "New visual effect"
                        onClicked: {
                            my_col.clean();
                           // projectControll.setProjectState(4);
                            root.project_state = 4
                            content.next = c4;
                        }
                    }
                    Content.MenuItem{
                        id: open
                        title: "Open project"
                        visible: projectControll.isForStart()
                        onVisibleChanged: {
                            console.log(projectControll.isForStart());
                            if(projectControll.isForStart())
                                open.visible =  true;
                            else
                                open.visible =  false;
                        }

                        onClicked: {
                            my_col.clean();
                            //projectControll.setProjectState(5);
                            root.project_state = 5
                            projectControll.close();
                        }
                    }
                }
            }
            Component.onCompleted: {
            //    m2.check();
              //   content.next = c1;
            }
        }
        Rectangle{
            id: separator
            width: 3
            height: parent.height
            color: "#777777"
        }

        Item{
            id: content
            width: parent.width * 0.7
            height: parent.height
            property Item curent: c1
            property Item next: c1
            property int swap_animation_duration: 500

           NumberAnimation {id: one; target: content.curent; properties: "scale, opacity";from: 1.0; to: 0.0; duration: content.swap_animation_duration;
                onStopped: {
                    console.log("stop_1");
                    content.curent.visible = false;
                    two.start();
                }
            }
            NumberAnimation { id: two; target: content.next; properties: "scale, opacity"; from: 0.0; to: 1.0; duration: content.swap_animation_duration;
                onStarted: {
                    console.log("start_2");
                    content.next.visible = true;
                }
                onStopped: content.swap();
            }

            onNextChanged:
            {
                one.start();
            }
            function swap()
            {
               console.log("swap");
               content.curent = content.next;
            }

            ScrollView{
                id: content_scroll
                anchors.fill: parent
                Column{
                    Content.TextVideoContent{
                        id: c0
                        parent: content_scroll
                    }
                    Content.ContentItem{
                        id: c1
                        parent: content_scroll
                    }
                    Content.ContentItem{
                        id: c2
                        parent: content_scroll
                    }
                    Content.ContentItem{
                        id: c3
                        parent: content_scroll
                    }
                    Content.ContentItem{
                        id: c4
                        parent: content_scroll
                    }
                    Content.ContentItem{
                        id: c5
                        parent: content_scroll
                    }
                }


            }
            Rectangle{
                id: advance
                anchors.bottom: parent.bottom
                height: 20
                width: parent.width
                color: root.color
                CheckBox{
                    id: advance_check
                    checked: false
                    anchors.left: advance.left
                    anchors.leftMargin: 10
                    style: CheckBoxStyle {
                        indicator: Rectangle {
                                implicitHeight: advance.height
                                implicitWidth: implicitHeight
                                radius: 3
                                border.color: control.hovered ? "#777" : "#333"
                                border.width: 3
                                color: "#555"
                                Image {
                                    visible: control.checked
                                    source: "qrc:/checkbox.png"
                                    anchors.margins: 4
                                    anchors.fill: parent
                                }
                        }
                    }
                    Component.onCompleted:
                    {
                        projectControll.setAdvanceMode(advance_check.checked);
                    }
                    onCheckedChanged: {
                        projectControll.setAdvanceMode(advance_check.checked);
                    }
                }
                Text {
                    id: title_check
                    anchors.left: advance_check.right
                    anchors.leftMargin: 3
                    font.pixelSize: 12
                    color: "white"
                    text: qsTr("Advance mode")
                }
            }
            Rectangle{
                id: create_area
                x: parent.width - create_button.width - row.anchors.margins*4
                y: parent.height - create_button.height
                Content.MenuItem{
                    id: create_button
                    title: "Create"
                    rotation_animation: false
                    checkable: false
                    onClicked: {                        
                        projectControll.setProjectState(root.project_state);
                        projectControll.close();
                    }
                }
            }
        }
    }
}

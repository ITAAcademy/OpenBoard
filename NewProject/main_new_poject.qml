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
                            projectControll.setProjectState(0);
                        }
                    }
                    Content.MenuItem{
                        title: "New pro video"
                        onClicked: {
                            my_col.clean();
                            projectControll.setProjectState(1);
                        }
                    }
                    Content.MenuItem{
                        title: "New empty project"
                        onClicked: {
                            my_col.clean();
                            projectControll.setProjectState(2);
                        }
                    }
                    Content.MenuItem{
                        title: "New modeal animation"
                        onClicked: {
                            my_col.clean();
                            projectControll.setProjectState(3);
                        }
                    }
                    Content.MenuItem{
                        title: "New visual effect"
                        onClicked: {
                            my_col.clean();
                            projectControll.setProjectState(4);
                        }
                    }
                }
            }
            Component.onCompleted: {
                m1.check();
                projectControll.setProjectState(0);
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
            ScrollView{
                anchors.fill: parent
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
                        projectControll.close();
                    }
                }
            }
        }
    }
}

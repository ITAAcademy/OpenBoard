import QtQuick 2.4
import QtQuick.Controls 1.2

import "Block" as ContentBlock
import "ToolBar" as ContentToolBar

Item{
    id: root
    Row {
        id: menu
        width: parent.width
        height: parent.height
        ScrollView{
            width: parent.width - 50
            height: parent.height
            Row {
                id: clockview
                spacing: 5
                Repeater {
                    id: repka
                    model: timeControll.getTestSize()
                    delegate:
                    ContentBlock.Block{
                        id: cool
                        height: 200
                        width: timeControll.getTestWight(index)
                        mIndex: index
                        title: timeControll.getTest(index)

                    }
                }
            }
        }
        ContentToolBar.ToolBar{
            width: 50
            height: parent.height
            globalRep: repka
        }
    }
}

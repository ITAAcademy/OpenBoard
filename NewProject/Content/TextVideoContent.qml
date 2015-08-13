import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import QtQuick.Dialogs 1.2
import QtGraphicalEffects 1.0

import "." as Curent
ContentItem{
    Column{
        id: items_col
        anchors.fill: parent
        spacing: 10
        property int maxTextWidth: 0
        OpenImage{
            title: "START"
            onPathChange: {
                projectControll.textMode_SetFirstImage(getFilePath());
            }
            onTimeChange: {
                projectControll.textMode_SetFirstTime(getTime());
            }
        }
        OpenImage{
            title: "FINAL"
            onPathChange: {
                projectControll.textMode_SetLastImage(getFilePath());
            }
            onTimeChange: {
                projectControll.textMode_SetLastTimeTime(getTime());
            }
        }
    }
}


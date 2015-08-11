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
        OpenImage{
            title: "START"
        }
        OpenImage{
            title: "FINAL"
        }
    }
}


import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtGraphicalEffects 1.0

import "Block" as ContentBlock
import "ToolBar" as ContentToolBar

    Item {
    id: item_col
    function addTrack()     {
    rep_columns.model +=1
    }
    function removeTrack()    {
    rep_columns.model -=1
    }
    property Item childa//: track
     property Item p_trackbar
    Column {
   id: columns
   width: parent.width
   spacing: 2
         Repeater {
             id: rep_columns
             model: 1

              delegate:
                  Row {
                  id: bar_track
                    ContentToolBar.TrackToolBar {
                           id: trackbar
                           width: 30
                           height: item_col.childa.height
                           z:12
                           x: 0
                           Component.onCompleted: {
                            p_trackbar = trackbar
                         }
                       }
                    Item{
                        x: trackbar.width
                        id: track
                        width: item_col.childa.width
                        height: item_col.childa.height
                    }
              }
         }

    }
    onChildrenChanged: {
        //console
        //item_col.children[1].parent = track
        item_col.childa = item_col.children[1]

    }
    Component.onCompleted: {
       item_col.p_trackbar.globalRep = item_col.children[1].globalRep
    }

    }


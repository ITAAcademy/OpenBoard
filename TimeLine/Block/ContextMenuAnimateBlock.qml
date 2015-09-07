import QtQuick 2.4
import QtGraphicalEffects 1.0
import QtQuick.Controls 1.2
import QtQuick.Window 2.2
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.2

ApplicationWindow {
    id: animate_block_wnd
     property int counter: 0
    property int anim_state: -1//anim_state_point.x //no anim = 0,begin = 1,end = 2, begin & end =3
    property int anim_time : -1//anim_state_point.y;
    property int blockIndex: 0
    property int columnIndex: 0
     property int block_time: 65534
    property bool anim_not_setted: true
    Component.onDestruction: {
        console.log("BBBBBBBBBBBBBBBB AAAAAAAAAAAAAA")

    }




    onClosing: {
// console.log("CCCCCCCCCCCCCCCCCCC counter = " + (++counter))
        //setAnim()
        if (block_anim_time_value.text.length ===0)
        {
            //block_anim_time_value.text = initValue;
        }
        else
        {
             setAnimTime()
        }
        setAnimState()
    }

    function closeIt()
    {
         //console.log("animate_block_wnd   closeIt( ) ")
        animate_block_wnd.close()
        animate_block_wnd.destroy()
    }

    function setAnim()
    {
        //console.log("AAAAAAAAAA AAAAAAAAAAAAAA AAAAAAAAAAAAAAAAAAA ="+anim_time)
         timeControll.setBlockAnimation(columnIndex,blockIndex,anim_state,anim_time)
    }


    function setAnimState()
    {
         //console.log("setAnimState() = " +columnIndex + " " + blockIndex + " "  + anim_state)
         timeControll.setBlockAnimationState(columnIndex,blockIndex,anim_state)
    }

    function setAnimTime()
    {
        var time = (block_anim_time_value.text)
         console.log("setAnimTime() = " +columnIndex + " " + blockIndex + " "  + time)
         timeControll.setBlockAnimationTime(columnIndex,blockIndex,(time))
    }




    onAnim_stateChanged:
    {
        switch (anim_state)
        {
        case 0:
            rb_no_anim.checked = true;
            break;
        case 1:
            rb_anim_on_begin.checked = true;
            break;
        case 2:
            rb_anim_on_end.checked = true;
            break;
        case 3:
            rb_anim_on_begin_end.checked = true;
            break;
        }

    }
     Rectangle {

         Component.onCompleted: {
            /* anim_state = anim_state_point.x
             anim_time = anim_state_point.y
             block_anim_time_value.text = block_anim_time_value.initValue = anim_time*/
         }

         border {width: 5; color: "black" }
        /* x: parent.width/2
         y: but_append.y
         z: 5*/
         id: animate_block_items
         visible: true
         width: parent.width

         height: parent.height// rb_no_anim.height * 3 + block_anim_time_value.height*/
         color: "gray"
         GroupBox {
             //title: "Tab Position"
             ColumnLayout {
                 id: rb_col_layout
                 ExclusiveGroup { id: tabPositionGroup }
         ContextRadioButton {
             id: rb_no_anim
            text: "no animations"
            checked: true
            exclusiveGroup: tabPositionGroup
            onCheckedChanged: {
                if (checked)
                {
                    animate_block_wnd.anim_state = 0;
                    //setAnimState()
                }
            }
        }
         ContextRadioButton {
             id: rb_anim_on_begin
            text: "on begin"
            checked: false
            exclusiveGroup: tabPositionGroup
            onCheckedChanged: {
                if (checked)
                {
                    animate_block_wnd.anim_state = 1;
                    //setAnimState()
                }

            }
        }
         ContextRadioButton {

             id: rb_anim_on_end
            text: "on end"
            checked: false
            exclusiveGroup: tabPositionGroup
            onCheckedChanged: {
                if (checked)
                {
                    animate_block_wnd.anim_state = 2;
                   // setAnimState()
                }


            }
        }
         ContextRadioButton {
             id: rb_anim_on_begin_end
            text: "on begin & and"
            checked: false
            exclusiveGroup: tabPositionGroup
            onCheckedChanged: {
                if (checked)
                {
                    animate_block_wnd.anim_state = 3;
                    //setAnimState()

                }
            }
        }
             }
         }
         /*SpinBox {
             id: block_anim_time_value
              property int initValue : animate_block_wnd.anim_time
              y: animate_block_items.height - 1.5 * height
              x:  (animate_block_items.width - width)/2
              value: initValue
              maximumValue: timeControll.getBlockTime(animate_block_wnd.olumnIndex,animate_block_wnd.blockIndex)
              minimumValue: 0
         }*/
         TextField   {
              id: block_anim_time_value
              width: animate_block_wnd.width - 10
              property string initValue : animate_block_wnd.anim_time
              font { pixelSize: 14 }
              y: animate_block_items.height - 1.5 * height
              x:  (animate_block_items.width - width)/2
             text: initValue
             onTextChanged: {
                 if (text > animate_block_wnd.block_time)
                      text = animate_block_wnd.block_time
             }

            // color: text_color

         }
     }
    }

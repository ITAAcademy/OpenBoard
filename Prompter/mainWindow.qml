import QtQuick 2.4
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.2

import "Content" as Content

Rectangle{   
     property  int number_fields_length : 100
    id: root
    width: 300
    height: 400
    //anchors.margins: 25
    border.width: 10
    border.color: "#333333"
    color: "#777777"
    radius: 10
    smooth: true
    MouseAreaForWindowDraging{
            id: framaMA
            anchors.fill:   root
        }

    Column{
        width:parent.width-parent.border.width*2
        height:parent.height-parent.border.width*2
        x: root.border.width
        y:root.border.width

        Button{
            id: btnAdd
            text:'Add'
            onClicked:
            {
                prompterControll.addPrompt(1,1,"button test");
                console.log("button clicked");
            }
        }
ScrollView {

    width:parent.width
    height:parent.height-btnAdd.height;
        ListView {
            spacing: 3
            header:

                Row{
                Rectangle{
                    color: "blue"
                    width:number_fields_length
                    height:50


                    Text{
                        text:"playTime"
                        font.pointSize: 15
                        color: "white"
                    }
                }
                Rectangle{
                    color: "blue"
                    width:number_fields_length
                    height:50
                    Text{
                        text:"lifeTime"
                        font.pointSize: 15
                        color: "white"
                    }
                }
                Rectangle{
                    color: "blue"
                    width:root.width-number_fields_length*2
                    height:50
                    Text{
                        text:"text"
                        font.pointSize: 15
                        color: "white"
                    }
                }
                }


            width:parent.width-root.border.width*2
            height:parent.height
              model: promptsData
              delegate:Rectangle {
                  property int delegateWidth : root.width-root.border.width*2
                  property int delegateSingleElementHeight : 50
                  property int indexOfThisDelegate: index
                  width: delegateWidth; height: childrenRect.height

                  border.width: 1

                  color: "grey"
                  Row{
                      //spacing: 30
                      id: mainRow
                      height:childrenRect.height
                      width:parent.width                     

                      Rectangle{
                          width: textInputStartTime.width
                          height: textInputStartTime.height
                          border.color: "#4b4b4b"
                          border.width:1
                  TextInput{
                      id:textInputStartTime
                      text: startTime
                      width:number_fields_length
                      font.pointSize: 12
                      wrapMode: TextEdit.Wrap
                      maximumLength: 8
                      selectByMouse:true
                      onTextChanged: {
                         prompterControll.setPromptStartTimeAt(indexOfThisDelegate,text.toString())
                      }
                  }
                      }
                      Rectangle{
                          width: textInputLifeTime.width
                          height: textInputLifeTime.height
                          border.width:1

                  TextInput{
                      id:textInputLifeTime
                      text: lifeTime
                       width:number_fields_length
                      font.pointSize: 12
                      wrapMode: TextEdit.Wrap
                       maximumLength: 8
                        selectByMouse:true
                        onTextChanged: {
                           prompterControll.setPromptLifeTimeAt(indexOfThisDelegate,text.toString())
                        }

                  }
                      }
                      Rectangle{
                          width: textInputPromtText.width
                          height: textInputPromtText.height
                          border.width:1
                  TextEdit{
                       id:textInputPromtText
                      text: promptText
                      font.pointSize: 12
                      width:mainRow.width-textInputStartTime.width-textInputLifeTime.width
                      wrapMode: TextEdit.Wrap
                      property int lastCursorPos: 0
                      selectByMouse:true
                        onTextChanged: {
                            if (text.charAt(lastCursorPos)==='\n')
                            {
                                console.log("new line");
                            }
                            lastCursorPos=cursorPosition;
                           prompterControll.setPromptTextAt(indexOfThisDelegate,text.toString())

                        }
                  }
                      }
                  }
              }
          }
    }

    }

}




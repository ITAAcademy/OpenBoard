import QtQuick 2.4
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.2
import QtQuick.Dialogs 1.1

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
    property int newLifeTimeValue : 0
    property int newStartTimeValue : 0
    property string newPromptTextValue : ""

    MouseAreaForWindowDraging{
        id: framaMA
        anchors.fill:   root
    }
    MessageDialog {
        id: messageDialog
        title: "Time error"
        text: "Several prompts can't excist in one time"
        visible:false
        onAccepted: {
            //console.log("And of course you could only agree.")
            //Qt.quit()
            visible=false;
        }
        //Component.onCompleted: visible = true
    }

    Column{
        id: mainColumn
        width:parent.width-parent.border.width*2
        height:parent.height-parent.border.width*2
        x: root.border.width
        y:root.border.width


        ScrollView {
            id:scrollView

            width:parent.width
            height:root.height-root.border.width*2-statusBar.height;

            ListView {

                //property alias btnAdd : btnAdd
                id:listView
                //spacing: 3
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
                Connections {
                    target: prompterControll
                    onBlockTimeChanged: {
                        console.log("block time changed");
                    }
                }

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
                                validator: RegExpValidator {
                                    regExp: /[0-9]+/
                                }
                                onFocusChanged: {
                                    if (focus===true)
                                    {
                                        parent.color="yellow";
                                        return;
                                    }
                                    parent.color="white";
                                    console.log("focus changed");
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
                                validator: RegExpValidator {
                                    regExp: /[0-9]+/
                                }
                                onFocusChanged: {
                                    if (focus===true)
                                    {
                                        parent.color="yellow";
                                        return;
                                    }
                                    parent.color="white";
                                    console.log("focus changed");
                                    prompterControll.setPromptLifeTimeAt(indexOfThisDelegate,text.toString())
                                }

                            }
                        }
                        Rectangle{
                            id:textInputPromtTextRect
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
                                onFocusChanged: {
                                    if (focus===true)
                                    {
                                        parent.color="yellow";
                                        return;
                                    }
                                    parent.color="white";
                                    console.log("focus changed");
                                    lastCursorPos=cursorPosition;
                                    prompterControll.setPromptTextAt(indexOfThisDelegate,text.toString())

                                }
                            }
                        }
                    }
                }
                footer:
                    ///////
                    Column{
                    id:newPromptColumn
                    width:parent.width
                  //  height:parent.height
                    property alias btnAdd : btnAdd
                    function clear(){
                        textInputNewStartTime.text="";
                        textInputNewLifeTime.text="";
                        textInputNewPromtText.text="";
                    }
                    Row{
                        //spacing: 30
                        id: newPromptRow
                        height:childrenRect.height
                        width:parent.width

                        Connections {
                            target: btnAdd
                            onClearNewPromptRow: {
                                newPromptColumn.clear();
                            }
                        }
                        Rectangle{
                            width: textInputNewStartTime.width
                            height: textInputNewStartTime.height
                            border.color: "#4b4b4b"
                            border.width:1
                            TextInput{
                                id:textInputNewStartTime
                                width:number_fields_length
                                font.pointSize: 12
                                wrapMode: TextEdit.Wrap
                                maximumLength: 8
                                selectByMouse:true
                                validator: RegExpValidator {
                                    regExp: /[0-9]+/
                                }
                                onTextChanged: {
                                    newStartTimeValue=1*text;
                                }
                                onFocusChanged: {
                                    if (focus===true)
                                    {
                                        parent.color="yellow";
                                        return;
                                    }
                                    parent.color="white";
                                }
                            }
                        }
                        Rectangle{
                            width: textInputNewLifeTime.width
                            height: textInputNewLifeTime.height
                            border.width:1

                            TextInput{
                                id:textInputNewLifeTime
                                width:number_fields_length
                                font.pointSize: 12
                                wrapMode: TextEdit.Wrap
                                maximumLength: 8
                                selectByMouse:true
                                validator: RegExpValidator {
                                    regExp: /[0-9]+/
                                }
                                onTextChanged: {
                                    newLifeTimeValue=1*text;
                                }
                                onFocusChanged: {
                                    if (focus===true)
                                    {
                                        parent.color="yellow";
                                        return;
                                    }
                                    parent.color="white";
                                }
                            }
                        }
                        Rectangle{
                            width: textInputNewPromtText.width
                            height: textInputNewPromtText.height
                            border.width:1
                            TextEdit{
                                id:textInputNewPromtText
                                font.pointSize: 12
                                width:newPromptRow.width-textInputNewStartTime.width-textInputNewLifeTime.width
                                wrapMode: TextEdit.Wrap
                                property int lastCursorPos: 0
                                selectByMouse:true

                                onTextChanged: {
                                    newPromptTextValue=text;
                                }
                                onFocusChanged: {
                                    if (focus===true)
                                    {
                                        parent.color="yellow";
                                        return;
                                    }
                                    parent.color="white";
                                }
                            }

                        }
                    }
                    Button{
                        id: btnAdd
                        text:'Add'
                        signal clearNewPromptRow();
                        onClicked:
                        {
                        var emptyFieldsExist = (newStartTimeValue.length<1 || newLifeTimeValue.length<1 || newPromptTextValue.length<1);
                        var isValuesCorrect = (newStartTimeValue>=0 && newLifeTimeValue>0);
                            if (emptyFieldsExist || !isValuesCorrect)
                            {
                                statusBar.setStatusText("empty field not allowed");
                                return; //empty fields not allowed;
                            }
                            var operationResult=prompterControll.addPrompt(newStartTimeValue,newLifeTimeValue,newPromptTextValue);
                            if(operationResult===0)
                            {
                            clearNewPromptRow();
                            console.log("prompt added");
                            }
                            else if (operationResult===1)
                                statusBar.setStatusText("Error, time values intersection detected");
                                //messageDialog.setVisible(true);
                        }
                    }
                }
                ///////

            }

        }
        StatusBar{
            id:statusBar
            function setStatusText(val){
                statusText.text=val;
            }

            width:parent.width
            Text{
                id:statusText
                width:parent.width
                text:"test"
            }
        }

    }

}




import QtQuick 2.3
import "boarFunc.js" as JS
Item{
    Rectangle{
        color: "#000000"
        anchors.fill: parent
    }
    MouseArea{
        anchors.fill: parent
        property int mx: -1
        property int my: -1
        id: mouse
        onClicked: {
            console.debug("click");
            JS.brickLastWT();

        }
    }
    Canvas{
        id: mainDrawElm
        objectName: "mcanvas"
        anchors.fill: parent
        antialiasing: true
        renderStrategy: Canvas.Threaded
        renderTarget: Canvas.Image
        property int index: 0
        property int animationIndex: 0
        property int scroll: -1

        property int row: 1
        property int rowMax: 1
        property var listOfObjects : []
        property var indexWords : 0;
        property var indexSTR : 0;
        function bDrawWT( a ){
            //console.debug("drawWT____OK" + a)
            JS.drawWT(a)
            mainDrawElm.markDirty();
        }

        //function drawSymbol(st);
       // Text { text: cFontLoader.status == FontLoader.Ready ? 'Loaded' : 'Not loaded' }
        Timer{
            id: fps
            interval: 1000/60

            onTriggered: {
                mainDrawElm.requestPaint()
            }
            running: true
            repeat: true
            Component.onCompleted: fps.start()

        }

        Connections {
            target: forma
            onDrawTextChanged: console.log("The application data changed!")
        }

        onPaint: {
         //   JS.isLastRow();
            for( var i = 0; i < JS.animateList.length; i++)
                JS.drawAnimationText(JS.animateList[i]);

        }
    }
    Component.onCompleted: {
     //   JS.init();
    }
}

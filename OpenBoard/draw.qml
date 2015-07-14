import QtQuick 2.0
import "boarFunc.js" as JS
Item{
    Rectangle{
        color: "#000000"
        anchors.fill: parent
    }
    Canvas{
        id: mainDrawElm
        objectName: "mcanvas"
        anchors.fill: parent
        antialiasing: true
        renderStrategy: Canvas.Threaded
        renderTarget: Canvas.Image
        property int index: 0
        property bool cross: false
        property bool underline: false
        property var color: "#FFFFFF"
        property int animationIndex: 0
        property int scroll: -1

        property int row: 1
        property int rowMax: 1
        property var listOfObjects : []
        property var indexWords : 0;
        property var indexSTR : 0;
        property int lastHeight: mainDrawElm.height
        property int globalScroll: 0

        function clear(){
            JS.context.clearRect(0,0, mainDrawElm.width,mainDrawElm.height);
            JS.context.lineWidth = 3;
            JS.clear(lastHeight + 200);
            JS.context.translate(0, globalScroll);
            globalScroll = 0;
            // set line color
            JS.context.strokeStyle = '#ff0000';
        }
        function clearRectangle(x,y,width,height){
                    JS.context.clearRect(x,y,width,height);
                }

        function bdrawWrapText( a ){
            //console.debug("drawWrapText____OK" + a)
            JS.drawWrapText(a)
            mainDrawElm.markDirty();
        }
        function fillText( str, x, y )
        {
            //JS.init();
            //initFont()
            //if(JS.context != null)
            var text = str.replace(/(\t)/g, "   "); // I use 4 spaces for tabulation, but you can use anything you want
                JS.context.fillText( text, x, y);
            //console.log("QML__LOG:  " + str);
            /*
            if(mainDrawElm.cross == true)
                    drawCrossText(str, x, y);
                if(mainDrawElm.underline == true)
                    drawUnderLine(str, x, y);
                */
           // mainDrawElm.markDirty();
        }
        function init()
        {
            JS.init();
        }

        function setGradientStyle(x , y, width, height, colorMAS )
        {
            var grd = context.createLinearGradient(x, y, width, height);
            var mas = new Array(colorMAS);
            for( var i = 0; i < mas.length; i++)
                grd.addColorStop(parseFloat(colorMAS[i++]), colorMAS[i]);
            /*grd.addColorStop(0.85, "red");
            grd.addColorStop(1, "rgba(255, 255, 255, 0)");*/
            context.fillStyle = grd;
        }

        function isLastRow(scroll, LPI, y)
        {
            var img = JS.context.getImageData(0, 0, mainDrawElm.width, mainDrawElm.height);
            JS.clear(y);
            lastHeight = y;
            JS.context.translate(0, scroll);
            mainDrawElm.globalScroll += scroll*(-1);
            JS.context.drawImage(img, 0, LPI); // LPI - висота стрічки
        }

        function initFont(pt, font, style, underLine, crossOut)
        {
           // console.debug(pt +  " " + font)
            JS.context.font = style + pt + "pt \"" + font + "\"";// "bold 10pt  \"font_name\" "
            JS.context.kerning = 10;
            mainDrawElm.cross = crossOut;
            mainDrawElm.underline = underLine;
       //     console.debug(mainDrawElm.cross +  " " + mainDrawElm.underline);
        }

        function setColor( col )
        {
            JS.context.fillStyle = col;
            mainDrawElm.color = col;
          //  console.debug("color set" + mainDrawElm.color);
        }

        function drawFigure(x, y, w, h, type, fill, size, color)
        {
            if(type == 0) //line
            {
                JS.context.beginPath();
                JS.context.strokeStyle = color;
                JS.context.lineWidth = size;
                JS.context.moveTo(x, y);
                JS.context.lineTo(w, h);
                JS.context.stroke();
            }
        }
        function drawUnderLine(text, x, y){
          var width = JS.context.measureText(text).width;
          var height = JS.context.measureText(text).height;
          var size =  Math.round(height*1.3);
          size = size + y;
           console.debug("                  height" + height)
          JS.context.beginPath();
          JS.context.strokeStyle = mainDrawElm.color;
          JS.context.lineWidth = Math.round(0.15*height);
          JS.context.moveTo(Math.round(x + 10),y);
          JS.context.lineTo(x+width,y);
          JS.context.stroke();
        }
        function clearSymbol(x){
        //TODO
        }

        function drawCrossText(ctx, text, x, y){
            var width = JS.context.measureText(text).width;
            var size =  JS.context.measureText(text).height/2 +  0.3* JS.context.measureText(text).height;
            size += y;

            JS.context.beginPath();
            JS.context.strokeStyle = mainDrawElm.color;
            JS.context.lineWidth = 0.15* JS.context.measureText(text).height;
            JS.context.moveTo(x - 0.3* JS.context.measureText(text).height,y);
            JS.context.lineTo(x+width,y);
            JS.context.stroke();
        }


        //function drawSymbol(st);
       // Text { text: cFontLoader.status == FontLoader.Ready ? 'Loaded' : 'Not loaded' }
        Timer{
            id: fps
            interval: 1000/120

            onTriggered: {
                mainDrawElm.requestPaint()
            }
            running: true
            repeat: true
            Component.onCompleted: fps.start()

        }

        Connections {
            target: forma
         //   onDrawTextChanged: console.log("The application data changed!")
        }

        onPaint: {
         //   JS.isLastRow();
/*            for( var i = 0; i < JS.animateList.length; i++)
                JS.fillAnimationText(JS.animateList[i]);
                */

        }
    }
    Component.onCompleted: {

    }
}

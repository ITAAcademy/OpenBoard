var context;
var lineHeight = 25;
var marginLeft = 20;
var marginTop = 40;
var maxWidth; //размер поле, где выводится текст
var pt = 36;
var font = "LC Chalk";
var isWord  =  new Boolean(true);
var x = marginLeft,y = lineHeight + pt;
var indexW = 1;
var indexRow = 0;
var listWords = new String(); // вся стрічка
var listStr = []; // номер з якої починається і-та стрічка
listStr[0] = 0;
var indexInLsit = 1;
var brickWT = 0;

var animateList = [];
//animateList[0].text = 5;

function update()
{
    mainDrawElm.markDirty();
}

function setPixel(x, y, r, g, b, a) {
  var context = mainDrawElm.getContext("2d");
  var imagedata = context.getImageData(0, 0, canvas.width, canvas.height);
  var i = (y * imagedata.width + x) * 4;
  imagedata.data[i++] = r;
  imagedata.data[i++] = g;
  imagedata.data[i++] = b;
  imagedata.data[i] = a;
}

function getPixel(imagedata, x, y) {
  var context = mainDrawElm.getContext("2d");
  var imagedata = context.getImageData(0, 0, canvas.width, canvas.height);
  var i = (y * imagedata.width + x) * 4;

  return {r: imagedata.data[i], g: imagedata.data[i+1], b: imagedata.data[i+2], a: imagedata.data[i+3]};
}

function floodFill(x, y, color, borderColor){
    var ctx = mainDrawElm.getContext("2d");
    var imageData = ctx.getImageData(0, 0, 300, 300);
    var width = imageData.width;
    var height = imageData.height;
    var stack = [[x, y]];
    var pixel;
    var point = 0;
    while (stack.length > 0)
    {
        pixel = stack.pop();
        if (pixel[0] < 0 || pixel[0] >= width)
            continue;
        if (pixel[1] < 0 || pixel[1] >= height)
            continue;

        // Alpha
        point = pixel[1] * 4 * width + pixel[0] * 4 + 3;

        // Если это не рамка и ещё не закрасили
        console.debug("color: " + imageData.data[point]);
        if (imageData.data[point] != borderColor && imageData.data[point] != color)
        {
            // Закрашиваем
            imageData.data[point] = color;

            // Ставим соседей в стек на проверку
            stack.push([
                pixel[0] - 1,
                pixel[1]
            ]);
            stack.push([
                pixel[0] + 1,
                pixel[1]
            ]);
            stack.push([
                pixel[0],
                pixel[1] - 1
            ]);
            stack.push([
                pixel[0],
                pixel[1] + 1
            ]);
        }
    }
    ctx.putImageData(imageData, 0, 0);
}

function setCharAt(str,index,chr) {
    if(index > str.length-1) return str;
    return str.substr(0,index) + chr + str.substr(index+1);
}
function drawAnimationText( input/*text, delta, iterator, tx, ty, index*/)
{
    //var iterator = tx;
    var style = context.fillStyle;
    var widht = context.measureText(input.text).width + input.tx;
    //var height = context.measureText(text).height;
    //animationTick.interval = 1000/60;
   // while(iterator < widht)
    {
        var grd = context.createLinearGradient(0, 0, input.iterator, -1);
        input.iterator += input.delta;
        grd.addColorStop(0, "red");
        grd.addColorStop(0.85, "red");
        grd.addColorStop(1, "rgba(255, 255, 255, 0)");
        context.fillStyle = grd;
        context.fillText(input.text, input.tx, input.ty);
    }
    context.fillStyle = style;
    if(input.iterator >= widht)
    {
        animateList.splice(input.index,1);
    }

    //animateList = this;
}

function drawWrapText(context, text, x, y, maxWidth, lineHeight) {
        var words = (text + "  ").split(' ');
        var line = '';
     //   var oneCharW = context.measureText('W').width;
        for(var n = 0; n < mainDrawElm.listOfObjects.length; n++) {
            context.fillText(mainDrawElm.listOfObjects[n], x, y);
            y+= lineHeight;
        }
       /*console.log("L: " + mainDrawElm.listOfObjects.length);
       console.log("W:  " + mainDrawElm.indexWords);
        console.log("W:  " + mainDrawElm.indexSTR);
        console.log("W:  " + mainDrawElm.listOfObjects);*/

        for(var n = mainDrawElm.indexWords; n < words.length - 4; n++) {
          var testLine = line + words[n] + ' ';
          var metrics = context.measureText(testLine);
          var testWidth = metrics.width;
          // animation(text, lineHeight)
          if (testWidth > maxWidth && n > 0) {
              var kus = "";
              var Width = context.measureText(line).width;
              if(Width + 25 >= maxWidth)
              {
                  var t_i;
                  for( t_i = 0; t_i < line.length; t_i++)
                  {
                    if(context.measureText(line.substring(0, t_i)).width > maxWidth - 20)
                        break;
                  }
                  kus = line.substring(--t_i,line.length);
                  line = line.substring(0,t_i) + "-";
                  n--;
                  mainDrawElm.indexWords--;
                  //setCharAt(line,line.length - (Width - maxWidth)/oneCharW + 1,'\0');

              }

              context.fillText(line, x, y);
              mainDrawElm.listOfObjects[mainDrawElm.indexSTR] = line;
              mainDrawElm.indexSTR++;
              if(Width + 25 >= maxWidth)
                line = kus + " ";
              else
                line = words[n] + " ";
                y+= lineHeight;
         }
          else {
            mainDrawElm.indexWords++;
            line = testLine;
          }
        }
       // context.fillText(line, x, y);
      }
function initFont()
{
    context.font = "italic "+ pt + "pt \"" + font + "\"";// "bold 10pt  \"font_name\" "
    context.fillStyle = "#FFFFFF";
}

function init()
{
    context = mainDrawElm.getContext("2d");
    maxWidth = mainDrawElm.width - marginLeft; //размер поле, где выводится текст
    initFont();
}
function isLastRow()
{
    if(y  + mainDrawElm.scroll*indexRow > mainDrawElm.height )
    {
        //context.reset();
        //context.reset();
        var img = context.getImageData(0, 0, mainDrawElm.width, mainDrawElm.height);
        clear();
        /*for(var i = 0; i < indexInLsit; i++)
        {
            var str = listWords.substring(listStr[i],listStr[i+1]);
            //console.debug("i=" + i +" "     "+  index = " + indexInLsit);
            context.fillText(str, x, y);
            y += lineHeight + pt;
        }*/
        //context. putImageData(img, 0, y);
        mainDrawElm.scroll = -(lineHeight + pt);
        context.translate(0, mainDrawElm.scroll);
        context.drawImage(img, 0, (lineHeight + pt)*indexRow);
        //mainDrawElm.scroll = -1;

        indexRow++;
    }
}

function drawWT( WT )
{
    init();
     console.debug(lineHeight + pt  + y  + mainDrawElm.scroll*indexRow);
    var widht = context.measureText(WT).width;
    if(widht + x > maxWidth)
    {
        if(isWord)
        {
            context.fillText("-", x, y);
            listWords += "-";
            listStr[indexInLsit++] = listWords.length;
        }
        y += lineHeight + pt;

        x = marginLeft;
    }
    isLastRow();
    context.fillText(WT, x, y);
    listWords += WT;
    x += widht;
    console.debug("Y:" + y + ":Y");
   // brickLastWT();
    /*mainDrawElm.row = 1;
    if(lineHeight + pt > mainDrawElm.height )
    context.translate(0, mainDrawElm.scroll);*/

    //drawWrapText(context, forma.drawText, marginLeft, marginTop + pt, maxWidth, lineHeight + pt);
}

function clear()
{
    context.clearRect(0,0, mainDrawElm.width, y);
    //y = 0;
}
function addAnimationText(text, delta, iterator, tx, ty)
{
    var temp = Object.create({text: text, delta: delta, iterator: iterator, tx: tx, ty: ty});
    animateList.push(temp);
}

function brickLastWT()
{
    var tWT = listWords.charAt(listWords.length - 1);
    /*context.fillText("/", x - context.measureText(tWT).width, y);
    context.fillText("\\", x - context.measureText(tWT).width, y);*/
    addAnimationText("/", 1, x - context.measureText(tWT).width, y);
    //drawAnimationText("/", 1, x - context.measureText(tWT).width, y)

}

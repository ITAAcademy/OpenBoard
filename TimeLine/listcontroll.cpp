#include "listcontroll.h"


void ListControll::recountMaxTrackTime()
{
    maxTrackTime = 0;
    for (int i=0; i< tracks.size(); i++)
        if (maxTrackTime < tracks[i].time)
            maxTrackTime = tracks[i].time;
}

QString ListControll::getBlockKey(int col, int i) const
{
    return tracks[col].block[i].key;
}

void ListControll::setBlockKey(int col, int i, QString name)
{
    tracks[col].block[i].key = name;
   // test[col][i] = name;
}

void ListControll::removeBlock(int col, int i)
{
    if (tracks[col].block.size() > i)
    {
   // tracks[col].block.removeAt(i);

   if (maxTrackTime == tracks[col].time)
   {
       int temp = tracks[col].block[i].time;
             //  testWidth[col][i];
       tracks[col].block.removeAt(i);
        tracks[col].time -= temp;
   // testColumnWidth[col] -= temp;
    recountMaxTrackTime();

   }
   else
   {
       int temp = tracks[col].block[i].time;
       tracks[col].block.removeAt(i);
        tracks[col].time -= temp;
   }
    }
}

void ListControll::addNewBlock(int col, QString str)
{
    Element temp;
    temp.key = str;
    temp.time = def_min_block_width;
    tracks[col].block.append(Element(str,def_min_block_width));
    tracks[col].time += def_min_block_width;
   // testWidth[col].append(200);
    //testColumnWidth[col]+=200;
  //  qDebug() << "SIZE   " << test.size();
    if (maxTrackTime <  tracks[col].time)
        maxTrackTime =  tracks[col].time;
}


void ListControll::addNewTrack( )
{
    QList <Element>  temp;
        temp.append(Element("1",def_min_block_width));
       temp.append(Element("2",def_min_block_width));
       temp.append(Element("3",def_min_block_width));
       int  temp_traclwidth =   def_min_block_width*temp.size();
       Track trak(temp_traclwidth,temp);
        tracks.append(trak);

   if (maxTrackTime < temp_traclwidth)
       maxTrackTime = temp_traclwidth; //1234
}

bool ListControll::removeLastBlock(int col)
{
    if (tracks[col].block.size())
    {
  // tracks[col].block.pop_back();

   if (maxTrackTime == tracks[col].time)
   {
       int temp = tracks[col].block.last().time;
      tracks[col].block.pop_back();
    tracks[col].time -= temp;
    recountMaxTrackTime();

   }
   else
   {
       int temp = tracks[col].block.last().time;
      tracks[col].block.pop_back();
    tracks[col].time -= temp;
   }
    return true;
    }
    return false;
}

bool ListControll::removeLastTrack()
{
    if (tracks.size())
    {
    int lastColTime = tracks.last().time;
    tracks.pop_back();
    if (maxTrackTime == lastColTime)
        recountMaxTrackTime();
    return true;
    }
    return false;
}

 void ListControll::reverseBlocks(int col, int init_pos, int end_pos)
 {
   Element temp = tracks[col].block[init_pos];
   qDebug() << "1 reverseBlocks:\n" <<  "tracks[col].block[init_pos].time = " << temp.time <<
   "\ntracks[col].block[end_pos].time = " <<  tracks[col].block[end_pos].time;
     //      testWidth[col][init_pos] ;
   tracks[col].block[init_pos] = tracks[col].block[end_pos];
  //   testWidth[col][init_pos] = testWidth[col][end_pos];
     tracks[col].block[end_pos] = temp;

     qDebug() << "2 reverseBlocks:\n" <<
    "tracks[col].block[init_pos].time = " << temp.time <<
     "\ntracks[col].block[end_pos].time = " <<  tracks[col].block[end_pos].time ;
 }

void ListControll::setBlocks(int col,const QList <Element> &value)
{
    tracks[col].block = value;
}

void ListControll::setBlockTime(int col, int i,int value)
{
  //   = value;
    if (maxTrackTime == tracks[col].time)
    {
        tracks[col].time += value - tracks[col].block[i].time  ;
      tracks[col].block[i].time = value;
        if (maxTrackTime < tracks[col].time)
            maxTrackTime = tracks[col].time;
    }
    else
         tracks[col].block[i].time = value;
}

int ListControll::getBlockTime(int col, int i ) const
{
    return tracks[col].block[i].time;
}

Element ListControll::getBlock(int col, int i) const
{
    qDebug() << "getBlock(int col, int i)" << col << " " << i;
     return tracks[col].block[i];
}

int ListControll::getTrackTime( int col) const
{

    return tracks[col].time;
}

int ListControll::getMaxTrackTime( ) const
{
    return maxTrackTime;
}

int ListControll::getTrackSize(int col) const
{
    int temp = tracks[col].block.size();
    return temp;
}


ListControll::ListControll(QObject *parent) : QObject(parent)
{
    maxTrackTime = 0;
   /* QList <QString>  temp;
        temp.append("1");
        temp.append("2");
        temp.append("3");
        temp.append("4");
        temp.append("5");
        temp.append("6");
        test.append(temp);
    QList <int>  temp_int;
        temp_int.append(200);
        temp_int.append(200);
        temp_int.append(200);

        temp_int.append(200);
        temp_int.append(200);
        temp_int.append(200);
        testWidth.append(temp_int);
*/
addNewTrack( );
selectedBlock  = getBlock(0,0);
recountMaxTrackTime();
    if (qgetenv("QT_QUICK_CORE_PROFILE").toInt()) {\
        QSurfaceFormat f = view.format();\
        f.setProfile(QSurfaceFormat::CoreProfile);\
        f.setVersion(4, 4);\
        view.setFormat(f);\
    }\
  //  view.connect(view.engine(), SIGNAL(quit()), &app, SLOT(quit()));
    new QQmlFileSelector(view.engine(), &view);\
    view.engine()->rootContext()->setContextProperty("timeControll", this);
   view.engine()->rootContext()->setContextProperty("viewerWidget", &view);
    view.setSource(QUrl("qrc:/main.qml")); \
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setPersistentOpenGLContext(true);
    view.setColor("transparent");
view.setMinimumHeight(235);
view.setWidth(800);

//view.setMaximumHeight(215);

}

 void ListControll::moveWindow(const int x,const int y)
 {
     QPoint pos = view.position();
    QPoint posMouse = QCursor::pos();
   // view.setPosition(  pos.x() + x , pos.y()  + y);
    view.setPosition( posMouse-prevMousePosition);
   // qApp->processEvents(QEventLoop::AllEvents, 1000);
 }

 void  ListControll::setPrevMousePosition( const int x,const int y)
 {
     prevMousePosition.setX(x);
     prevMousePosition.setY(y);
 }

void ListControll::setSelectedBlock(int col, int i)
{
      selectedBlock = getBlock(col,i);
}

 Element ListControll::getSelectedBlock()
 {
    return selectedBlock;
 }


 void  ListControll::setPrevMousePosition( const QPoint x)
 {
     prevMousePosition = x;
 }

ListControll::~ListControll()
{

}

void ListControll::show()
{
    view.setFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint | Qt::WindowTitleHint);

    if (QGuiApplication::platformName() == QLatin1String("qnx") || \
          QGuiApplication::platformName() == QLatin1String("eglfs")) {\
        view.showFullScreen();\
    } else {\
        view.show();\
    }\
}


 void ListControll::setScalePointerPos( int x)
 {
     scale_pointer_pos = x + 10;
    // qDebug() << "RRRRRRRRRRRRRRR =" << scale_pointer_pos;
 }

 int ListControll::getScalePointerPos( )
 {
     return scale_pointer_pos;
 }

 QList <Element> ListControll::getPointedBlocks( )
 {
     return pointed_block;
 }

 void ListControll::calcPointedBlocks( )
 {
     pointed_block.clear();
     for (int i=0; i<tracks.size(); i++)
     {
         int blockXstart = 0;
         for (int y=0; y<tracks[i].block.size(); y++ )
         {
             int blockXend =blockXstart + tracks[i].block[y].time;
             if (scale_pointer_pos <= blockXend)
             {
                 pointed_block.append(tracks[i].block[y]);
                 //qDebug() << "POP: " << i<< " "<<y;
             break;
             }
              blockXstart = blockXend;
         }
     }
 }

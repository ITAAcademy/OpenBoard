#include "listcontroll.h"

void ListControll::recountMaxColumnWidth()
{
    maxwidth = 0;
    for (int i=0; i< testColumnWidth.size(); i++)
        if (maxwidth < testColumnWidth[i])
            maxwidth = testColumnWidth[i];
}

QString ListControll::getTest(int col, int i) const
{
    return "test[col][i]";
}

void ListControll::addNewTest(int col, QString str)
{
    test[col].append(str);
    testWidth[col].append(200);
    testColumnWidth[col]+=200;
    qDebug() << "SIZE   " << test.size();
    if (maxwidth < testColumnWidth[col])
        maxwidth = testColumnWidth[col];
  /*  int col_width=0;
for (int i=0; i< testWidth[col].size(); i++)
    col_width+=testWidth[col][i];*/
}


void ListControll::addNewColumn( )
{
    QList <QString>  temp;
        temp.append("1");
        temp.append("2");
        temp.append("3");
        test.append(temp);
    QList <int>  temp_int;
        temp_int.append(200);
        temp_int.append(200);
        temp_int.append(200);
        testWidth.append(temp_int);
   testColumnWidth.append(600);
   if (maxwidth < 600)
       maxwidth = 600;
}

bool ListControll::removeLastTest(int col)
{
    if (test[col].size())
    {
   test[col].pop_back();

   if (maxwidth == testColumnWidth[col])
   {
       int temp = testWidth[col].last();
       testWidth[col].pop_back();
    testColumnWidth[col] -= temp;
    recountMaxColumnWidth();

   }
   else
   {
       int temp = testWidth[col].last();
       testColumnWidth[col] -= temp;
       testWidth[col].pop_back();
   }
    qDebug() << "SIZE   " << test[col].size();
    return true;
    }
    return false;
}

bool ListControll::removeLastColumn()
{
    if (test.size())
    {
    test.pop_back();
    testWidth.pop_back();
    int lastColWidth = testColumnWidth.last();
    testColumnWidth.pop_back();
    if (maxwidth == lastColWidth)
        recountMaxColumnWidth();
    qDebug() << "SIZE   " << test.size();
    return true;
    }
    return false;
}

 void ListControll::reverseTests(int col, int init_pos, int end_pos)
 {
   int temp =  testWidth[col][init_pos] ;
     testWidth[col][init_pos] = testWidth[col][end_pos];
     testWidth[col][end_pos] = temp;

    QString temp2 =  test[col][init_pos] ;
         test[col][init_pos] = test[col][end_pos];
         test[col][end_pos] = temp2;

 }

void ListControll::setTest(int col,const QList<QString> &value)
{
    test[col] = value;
}

void ListControll::setTestWidth(int col, int i,int value)
{
  //   = value;
    if (maxwidth == testColumnWidth[col])
    {
        testColumnWidth[col] += value - testWidth[col][i]  ;
       testWidth[col][i] = value;
        if (maxwidth < testColumnWidth[col])
            maxwidth = testColumnWidth[col];
    }
    else
         testWidth[col][i] = value;
}

int ListControll::getTestWidth(int col, int i ) const
{
    return testWidth[col][i];
}

int ListControll::getColumnWidth( int col) const
{

    return testColumnWidth[col];
}

int ListControll::getMaxTestWidth( ) const
{
    qDebug() << "maxwidth = " << maxwidth;
    return maxwidth;
}


ListControll::ListControll(QObject *parent) : QObject(parent)
{
    maxwidth = 0;
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
addNewColumn( );
recountMaxColumnWidth();
    if (qgetenv("QT_QUICK_CORE_PROFILE").toInt()) {\
        QSurfaceFormat f = view.format();\
        f.setProfile(QSurfaceFormat::CoreProfile);\
        f.setVersion(4, 4);\
        view.setFormat(f);\
    }\
  //  view.connect(view.engine(), SIGNAL(quit()), &app, SLOT(quit()));
    new QQmlFileSelector(view.engine(), &view);\
    view.engine()->rootContext()->setContextProperty("timeControll", this);
    view.setSource(QUrl("qrc:///main.qml")); \
    view.setResizeMode(QQuickView::SizeRootObjectToView);
view.setMinimumHeight(415);
view.setWidth(800);
//view.setMaximumHeight(215);

}

ListControll::~ListControll()
{

}

void ListControll::show()
{

    if (QGuiApplication::platformName() == QLatin1String("qnx") || \
          QGuiApplication::platformName() == QLatin1String("eglfs")) {\
        view.showFullScreen();\
    } else {\
        view.show();\
    }\
}

int ListControll::getColumnSize(int col) const
{
    int temp = test[col].size();
    qDebug() << "TEMP" << temp;
    return temp;
}


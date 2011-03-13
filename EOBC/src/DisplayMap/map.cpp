#include "map.h"

Map::Map(QWidget *parent) :
    QMainWindow(parent)
{

    setWindowTitle(tr("EOBC"));
    //this->vec = new MapVectors();

    //this->butt = new QPushButton("Save");
    //this->buttOpen = new QPushButton("Open");
    this->mapLayout = new QLabel();

    mapLayout->setGeometry(0,0,1000,800);
    resize(500,500);
    //QLayout* q = layout();
    setCentralWidget(mapLayout);
    mapLayout->setLayout(new QFormLayout());
    loadAreas();
    /*layout()->addWidget(butt);
    layout()->addWidget(buttOpen);
    butt->setGeometry(500,500,100,30);
    buttOpen->setGeometry(500,550,100,30);
    //this->setCentralWidget(mapLayout);
    connect(butt,SIGNAL(clicked()),this,SLOT(clickSave()));
    connect(buttOpen,SIGNAL(clicked()),this,SLOT(clickOpen()));*/

}
Map::~Map()
{
    QVector<MapArea*>::iterator iter = areas.begin();
    while(iter != areas.end())
    {
        delete *iter;
        iter++;
    }

    //delete vec;
    delete mapLayout;

}

void Map::loadAreas()
{
    QLayout* q = layout();

    areas.push_back(new MapArea(loadFile(":/mapFiles/bin/PurpleArea.txt"), QColor::fromRgb(255,0,255)));
    q->addWidget(areas.last()->getVec());
    //q->addRow();
   //connect(butt,SIGNAL(clicked()),this,SLOT(clickSave()));
    //connect(buttOpen,SIGNAL(clicked()),this,SLOT(clickOpen()));


    areas.push_back(new MapArea(loadFile(":/mapFiles/bin/GreenArea.txt"), Qt::green));
     q->addWidget(areas.last()->getVec());

     //qDebug()<<QTime::currentTime().toString("s:z");
     areas.push_back(new MapArea(loadFile(":/mapFiles/bin/BlueArea.txt"),Qt::blue));
     q->addWidget(areas.last()->getVec());

     //qDebug()<<QTime::currentTime().toString("s:z");
     areas.push_back(new MapArea(loadFile(":/mapFiles/bin/RedArea.txt"),Qt::red));
     q->addWidget(areas.last()->getVec());

     //qDebug()<<QTime::currentTime().toString("s:z");
     areas.push_back(new MapArea(loadFile(":/mapFiles/bin/otherGreenArea.txt"),Qt::green));
     q->addWidget(areas.last()->getVec());

     //qDebug()<<QTime::currentTime().toString("s:z");
     areas.push_back(new MapArea(loadFile(":/mapFiles/bin/YellowArea.txt"),Qt::yellow));
     q->addWidget(areas.last()->getVec());

     //qDebug()<<QTime::currentTime().toString("s:z");
     areas.push_back(new MapArea(loadFile(":/mapFiles/bin/LightBlueArea.txt"),QColor::fromRgb(100,100,255)));
     q->addWidget(areas.last()->getVec());

     //qDebug()<<QTime::currentTime().toString("s:z");
    //vec->setVectors(points);
}
QVector<QPoint>* Map::loadFile(QString fname)
{
    QVector<QPoint>* points = new QVector<QPoint>();
    QFile file(fname);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);


    QString data = in.readLine(20);

    while (data != "")
    {

        char curChar = ' ';
        int index = 0, x = -1,y = -1;
        QString curWord;
        while(curChar != ')')
        {

            curChar = data[index].toAscii();
            if(curChar >= 48 && curChar <=48+10)
                curWord += data[index];
            if(curChar == ',')
            {
                x = curWord.toInt();
                curWord = "";
            }

            if(curChar == ')')
            {
                y = curWord.toInt();
            }
            index ++;
        }
        points->push_back(QPoint(x,y));
        //data = data.chop();
        data= in.readLine(20);

         // qDebug()<< "yay!";
    }

    // optional, as QFile destructor will already do it:
    file.close();
    return points;

}


#include "map.h"

Map::Map(QWidget *parent) :
    QMainWindow(parent)
{

    setWindowTitle(tr("EOBC"));
    this->mapLayout = new QLabel();
    mapLayout->setGeometry(0,0,1000,800);


    fileMenu = menuBar()->addMenu("&File");

    editAct = new QAction(tr("&Edit"),this);
    fileMenu->addAction(editAct);
    //
    //QLayout* q = layout();
    setCentralWidget(mapLayout);
    //mapLayout->setLayout(new QFormLayout());
    loadAreas();

}
Map::~Map()
{
    delete area;

}

void Map::loadAreas()
{
    //mapLayout->setLayout(new QBoxLayout(QBoxLayout::LeftToRight));
    mapLayout->setLayout(new QGridLayout());
    QGridLayout* q = dynamic_cast<QGridLayout*>(mapLayout->layout());

    MapArea* tempArea = new MapArea();
    q->addWidget(tempArea,0,0);
    q->setColumnStretch(0,720);
    q->setRowMinimumHeight(0,800);
    QPushButton* bstuff = new QPushButton("ok");
    q->addWidget(bstuff,0,1);
    q->setMargin(0);
    QPoint middle(tempArea->width()/2,tempArea->height()/2);
    MapArea::setMiddle(middle);
    tempArea->addVecs(loadFile(":/mapFiles/bin/PurpleArea.txt"),QColor::fromRgb(255,0,255));
    tempArea->addVecs(loadFile(":/mapFiles/bin/GreenArea.txt"), Qt::green);
    tempArea->addVecs(loadFile(":/mapFiles/bin/BlueArea.txt"),Qt::blue);
    tempArea->addVecs(loadFile(":/mapFiles/bin/RedArea.txt"),Qt::red);
    tempArea->addVecs(loadFile(":/mapFiles/bin/otherGreenArea.txt"),Qt::green);
    tempArea->addVecs(loadFile(":/mapFiles/bin/YellowArea.txt"),Qt::yellow);
    tempArea->addVecs(loadFile(":/mapFiles/bin/LightBlueArea.txt"),QColor::fromRgb(100,100,255));

    /*
    tempArea->addVecs(loadFile(":/mapFiles/bin/area2.txt"), Qt::green);
    tempArea->addVecs(loadFile(":/mapFiles/bin/area3.txt"),Qt::blue);
    tempArea->addVecs(loadFile(":/mapFiles/bin/area4.txt"),Qt::red);
    tempArea->addVecs(loadFile(":/mapFiles/bin/area5.txt"),Qt::green);
    tempArea->addVecs(loadFile(":/mapFiles/bin/area6.txt"),Qt::yellow);
    tempArea->addVecs(loadFile(":/mapFiles/bin/area7.txt"), Qt::green);
    tempArea->addVecs(loadFile(":/mapFiles/bin/area8.txt"),Qt::blue);
    tempArea->addVecs(loadFile(":/mapFiles/bin/area9.txt"),Qt::red);
    tempArea->addVecs(loadFile(":/mapFiles/bin/area10.txt"),Qt::green);
    tempArea->addVecs(loadFile(":/mapFiles/bin/area11.txt"),Qt::yellow);
    tempArea->addVecs(loadFile(":/mapFiles/bin/area12.txt"),QColor::fromRgb(100,100,255));
    tempArea->addVecs(loadFile(":/mapFiles/bin/area13.txt"),QColor::fromRgb(100,100,255));
    tempArea->addVecs(loadFile(":/mapFiles/bin/area14.txt"),QColor::fromRgb(255,0,255));*/
    area = tempArea;
    middle = QPoint(tempArea->geometry().width()/2,tempArea->geometry().height()/2);
    MapArea::setMiddle(middle);





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
void Map::resizeEvent(QResizeEvent *event)
{
    int x =area->geometry().width()/2;
    int y =area->geometry().height()/2;
    QPoint middle(x, y);
    area->setMiddle(middle);
}


#include "map.h"
#define RIGHTCOLUMNWIDTH 80
#define TOPMENUHEIGHT 10
enum {FACILITYSTAFF,LHINSTAFF,ADMINISTRATOR};
/** The constructor for Map, sets up the menu bar and calls multiple helper functions
  * to set up more functionality
  * @param parent just passed to the QMainWindow constructor
  */
Map::Map(QWidget *parent) :
    QMainWindow(parent)
{

    setWindowTitle(tr("EOBC"));
    this->mapLayout = new QLabel();

    fileMenu = menuBar()->addMenu("&File");
    addMenu = menuBar()->addMenu("&Add");
    updateMenu = menuBar()->addMenu("&Update");
    reportsMenu = menuBar()->addMenu("&Reports");
    menuBar()->addMenu("&Help");

    editAct = new QAction(tr("&Edit"),this);
    fileMenu->addAction(editAct);
    actions.push_back(new QAction("&Beds",this));
    addMenu->addAction(actions.at(actions.count()-1));
    actions.push_back(new QAction("&Facilities",this));
    addMenu->addAction(actions.at(actions.count()-1));
    actions.push_back(new QAction("&User Accounts",this));
    addMenu->addAction(actions.at(actions.count()-1));

    actions.push_back(new QAction("&Move Patients",this));
    updateMenu->addAction(actions.at(actions.count()-1));
    actions.push_back(new QAction("&Update Waiting List",this));
    updateMenu->addAction(actions.at(actions.count()-1));

    actions.push_back(new QAction("&Submit Report",this));
    reportsMenu->addAction(actions.at(actions.count()-1));
    actions.push_back(new QAction("&View Report",this));
    reportsMenu->addAction(actions.at(actions.count()-1));
    for(int i=0;i<actions.size();i++)
    {
        actions.at(i)->setEnabled(false);
    }
    //
    //QLayout* q = layout();
    setCentralWidget(mapLayout);
    //mapLayout->setLayout(new QFormLayout());
    loadAreas();
    setGeometry(Convenience::getCenterForSize(1000,650));

}

 /** Destructor for map, does nothing since the layout manager deletes all memory
   *
   */
Map::~Map()
{
    //delete area;

}
 /** loadAreas sets up the layout for the form.
   * Loads in the text on the right column, and the map polygons for the right column
   *
   */
void Map::loadAreas()
{
    //mapLayout->setLayout(new QBoxLayout(QBoxLayout::LeftToRight));
    mapLayout->setLayout(new QGridLayout());
    QGridLayout* q = dynamic_cast<QGridLayout*>(mapLayout->layout());

    MapArea* tempArea = new MapArea();
    q->addWidget(tempArea,0,0,6,0);


    // LOAD SIDE BAR //
    // LOAD SIDE BAR //
    // LOAD SIDE BAR //
    q->setColumnStretch(0,8010);
    q->setColumnMinimumWidth(0,10000);
    q->setColumnStretch(1,0);
    q->setColumnMinimumWidth(1,150);
    q->setMargin(0);

    QLabel* fTemp = new QLabel("Facility Name");
    fTemp->setFont(QFont("Arial",14,3));
    q->addWidget(fTemp,0,1);
    fName = new QLabel();
    q->addWidget(fName,1,1);
    fTemp = new QLabel("Facility Area");
    fTemp->setFont(QFont("Arial",14,3));
    q->addWidget(fTemp,2,1);
    fArea = new QLabel();
    q->addWidget(fArea,3,1);
    fTemp = new QLabel();
    q->addWidget(fTemp,4,1);
    fTemp = new QLabel("Occupancy Rates");
    fTemp->setFont(QFont("Arial",14,3));
    q->addWidget(fTemp,5,1);
    fLTCRates = new QLabel();
    q->addWidget(fLTCRates,6,1);
    fCCCRates = new QLabel();
    q->addWidget(fCCCRates,7,1);
    fACRates = new QLabel();
    q->addWidget(fACRates,8,1);
    fTemp = new QLabel();
    q->addWidget(fTemp,9,1);
    fTemp = new QLabel("Coordinates");
    fTemp->setFont(QFont("Arial",14,3));
    q->addWidget(fTemp,10,1);
    fCoord = new QLabel();
    q->addWidget(fCoord,11,1);
    fTemp = new QLabel("Waiting List");
    fTemp->setFont(QFont("Arial",14,3));
    q->addWidget(fTemp,12,1);
    fWList = new QLabel();
    q->addWidget(fWList,13,1);
    for(int i=1;i<14;i++)
    {
        q->setRowMinimumHeight(i,20);
        q->setRowStretch(i,100);
    }
    q->setRowMinimumHeight(4,100);
    //q->setRowMinimumHeight(10,100);
    q->setRowStretch(0,50);
     q->setRowStretch(1,10);
     q->setRowStretch(5,0);
     q->setRowStretch(4,0);
    q->setRowStretch(6,0);
    q->setRowStretch(7,0);
    q->setRowStretch(8,0);
    q->setRowStretch(9,1);
    q->setRowMinimumHeight(9,100);
    q->setRowStretch(10,0);
    //
    //
    QVector<QLabel*> labels;
    labels.push_back(fName);
    labels.push_back(fArea);
    labels.push_back(fLTCRates);
    labels.push_back(fCCCRates);
    labels.push_back(fACRates);
    labels.push_back(fCoord);
    labels.push_back(fWList);
    tempArea->loadLabels(labels);
    //
    //
    // LOAD AREAS //
    // LOAD AREAS //
    // LOAD AREAS //
    QPoint middle(tempArea->width()/2,tempArea->height()/2);
    MapArea::setMiddle(middle);
    tempArea->addVecs(loadFile(":/mapFiles/resources/PurpleArea.txt"),QColor::fromRgb(255,0,255));
    tempArea->addVecs(loadFile(":/mapFiles/resources/GreenArea.txt"), Qt::green);
    tempArea->addVecs(loadFile(":/mapFiles/resources/BlueArea.txt"),Qt::blue);
    tempArea->addVecs(loadFile(":/mapFiles/resources/RedArea.txt"),Qt::red);
    tempArea->addVecs(loadFile(":/mapFiles/resources/otherGreenArea.txt"),Qt::green);
    tempArea->addVecs(loadFile(":/mapFiles/resources/YellowArea.txt"),Qt::yellow);
    tempArea->addVecs(loadFile(":/mapFiles/resources/LightBlueArea.txt"),QColor::fromRgb(100,100,255));

    /*
    tempArea->addVecs(loadFile(":/mapFiles/resources/area2.txt"), Qt::green);
    tempArea->addVecs(loadFile(":/mapFiles/resources/area3.txt"),Qt::blue);
    tempArea->addVecs(loadFile(":/mapFiles/resources/area4.txt"),Qt::red);
    tempArea->addVecs(loadFile(":/mapFiles/resources/area5.txt"),Qt::green);
    tempArea->addVecs(loadFile(":/mapFiles/resources/area6.txt"),Qt::yellow);
    tempArea->addVecs(loadFile(":/mapFiles/resources/area7.txt"), Qt::green);
    tempArea->addVecs(loadFile(":/mapFiles/resources/area8.txt"),Qt::blue);
    tempArea->addVecs(loadFile(":/mapFiles/resources/area9.txt"),Qt::red);
    tempArea->addVecs(loadFile(":/mapFiles/resources/area10.txt"),Qt::green);
    tempArea->addVecs(loadFile(":/mapFiles/resources/area11.txt"),Qt::yellow);
    tempArea->addVecs(loadFile(":/mapFiles/resources/area12.txt"),QColor::fromRgb(100,100,255));
    tempArea->addVecs(loadFile(":/mapFiles/resources/area13.txt"),QColor::fromRgb(100,100,255));
    tempArea->addVecs(loadFile(":/mapFiles/resources/area14.txt"),QColor::fromRgb(255,0,255));*/
    area = tempArea;
    middle = QPoint(tempArea->geometry().width()/2,tempArea->geometry().height()/2);
    MapArea::setMiddle(middle);

}
 /** loadFile uses QTextStream to read data files for the map
   * each file contains points that are loaded into polygons to make up the map
   * @param fname contains the name of the file to read
   * @return a vector of all the points that make up the polygon
    */
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
        data= in.readLine(20);
    }

    // optional, as QFile destructor will already do it:
    file.close();
    return points;

}
 /** resizeEvent is a slot that is called when the window is resized
   * The areas resize even is also called when the window is resized
   * along with the middle recalculated
   */
void Map::resizeEvent(QResizeEvent *)
{
    int x =geometry().width()/2 - RIGHTCOLUMNWIDTH;
    int y =geometry().height()/2 - TOPMENUHEIGHT;
    QPoint middle(x, y);
    area->setMiddle(middle);
}
/**
  * @todo fix permissions so that not everything is enabled all the time.
  * delete highlited code below
  */
void Map::setPermissions(int permissions)
{
    this->editAct->setEnabled(true);
    if(permissions >= FACILITYSTAFF)
    {
        actions.at(0)->setEnabled(true);
        actions.at(3)->setEnabled(true);
        actions.at(4)->setEnabled(true);
    }
    if(permissions >= LHINSTAFF)
    {
        actions.at(5)->setEnabled(true);
        actions.at(6)->setEnabled(true);
    }
    if(permissions == ADMINISTRATOR)
    {
        actions.at(1)->setEnabled(true);
        actions.at(2)->setEnabled(true);
    }


    /* FOR TESTING ONLY, DELETE FOR FINAL RELEASE */
    /* FOR TESTING ONLY, DELETE FOR FINAL RELEASE */
    for(int i=0;i<actions.size();i++)
    {
        actions.at(i)->setEnabled(true);
    }
    /* FOR TESTING ONLY, DELETE FOR FINAL RELEASE */
    /* FOR TESTING ONLY, DELETE FOR FINAL RELEASE */
}


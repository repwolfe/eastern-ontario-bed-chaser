#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    setWindowTitle("LHIN EOBC");

    loadImage(":/Champlain.jpg",QRect(-0,-0,800,525),ui->mapBox);
    DrawFacilities();
    connect(ui->logOffButton,SIGNAL(clicked()),this,SLOT(logOff()));
    connect(ui->actionOccupancy_Rates,SIGNAL(triggered()),this,SLOT(updateBeds()));
    connect(ui->updateWaitingListButton,SIGNAL(clicked()),this,SLOT(updateWaitingList()));
    connect(ui->generateReportButton,SIGNAL(clicked()),this,SLOT(generateReport()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::loadImage(const QString &fileName,QRect size,
                              QLabel *box)
{
    QImage image;
    image.load(fileName);
    QImage fixedImage(1000,1000, QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&fixedImage);
    int offsetx = 150, offsety = 175;
    painter.fillRect(QRect(size.x(),size.y(),1000,1000), Qt::white);
    painter.drawImage(size,image,QRect(offsetx,offsety+200,image.width()-offsetx,image.height()-offsety-200));
    painter.drawLine(QPoint(0,525),QPoint(800,525));
    painter.drawLine(QPoint(800,0),QPoint(800,525));
    painter.end();

    box->setPixmap(QPixmap::fromImage(fixedImage));

}
void MainWindow::DrawFacilities()
{
    QImage image;
    QLayout* l = layout();
    for(int i=0;i<4;i++)
    {
        QLabel* p = new QLabel("",this);
        int radius;
        if(i%4 <4)
        {
            image.load(":/H3.png");
            radius = 75;
        }
        else
        {
            image.load(":/H2.png");
            radius = 50;
        }
        image = image.scaledToHeight(radius);
        image = image.scaledToWidth(radius);
        p->setGeometry(rand()%650+80,250+rand()%200,radius,radius);
        p->setPixmap(QPixmap::fromImage(image));
        l->addWidget(p);
    }

    for(int i=0;i<5;i++)
    {
        QLabel* p = new QLabel("",this);
        int radius;
        if(i%4 < 4)
        {
            image.load(":/N3.png");
            radius = 75;
        }
        else
        {
            image.load(":/N2.png");
            radius = 50;
        }

        image = image.scaledToHeight(radius);
        image = image.scaledToWidth(radius);
        p->setGeometry(rand()%650+80,250+rand()%200,radius,radius);
        p->setPixmap(QPixmap::fromImage(image));
        l->addWidget(p);
    }
    image.load(":/HSelected.png");
    QLabel* p = new QLabel("",this);
    p->setGeometry(rand()%650 + 80,250+rand()%200,50,50);
    p->setPixmap(QPixmap::fromImage(image));
    l->addWidget(p);
    p = new QLabel("",this);
    p->setGeometry(800,25,50,50);
    p->setPixmap(QPixmap::fromImage(image));
    l->addWidget(p);

    image.load(":/H.png");
    p = new QLabel("",this);
    p->setGeometry(rand()%650+80,250+rand()%200,75,75);
    p->setPixmap(QPixmap::fromImage(image));
    l->addWidget(p);

    this->setLayout(l);//Set the new layout
}
void MainWindow::logOff()
{
    this->close();
}
void MainWindow::updateBeds()
{
    this->bedWind.show();
}
void MainWindow::updateWaitingList()
{
    this->waitWind.show();
}
void MainWindow::generateReport()
{
    this->genWind.show();
}

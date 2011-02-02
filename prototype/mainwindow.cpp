#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    setWindowTitle("LHIN EOBC");

    loadImage(":/map.png",QRect(-0,-0,800,550),ui->mapBox);
    DrawFacilities();
    connect(ui->logOffButton,SIGNAL(clicked()),this,SLOT(logOff()));
    connect(ui->updateBedsButton,SIGNAL(clicked()),this,SLOT(updateBeds()));
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
    int offsetx = 150, offsety = 150;
    painter.fillRect(QRect(size.x(),size.y(),1000,1000), Qt::white);
    painter.drawImage(size,image,QRect(offsetx,offsety,image.width()-offsetx,image.height()-offsety));
    painter.drawLine(QPoint(0,550),QPoint(800,550));
    painter.end();

    box->setPixmap(QPixmap::fromImage(fixedImage));

}
void MainWindow::DrawFacilities()
{
    QImage image;
    image.load(":/H2.png");
    QLayout* l = layout();
    for(int i=0;i<9;i++)
    {
        QLabel* p = new QLabel("",this);
        p->setGeometry(rand()%750,170+rand()%100,50,50);
        p->setPixmap(QPixmap::fromImage(image));
        l->addWidget(p);
    }
     image.load(":/N2.png");
    for(int i=0;i<9;i++)
    {
        QLabel* p = new QLabel("",this);
        image = image.scaledToHeight(30);
        image = image.scaledToWidth(30);
        p->setGeometry(rand()%750,170+rand()%100,30,30);
        p->setPixmap(QPixmap::fromImage(image));
        l->addWidget(p);
    }
    image.load(":/HSelected.png");
    QLabel* p = new QLabel("",this);
    p->setGeometry(rand()%700,170+rand()%100,50,50);
    p->setPixmap(QPixmap::fromImage(image));
    l->addWidget(p);
    p = new QLabel("",this);
    p->setGeometry(800,25,50,50);
    p->setPixmap(QPixmap::fromImage(image));
    l->addWidget(p);

    image.load(":/H.png");
    p = new QLabel("",this);
    p->setGeometry(rand()%700,170+rand()%100,50,50);
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

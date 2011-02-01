#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //img.load(":/map.png");
    //ui->mapBox->setPixmap(QPixmap::fromImage(QImage(":/map.png")));//fromImage(img));\
   // ui->mapBox->setGeometry(0,0,1000,1000);

    QRect j = ui->mapBox->geometry();

    loadImage(":/map.png",QRect(0,-0,1200,1000),ui->mapBox);
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
    QImage fixedImage(size.width(),size.height(), QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&fixedImage);
    painter.fillRect(QRect(size.x(),size.y(),1000,1000), Qt::white);
    painter.drawImage(size,image);
    painter.end();

    box->setPixmap(QPixmap::fromImage(fixedImage));

}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QPainter>
#include <QWidget>
//#include <gui.h>
#include <updatebeds.h>
#include <updatewaitinglist.h>
#include <generatereport.h>
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void logOff();
    void updateBeds();
    void updateWaitingList();
    void generateReport();

private:
    Ui::MainWindow *ui;
    void loadImage(const QString &fileName, QRect size,
                                  QLabel *button);
    void DrawFacilities();
    UpdateBeds bedWind;
    UpdateWaitingList waitWind;
    GenerateReport genWind;
};

#endif // MAINWINDOW_H

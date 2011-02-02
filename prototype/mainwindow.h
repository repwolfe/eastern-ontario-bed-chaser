#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QPainter>
#include <QWidget>
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void loadImage(const QString &fileName, QRect size,
                                  QLabel *button);
    void DrawFacilities();
};

#endif // MAINWINDOW_H

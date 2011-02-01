#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include <mainwindow.h>
#include <QtGui>
#include <QPainter>
#include <QWidget>
namespace Ui {
    class Gui;
}

class Gui : public QMainWindow
{
    Q_OBJECT

public:
    explicit Gui(QWidget *parent = 0);
    ~Gui();

private slots:
    void logInButton();

private:
    Ui::Gui *ui;
    void loadImage(const QString &fileName, QImage *image, QLabel *button);
    void recalculateResult(QImage* img);
    MainWindow wind;

};

#endif // GUI_H

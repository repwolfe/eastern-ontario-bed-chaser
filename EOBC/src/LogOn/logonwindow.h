#ifndef LOGONWINDOW_H
#define LOGONWINDOW_H

#include <QMainWindow>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>
#include <QtGui/QPainter>
class LogOnWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit LogOnWindow(QWidget *parent = 0);

signals:

public slots:
private:
    QLabel* backgroundPic;

};

#endif // LOGONWINDOW_H

#ifndef LOGONWINDOW_H
#define LOGONWINDOW_H

#include <QMainWindow>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>
#include <QtGui/QPainter>
#include <QtGui/QLineEdit>
#include <QtGui/QGridLayout>
#include <QKeyEvent>
#include <QFile>
#include <QTextStream>
class LogOnWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit LogOnWindow(QWidget *parent = 0);

signals:

protected:
    void keyPressEvent(QKeyEvent *event);
public slots:
    void logIn();
private:
    QLabel* backgroundPic;
    QPushButton* logInButton;
    QPushButton* cancelButton;
    QLineEdit* usrBox;
    QLineEdit* passBox;
    void loadBackground();
    void loadLayout();
};

#endif // LOGONWINDOW_H
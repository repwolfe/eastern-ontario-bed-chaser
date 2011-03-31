#ifndef MAP_H
#define MAP_H

#include <QMainWindow>

#include <QtGui>
#include <QPainter>
#include <QWidget>
#include <QMouseEvent>
#include "mapvectors.h"
#include <QtGui/QPushButton>
#include "maparea.h"
#include "convenience.h"
class Map : public QMainWindow
{
    Q_OBJECT
public:
    Map(QWidget *parent = 0);
    void setPermissions(int permissions);
    ~Map();
    void startTimer();

signals:
    void pressedAddBeds();
    void pressedAddFacilities();
    void pressedAddUserAccts();
    void pressedMovePatients();
    void pressedAddPatients();
    void pressedGenerateReport();
    void pressedViewAllReports();
    void pressedUpdateWaitingList();
public slots:
    void pressedExitSlot();
    void pressedAddBedsSlot();
    void pressedAddFacilitiesSlot();
    void pressedAddUserAcctsSlot();
    void pressedMovePatientsSlot();
    void pressedAddPatientsSlot();
    void pressedGenerateReportSlot();
    void pressedViewAllReportsSlot();
    void pressedUpdateWaitingListSlot();

protected:
    void resizeEvent(QResizeEvent *);
private:
    QVector<QPoint>* loadFile(QString fname);
    void loadAreas();
    void connectActions();

private:
        QMenu* fileMenu;
        QMenu* addMenu;
        QMenu* updateMenu;
        QMenu* reportsMenu;
        QAction* editAct;
        QLabel* mapLayout;
        QLabel* fName;
        QLabel* fArea;
        QLabel* fLTCRates;
        QLabel* fACRates;
        QLabel* fCCCRates;
        QLabel* fWList;
        QLabel* fCoord;
        QVector<QAction*> actions;
        MapArea* area;


};

#endif // MAP_H

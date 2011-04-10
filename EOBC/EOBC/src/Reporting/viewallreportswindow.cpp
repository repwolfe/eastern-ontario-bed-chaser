#include "viewallreportswindow.h"

 /** The constructor for ViewAllReportsWindow.
   * initializes add buttons and widgets for the window, and connects the slots for the buttons
   * @param parent just passed to the QWidget constructor
   */


ViewAllReportsWindow::ViewAllReportsWindow(QWidget *parent) :
    QWidget(parent)
{
    setWindowTitle("All Reports Recieved");
    QGridLayout* layout = new QGridLayout();
    layout->addWidget(new QLabel("Reports"),0,0);
    layout->addWidget(new QLabel(),0,1);
    reportsBox = new QListWidget();

    layout->addWidget(reportsBox,1,0,1,0);
    QPushButton* select = new QPushButton("Select");
    layout->addWidget(select,2,0);
    connect(select,SIGNAL(pressed()),this,SLOT(pressedSelectSlot()));

    QPushButton* cancel = new QPushButton("Cancel");
    layout->addWidget(cancel,3,0);
    connect(cancel,SIGNAL(clicked()),this,SLOT(close()));
    setLayout(layout);
    layout->setContentsMargins(30,10,30,10);
    setGeometry(Convenience::getCenterForSize(400,350));

}

  /** the pressedSelectSlot is the slot thats called when the select button has been pressed
    * emits a signal to ReportingControl that tells the current row selected.
    */
void ViewAllReportsWindow::pressedSelectSlot()
{
    emit pressedSelect(reportsBox->currentIndex().row());
}
void ViewAllReportsWindow::addItem(Report* r)
{
    reportsBox->addItem("Report: "+ r->getDate());
}
void ViewAllReportsWindow::pressedCancelSlot()
{
    close();
}



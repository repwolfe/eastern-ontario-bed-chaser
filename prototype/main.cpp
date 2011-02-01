#include <QtGui/QApplication>
#include "gui.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(Resourcepics);
    QApplication a(argc, argv);
    Gui w;
    w.setWindowTitle("LHIN EOBC");

    w.show();

    return a.exec();
}

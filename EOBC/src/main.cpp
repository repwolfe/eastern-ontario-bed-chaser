#include <QtGui/QApplication>
#include "DisplayMap/displaymapcontrol.h"
#include "LogOn/logoncontrol.h"
#include "Model/area.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DisplayMapControl mapControl;
    mapControl.run();
    LogOnControl logControl;
    logControl.run();

    /***************** Testing Model ****************/
 /* TEMPORARY: REMOVING IT SOON -Robbie
    QMap<ID,Area*> areas;
    for (int i = 0; i < 5; ++i)
    {
	areas.insert(i, new Area(i));
    }

    Area* area4 = areas[4];

    for (int i = 500; i < 510; ++i)
    {
	Facility* fac = new Facility(i, "Rawr", 1, 2, QPoint(0,0));
	area4->addFacility(fac);
    }

    // Add Patient John to Area 4, Facility 508
    Facility* fac = area4->getFacility(508);
    fac->addPatientToBed(new Patient("2341245", "John", "Doe", EOBC::AC), EOBC::CCC);

    // Move Patient John to Area 4, Facility 2
    // Remove Patient John

    foreach(Area* area, areas)
    {
	delete area;
    }
*/
    return a.exec();
}

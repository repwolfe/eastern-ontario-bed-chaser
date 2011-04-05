#include "reportbars.h"
 /** The constructor for ReportBars
   * initializes the QVectors that contain all the data, the datatypes, and the colors for each bar
   * @param barHei stores the actual data for this bar. The reference is saved so it can be drawn later
   * @param barTyp stores the type of data. Can either be a facil name, or a bed type
   * @param parent does nothing
   */
ReportBars::ReportBars(QVector<int>& barHei,QVector<QString>& barTyp,QObject *parent) :
    QObject(parent) , barHeights(barHei), barTypes(barTyp)
{
    barMax = 4;
    barColors = new QColor[4];
    barColors[0] = Qt::blue;
    barColors[1] = Qt::red;
    barColors[2] = QColor(100,255,0);
    barColors[3] = QColor(0,255,100);


   //this->barHeights = new int[4];
    //this->barHeights[0] = barHeights[0];
    //this->barHeights[1] = barHeights[1];
    //this->barHeights[2] = barHeights[2];
    //this->barHeights[3] = barHeights[3];
    totalHeight = 0;
    for(int i=0;i<barHei.count();i++)
        this->totalHeight+=barHeights.at(i);
    barMax=0;
    for(int i=0;i<barHei.count();i++)
    {
        if(barHeights.at(i)>0)
            barMax++;
    }
    //QLinearGradient rg(
     //   position+size/2,
       // QPoint(position.x(),position.y()+size.y()/2));
}
 /** the deconstructor for ReportBars
   * deletes the barColors
   */
ReportBars::~ReportBars()
{
    //delete barHeights;
    delete barColors;
}
/** The draw method renders the ReportBars on to the graph
  * uses a QLinearGradient to make the color of the bars all fancy.
  * the bars are rendered to look somewhat 3D, they have an oblique top and side,
  * and the gradient is drawn in a way that the side appears to be in shadow.
  * @param g The painter object given by the QWidget parent.
  * @param threeDNess the cooeficent for how oblique the rectangles are.
  */
void ReportBars::draw(QPainter& g,int threeDness)
{
    if(barMax>0)
    {
        rg.setStart(position+size/2);
        rg.setFinalStop(QPoint(position.x(),position.y()+size.y()/2));

        rg.setColorAt(0,barColors[barMax-1].lighter(70));
        rg.setColorAt(1,barColors[barMax-1].lighter(150));
        //rg.setColorAt(0.5,barColors[1]);
        //rg.setColorAt(0.75,barColors[2]);
        g.setBrush(rg);
        g.setPen(Qt::black);
        //g.drawRect(position.x()-threeDness,position.y()+threeDness,size.x(),size.y()); ///Draw Face
        rg.setColorAt(0,barColors[0].lighter(70));
        rg.setColorAt(1,barColors[0].lighter(150));
        g.setBrush(rg);
        QPolygon top;                                                                   ///Draw Top
        top.push_back(QPoint(position.x()-threeDness,position.y()+threeDness));
        top.push_back(QPoint(position.x(),position.y()));
        top.push_back(QPoint(position.x()+size.x(),position.y()));
        top.push_back(QPoint(position.x()+size.x()-threeDness,position.y()+threeDness));
        g.drawPolygon(top);

        float lastHeight = 0;
        for(int i=0;i<barHeights.count();i++)
        {
            if(barHeights.at(i)>0)
            {
                g.setPen(Qt::black);
                rg.setColorAt(0,barColors[i].lighter(70));
                rg.setColorAt(1,barColors[i].lighter(150));
                g.setBrush(rg);                                          ///Draw Side
                QPolygon side;
                side.push_back(QPoint(position.x()+size.x()-threeDness,position.y()+threeDness+ lastHeight));
                side.push_back(QPoint(position.x()+size.x(),position.y()+ lastHeight));
                side.push_back(QPoint(position.x()+size.x(),position.y()+ lastHeight +barHeights.at(i)*size.y()/totalHeight));
                side.push_back(QPoint(position.x()+size.x()-threeDness,position.y()+threeDness+ lastHeight +barHeights.at(i)*size.y()/totalHeight));
                g.drawPolygon(side);

                g.drawRect(position.x()-threeDness,position.y()+ threeDness + lastHeight,size.x(),barHeights.at(i)*size.y()/totalHeight); ///Draw Other Faces
                lastHeight += barHeights.at(i)*size.y()/totalHeight;
                g.setPen(Qt::white);
                g.drawText(position.x()+size.x()/2 - 15,position.y()+lastHeight,QString::number(barHeights.at(i)));
            }
        }
    }
}
int ReportBars::getHeight()
{
    return totalHeight;
}
QVector<int>& ReportBars::getAllHeights()
{
    return barHeights;
}
QColor* ReportBars::getAllColors()
{
    return barColors;
}
QVector<QString>& ReportBars::getAllBarTypes()
{
    return barTypes;
}

void ReportBars::setPosition(QPoint p)
{
    position = p;
}

void ReportBars::setSize(QPoint s)
{
    size = s;
}
void ReportBars::setBarMax(int bm)
{
    this->barMax = bm;
    totalHeight = 0;
    for(int i=0;i<barMax;i++)
        this->totalHeight+=barHeights.at(i);
}

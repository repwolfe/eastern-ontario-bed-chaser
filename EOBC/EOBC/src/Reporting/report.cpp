#include "report.h"
int windHeight = 450;
int height = 300;
int left = 120;
int width = 300;
int top = 70;
int threeDness = 10;
 /** This is the Constructor for Report.
   * it takes in many parameters that define when the report should hold data, the kind of report, and all the data recieved from the remote host.
   * there is little intelligence in the constructor, all the parameters are just saved, and prepared to render.
   * @param date The whole string of dates, includes two years, months, and days.
   * @param startDate A date object for when the report data starts.
   * @param bars A QVector of ReportBars that contain all the numerical data of the report. Each bar may contain several minibars of data.
   * @param facilityType contains the kind of facility that data has been requested. Only useful if only one facility has been selected
   * @param dateType is an int that will determine if the report will display difference in months, days, or years.
   * @param fac is the QVector that contains all the facilities that were involved with the report.
   */
Report::Report(QString date, QDate startDate,QVector<ReportBars*>& bars,int facilityType, int dateType,QVector<QString>& fac,QObject *parent) :
    QObject(parent), facility(fac)
{
    this->bars = bars;
    this->date = date;
    this->dateType = dateType;
    this->facilityType = facilityType;
    this->startDate = startDate;
   // this->facility = facility;
    type = Report::OCCUPANCYRATESNUMBER;
    maxHeight = 0;
    for(int i=0;i<bars.count();i++)
    {
        if(facilityType == Convenience::LONGTERMCARE)
        {
            bars.at(i)->setBarMax(2);
        }
        if(bars.at(i)->getHeight() > maxHeight)
            maxHeight = bars.at(i)->getHeight();
    }
}
 /** the destructor for Report
   * deletes the ReportBars involved in the report object.
   */
Report::~Report()
{
    QVector<ReportBars*>::iterator iter = bars.begin();
    while(iter != bars.end())
    {
        delete *iter;
        iter++;
    }
}
  /** The draw method for Report renderes the actual report itself on a given QWidget
    * paints a white background based on the width and height of the report, and calls a couple helper methods
    *@param g The painter object given by the QWidget parent.
    */
void Report::draw(QPainter& g)
{
    g.setBrush(Qt::white);
    g.setPen(Qt::black);
    g.drawRect(0,0,width + 400,50+windHeight);

    drawGrid(g);
    drawBars(g);
}
/** The draw method for Report that draws the background, labels, and legend of the report
  * a couple calculations are done to find the center of the text as to find the right spot to put the title.
  * the legend is drawn by calling a helper method.
  *@param g The painter object given by the QWidget parent.
  */
void Report::drawGrid(QPainter& g)
{
    int bars = 6;
    g.setBrush(QColor(190,210,255));
    g.drawRect(left,top,width,height);

    g.drawLine(left,top,left+width,top);
    g.drawLine(left,top,left-threeDness,top+ threeDness);

    g.drawLine(left-threeDness,top + threeDness,left-threeDness,top + height+ threeDness);
    g.drawLine(left,top,left,top + height);
    g.drawLine(left + width,top,left+width,top + height);

    g.drawLine(left,top+height,left+width,top+height);
    g.drawLine(left,top+height,left-threeDness,top+height+ threeDness);

    for(int i=0;i<=bars;i++)
    {
        int ratio = (height / bars)*i;
        g.drawLine(left,top +ratio,left+width,top+ratio);
        g.drawLine(left,top+ratio,left-threeDness,top+ratio+ threeDness);
        g.setPen(Qt::black);
        g.drawText(left - 40,top + ratio + 15,QString::number((int)maxHeight - (i*(int)maxHeight/bars)));
    }
    QPolygon bottom;
    bottom.push_back(QPoint(left - threeDness,height + top + threeDness));
    bottom.push_back(QPoint(left,height + top));
    bottom.push_back(QPoint(left+width,height + top));
    bottom.push_back(QPoint(left+width - threeDness,height + top + threeDness));
    g.setBrush(Qt::gray);
    g.drawPolygon(bottom,Qt::OddEvenFill);

    //
    ///Draw Legend
    //

    drawLegend(g);



    //
    // DRAW TITLES
    //

    QFont font = g.font();//save old font
    g.setBrush(Qt::black);

    g.setFont(QFont("Times New Roman",16,5));
    QFontMetrics qfm(QFont("Times New Roman",16,5));
    g.drawText((width+200)/2-qfm.width(date)/2,20,"Report: " + date);

    g.setFont(QFont("Arial",14,5));
    g.drawText(width/2+left-30, height+top+threeDness + 60,"Time");
    for (int i=0;i<facility.size();i++)
    {
        g.drawText(10,height+top+threeDness + 60 + 30*i,facility.at(i));
    }
    if(dateType == Report::DAY)
        g.drawText(left-30, height+top+threeDness + 30,""+startDate.toString("MMM"));
    if(this->type == Report::OCCUPANCYRATESNUMBER)
    {
        g.save();
        g.setFont(QFont("Arial",14,5));
        g.translate(left-70,height/2+125);
        g.rotate(-90);
        g.drawText(0,0,"Occupancy Rates");
        g.restore();
    }
    g.setFont(font); // restore old font

    //
    // DRAW TITLES
    //
}
/** The draw method for Report renderes the bars (actual information) of the report.
  * makes a couple calculations to find where each bar should be drawn based on the number of bars,
  * then calls the ReportBar's draw method for each bar.
  *@param g The painter object given by the QWidget parent.
  */
void Report::drawBars(QPainter& g)
{
    for(int i=0;i<bars.count();i++)
    {
        ReportBars* curBar = bars.at(i);

        int barLeft = left + i*width/bars.count() + 10;
        float barWidth = width/bars.count() - 20;
        int barHeight = curBar->getHeight();
        curBar->setPosition(QPoint(barLeft,(top+height)-(barHeight/maxHeight)*height));
        curBar->setSize(QPoint(barWidth,(barHeight/maxHeight)*height));

        //g.setBrush(Qt::blue);
        //g.drawRect(barLeft,(50+height)-(curBar->getHeight()/maxHeight)*height,barWidth,(curBar->getHeight()/maxHeight)*height);
        curBar->draw(g,threeDness);
        g.setPen(Qt::black);
        if(dateType == Report::DAY)
            g.drawText(left+i*(width/bars.count()) + 15, height+top+threeDness + 20,""+QString::number(startDate.day()+i));
        if(dateType == Report::MONTH)
            g.drawText(left+i*(width/bars.count()) + 15, height+top+threeDness + 20,""+startDate.addMonths(i).toString("MMM"));
        if(dateType == Report::YEAR)
            g.drawText(left+i*(width/bars.count()) + 15, height+top+threeDness + 20,""+QString::number(startDate.year()+i));
    }
}

QString Report::getDate()
{
    return date;
}
int Report::getBarNum()
{
    return bars.count();
}
int Report::getFacilNum()
{
    return facility.count();
}

void Report::setWidth(int w)
{
    width = w;
}
void Report::setHeight(int h)
{
    windHeight = h;
}
/** The draw method for Report renderes the legend of the report
  * the legend contains the kind of data given in each report bar
  * can be a certain kind of care type, or a facility name
  *@param g The painter object given by the QWidget parent.
  */
void Report::drawLegend(QPainter& g)
{
    g.setFont(QFont("Arial",12,5));
    g.drawText(20,45,"Legend: ");
    QLinearGradient rg;
    ReportBars* curBar = bars.at(0);
    for(int i=0;i<curBar->getAllBarTypes().count();i++)
    {
        if(curBar->getAllHeights().at(i)>=0 && curBar->getAllHeights().at(i) < 1000)
        {
            rg.setStart(QPoint (100 + i*80,40));
            rg.setFinalStop(QPoint(100 + i*80,70));

            rg.setColorAt(0,curBar->getAllColors()[i].lighter(70));
            rg.setColorAt(1,curBar->getAllColors()[i].lighter(150));
            //rg.setColorAt(0.5,barColors[1]);
            //rg.setColorAt(0.75,barColors[2]);
            g.setBrush(rg);
            QString typ = curBar->getAllBarTypes().at(i);
            if(typ.size()>4)
                typ.resize(4);
            if(i<2)
            {
                g.drawText(100 + 25 + 70*i,55,""+typ);
                g.drawRect(100 + i * 70,40,20,20);
            }
            else
            {
                g.drawText(50 + 25 + 110*i,55,""+typ);
                g.drawRect(50 + i * 110,40,20,20);
            }
        }
    }
}

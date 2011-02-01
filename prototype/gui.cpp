#include "gui.h"
#include "ui_gui.h"


static const QSize resultSize(1000, 1000);
Gui::Gui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gui)
{
    ui->setupUi(this);
    QImage sourceImage;
    QToolButton* sourceButton = new QToolButton;
    sourceButton->setIconSize(resultSize);
    ui->resultLabel->setGeometry(0,0,1000 ,1000);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(logInButton()));
    loadImage(":/LHINLogo2.png", &sourceImage, ui->resultLabel);
}

Gui::~Gui()
{
    delete ui;
}
void Gui::loadImage(const QString &fileName, QImage *image,
                              QLabel *button)
{
    image->load(fileName);

    QImage fixedImage(resultSize, QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&fixedImage);
   // painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(QRect(0,0,resultSize.width(),resultSize.height()), Qt::white);
    //painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawImage(QPoint(),*image);
    painter.end();
    button->setPixmap(QPixmap::fromImage(fixedImage));
//button->setIcon(QPixmap::fromImage(*image));
    //*image = fixedImage;

    //recalculateResult(image);
}
void Gui::recalculateResult(QImage* img)
{
   // QPainter::CompositionMode mode;

}

void Gui::logInButton()
{
    this->close();
    wind.setGeometry(this->geometry());
    wind.show();
    wind.setFocus();

}

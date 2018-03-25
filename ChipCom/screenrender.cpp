// ----------------------------------------------------------------- //
//                     Creation d'un widget de rendu                 //
// ----------------------------------------------------------------- //



//-
#include "screenrender.h"
#include "data.h"
#include "setting.h"
//-



ScreenRender::ScreenRender(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(Data::getSetting()->tsScreenWidth, Data::getSetting()->tsScreenHeight);
}

void ScreenRender::addPoint(QString point)
{
    pointsList.append(point);
    this->update();
}

void ScreenRender::setFontColor(QString hexColor)
{
    this->setStyleSheet("background-color:" + hexColor + ";");
    update();
}

void ScreenRender::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(Qt::blue);
    painter.drawRect(0, 0, Data::getSetting()->tsScreenWidth-1, Data::getSetting()->tsScreenHeight-1);

    if(pointsList.isEmpty())
        return;

    QString points = pointsList.takeFirst();
    QStringList list = points.split(';');

    int px = list.value(0).toInt();
    int py = list.value(1).toInt();

    if(list.size() != 2)
        return;

    painter.setPen(Qt::black);
    painter.setBrush(Qt::blue);
    painter.drawEllipse(QPoint(px, py), 5, 5);
}

//-
#include <QDebug>
#include <qthread.h>
#include <QApplication>
#include "oscillo.h"
#include "data.h"
#include "texthelper.h"
#include "setting.h"
//-

Oscillo::Oscillo(QString data, QWidget *parent) : QWidget(parent),
    screenWidth(Data::getSetting()->oscilloWidgetWidth), screenHeight(Data::getSetting()->oscilloWidgetHeight),
    rawData(data), listPos(0)
{
    this->setFixedSize(screenWidth, screenHeight);
    this->dataList = data.split(";");
    if(dataList.last() == "")
        dataList.removeLast();

    this->connect(&updateTimer, SIGNAL(timeout()),
                  this,         SLOT(update()));
    this->updateTimer.start(10);
    qDebug() << "----------------------------------------";
    qDebug() << dataList;
    qDebug() << "----------------------------------------";
}

void Oscillo::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(Qt::blue);

    QPoint oldPoint(5, screenHeight - 10);
    int actualPos = 0;
    QString lastData = dataList.last();
    QString lastDataSplit = lastData.split(":").value(1);
    int lastDataInt = lastDataSplit.toInt();
    if(lastDataInt <= 0)
        lastDataInt = 100;

    foreach (QString data, dataList)
    {
        QString data1 = data.split(":").value(0);
        int     data2 = data.split(":").value(1).toFloat();

        if(data1 != "h" and data1 != "l")
        {
            qDebug() << "Error1: " << data1;
            continue;
        }

        if(data2 <= 0)
        {
            qDebug() << "Error2: " << data2;
            continue;
        }

        int pointX = 0;
        int pointY = 0;

        if(data1 == "h")
            pointY = 30;
        else if (data1 == "l")
            pointY = screenHeight - 10;

        if(actualPos == 0 and data2 > 10000)
            data2 = 500;

        pointX = (float) data2 / (float) lastDataInt * (float) (screenWidth - 20) + 10;
        //pointX = data2 / 100;

        painter.drawLine(oldPoint.x(), oldPoint.y(), pointX, oldPoint.y());
        painter.drawLine(pointX, oldPoint.y(), pointX, pointY);

        if(actualPos == listPos)
            painter.drawText(5, 15, data);


        oldPoint.setX(pointX);
        oldPoint.setY(pointY);
        actualPos++;

        if(actualPos > listPos)
            break;
    }

    listPos++;
    if(listPos > dataList.size())
    {
        painter.drawText(5, 15, QString::number(dataList.size()) + " data");
        updateTimer.stop();
    }
}

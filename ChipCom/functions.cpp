
//-
#include <QTime>
#include <QDebug>
#include "functions.h"
#include "data.h"
#include "serialport.h"
#include "commandinterpreter.h"
//-

void Functions::setUpTime(SerialData *serialData)
{
    int sTime = QTime::currentTime().second()   +
                QTime::currentTime().minute()   * 60 +
                QTime::currentTime().hour()     * 3600;
    Data::addMainText("Time set to: " + QString::number(sTime) + "s");
    Data::getSerialPort()->sendText("/setuptime/" + QString::number(sTime), serialData->portName);
}

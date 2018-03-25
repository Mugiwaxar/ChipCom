// ----------------------------------------------------------------- //
//             Contient les informations d'un port serial            //
// ----------------------------------------------------------------- //


//-
#include "serialdata.h"
#include "data.h"
#include "setting.h"
//-

SerialData::SerialData(QSerialPort *serialPort) : QObject(serialPort), serialPort(serialPort),
    portName(serialPort->portName()), messageReceived(true), timeOut(0), color(Data::getSetting()->openPortColor)
{}

void SerialData::sendTimerSlot()
{
    emit sendTimerSignal(this);
}

// -------------------------------------------- //
//     Gère la connexion avec le port série     //
// -------------------------------------------- //

//-
#include <QtConcurrent>
#include <QThread>
#include "serialport.h"
#include "data.h"
#include "texthelper.h"
#include "datainterpreter.h"
#include "commandinterpreter.h"
#include "setting.h"
//-

// -- Constructeur -- //
SerialPort::SerialPort()
{
    connectedPorts  = new QList<SerialData *>;
}

// -- Destructeur -- //
SerialPort::~SerialPort()
{}

// ------------------------------------------- scanPorts -------------------------------------------- //
void SerialPort::scanPorts(QList<SerialData *> *portsList)
{
    foreach(QSerialPortInfo portInfo, listPort())
    {
        if(!portInfo.manufacturer().contains("Arduino"))
            continue;

        bool portFound = false;

        foreach (SerialData *serialPort, *portsList)
        {
            if(portInfo.portName() == serialPort->portName)
            {
                portFound = true;
                break;
            }
        }

        if(!portFound)
            emit portConnectedSignal(portInfo.portName(), true);
    }


    foreach (SerialData *serialPort, *portsList)
    {
        bool isOpen = false;
        foreach(QSerialPortInfo portInfo, listPort())
        {
            if(serialPort->portName == portInfo.portName())
            {
                if(portInfo.serialNumber() != "")
                    isOpen = true;
            }
        }
        if(!isOpen)
            emit portDisconnectedSignal(serialPort->portName);
    }

}

// ------------------------------------------- listPort -------------------------------------------- //
QList<QSerialPortInfo> SerialPort::listPort(bool showInfos)
{
    QList<QSerialPortInfo> portsList = QSerialPortInfo::availablePorts();

    if(showInfos)
    {
        foreach (QSerialPortInfo portInfo, portsList)
        {
            Data::addMainText("---");
            Data::addMainText("Port name:"      + portInfo.portName());
            Data::addMainText("Serial number:"  + portInfo.serialNumber());
            Data::addMainText("Manifacturer:"   + portInfo.manufacturer());
            Data::addMainText("Description:"    + portInfo.description());
            Data::addMainText("---");
        }
    }

    return portsList;

}

// ------------------------------------------- scanPortsSlot -------------------------------------------- //
void SerialPort::scanPortsSlot()
{
    QtConcurrent::run(this, &SerialPort::scanPorts, connectedPorts);
}

// ------------------------------------------- connectToPort -------------------------------------------- //
void SerialPort::connectToPort(QString portName, bool autoConnect)
{
    if(autoConnect == true && !Data::getSetting()->autoconnect)
        return;

    foreach (QSerialPortInfo portInfo, listPort())
    {
        if(portInfo.portName() == portName)
        {
            QSerialPort *serialPort = new QSerialPort();
            serialPort->setPort(portInfo);
            serialPort->setBaudRate(Data::getSetting()->baudRate);
            SerialData *serialData = new SerialData(serialPort);
            connectedPorts->append(serialData);
            if(serialPort->open(QIODevice::ReadWrite))
            {
                Data::addMainText(TextHelper::ToBlue("Connected to " + serialPort->portName()));
                Data::addSysTrayText("Connected to " + serialPort->portName());
                startReading(serialData);
                startSending(serialData);
                Data::getMainWindows()->updateAll();
                return;
            }
            else
                Data::addMainText(TextHelper::ToRed("Unable to open port"));
            break;
        }
    }
    Data::addMainText(TextHelper::ToRed("Port no found: " + portName));
}

// ------------------------------------------- disconnectPort -------------------------------------------- //
void SerialPort::disconnectPort(QString serialPortName)
{
    SerialData *serial = 0;
    foreach (SerialData *serialData, *connectedPorts)
    {
        if(serialData->portName == serialPortName)
            serial = serialData;
    }

    if(serial == 0)
        return;

    serial->serialPort->close();
    serial->serialPort->disconnect();
    connectedPorts->removeOne(serial);
    serial->serialPort->deleteLater();
    serial->deleteLater();

    Data::addMainText(TextHelper::ToRed(serial->portName + " Disconnected!"));
    Data::addSysTrayText(serial->portName + " Disconnected!");
}

// ------------------------------------------- startScanning -------------------------------------------- //
void SerialPort::startScanning()
{
    connect(&portScanerTimer,   &QTimer::timeout,
            this,               &SerialPort::scanPortsSlot);
    connect(this,               &SerialPort::portConnectedSignal,
            this,               &SerialPort::connectToPort);
    connect(this,               &SerialPort::portDisconnectedSignal,
            this,               &SerialPort::disconnectPort);
    portScanerTimer.start(Data::getSetting()->scanPortsSpeed);
}

// ------------------------------------------- startReading -------------------------------------------- //
void SerialPort::startReading(SerialData *serial)
{
    if(serial == 0)
    {
        Data::addMainText(TextHelper::ToRed("Not connected to serial: " + serial->portName));
        return;
    }
    if(!serial->serialPort->isOpen())
    {
        Data::addMainText(TextHelper::ToRed("Not connected to serial: " + serial->portName));
        return;
    }

    connect(serial->serialPort,     &QSerialPort::readyRead,
            this,                   &SerialPort::dataDetected);


    Data::addMainText(TextHelper::ToGreen("Ready to listen on " + serial->portName));
}

// ------------------------------------------- startSending -------------------------------------------- //
void SerialPort::startSending(SerialData *serial)
{
    if(serial == 0 or !serial->serialPort->isOpen())
    {
        Data::addMainText(TextHelper::ToRed("Not connected to serial: " + serial->portName));
        return;
    }

    connect(&serial->sendTimer,         &QTimer::timeout,
            serial,                     &SerialData::sendTimerSlot);
    connect(serial,                     &SerialData::sendTimerSignal,
            this,                       &SerialPort::sendData);
    serial->sendTimer.start(Data::getSetting()->sendDataSpeed);

    Data::addMainText(TextHelper::ToGreen("Ready to write on " + serial->portName));
}

// ------------------------------------------- getPort -------------------------------------------- //
SerialData *SerialPort::getPort(QString portName)
{
    foreach(SerialData *serial, *connectedPorts)
    {
        if(serial->portName == portName)
            return serial;
    }

    Data::addMainText("Serial port no found: " + portName);
    return 0;
}

// ------------------------------------------- messageReceived -------------------------------------------- //
void SerialPort::messageReceived(SerialData *serialData)
{
    serialData->messageReceived = true;
}

// ------------------------------------------- sendText -------------------------------------------- //
void SerialPort::sendText(QString text, QString portName)
{
    SerialData *serial = getPort(portName);

    if(serial == 0 or !serial->serialPort->isOpen())
    {
        Data::addMainText(TextHelper::ToRed("Not connected to serial:" + serial->portName));
        return;
    }

    text.append("\n");

    QStringList stringList(text);

    foreach (QChar aChar, stringList.takeFirst())
    {
        serial->charList.append(aChar);
    }

}

// ------------------------------------------- dataDetected -------------------------------------------- //
void SerialPort::dataDetected()
{
    QSerialPort *serial = qobject_cast<QSerialPort*>(sender());
    SerialData  *serialData = getPort(serial->portName());
     serialData->color = Data::getSetting()->receivingColor;
    Data::getMainWindows()->updateAll();

    if(serial == 0 or !serial->canReadLine())
        return;

    QString message = QString::fromUtf8(serial->readLine());


    message = message.remove("\r");
    message = message.remove("\n");

    if(message == "")
        return;

    DataInterpreter::readData(message, serialData);
    serialData->color = Data::getSetting()->openPortColor;
    Data::getMainWindows()->updateAll();
}

// ------------------------------------------- sendData -------------------------------------------- //
void SerialPort::sendData(SerialData *serialData)
{
    serialData->color = Data::getSetting()->sendingColor;
    Data::getMainWindows()->updateAll();

    if(serialData->charList.isEmpty())
        return;

    if(serialData->messageReceived)
    {
        QString text = serialData->charList.takeFirst();
        int eta = serialData->serialPort->write(text.toStdString().c_str(), text.length());
        serialData->serialPort->flush();
        if(eta < 0)
            Data::addMainText(TextHelper::ToRed("Error while sending data: ") + serialData->serialPort->portName());
        serialData->messageReceived = false;
        serialData->timeOut = 0;
    }
    else
    {
        if(serialData->timeOut <= Data::getSetting()->reponseTimeout)
        {
            serialData->timeOut++;
        }
        else
        {
            Data::addMainText(TextHelper::ToRed("Reponse TimeOut: " + serialData->serialPort->portName()));
            serialData->timeOut = 0;
            serialData->messageReceived = true;
        }
    }

    serialData->color = Data::getSetting()->openPortColor;
    Data::getMainWindows()->updateAll();
}

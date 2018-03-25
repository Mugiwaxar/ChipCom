// -------------------------------------- //
//        Interprète les commandes        //
// -------------------------------------- //

//-
#include <QDebug>
#include <QtConcurrent>
#include "commandinterpreter.h"
#include "data.h"
#include "serialport.h"
#include "functions.h"
//-


bool CommandInterpreter::readCommand(QString command, SerialData *serialData)
{
    if(command.toLower().contains("listserialport"))
    {
        Data::getSerialPort()->listPort();
        return true;
    }

    if(command.toLower().contains("connecttoport"))
    {
        //QString portName = command.split(" ").value(1);

        //if(portName == "")
        //    return true;

        Data::addMainText("Manual connect disabled");
        //Data::getSerialPort()->connectToPort(portName);
        return true;
    }

    if(command.toLower().contains("startscanning"))
    {
        Data::getSerialPort()->startScanning();
        return true;
    }

    if(command.toLower().contains("sendtext"))
    {
        Data::getSerialPort()->sendText(command.split(" ").value(1), command.split(" ").value(2));
        return true;
    }

    if(command.toLower().contains("testspeed"))
    {
        //int number = command.split(" ").value(1).toInt();
        Data::addMainText("testspeed disabled");
        //QtConcurrent::run(Data::getSerialPort(), &SerialPort::testSpeed, number);
        return true;
    }

    if(command.toLower().contains("testcharspeed"))
    {
        //int number = command.split(" ").value(1).toInt();
        Data::addMainText("testspeed disabled");
        //QtConcurrent::run(Data::getSerialPort(), &SerialPort::testCharSpeed, number);
        return true;
    }

    if(command.toLower().contains("startscreen"))
    {

        Data::getScreenRender()->show();
        return true;
    }

    if(command.toLower().contains("setuptime"))
    {
        Functions::setUpTime(serialData);
        return true;
    }

    return false;
}

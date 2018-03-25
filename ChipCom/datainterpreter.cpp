//-
#include "datainterpreter.h"
#include "data.h"
#include "serialport.h"
#include "screenrender.h"
#include "commandinterpreter.h"
#include "oscillo.h"
//-

void DataInterpreter::readData(QString data, SerialData *serialData)
{
    data = data.toLower();
    if(data == "/r/")
    {
        Data::getSerialPort()->messageReceived(serialData);
        return;
    }

    if(data.contains("/touchpoints/"))
    {
        if(!Data::getScreenRender()->isVisible())
            return;
        data.remove("/touchpoints/");
        Data::getScreenRender()->addPoint(data);
        return;
    }

    if(data.contains("/seektime/"))
    {
        CommandInterpreter::readCommand("setuptime", serialData);
        Data::addMainText("Time Synchronization...");
        return;
    }

    if(data.contains("/ClockClicked/"))
    {
        //return;
    }

    if(data.contains("/color/"))
    {
        data.remove("/color/");
        Data::getScreenRender()->setFontColor(data);
        return;
    }


    if(data.contains("/oscillo/"))
    {
        data.remove("/oscillo/");
        Oscillo *oscillo = new Oscillo(data);
        oscillo->show();
        return;
    }



    Data::addMainText("Data: " + data);
}

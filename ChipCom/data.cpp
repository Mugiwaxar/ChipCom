// --------------------------------------------------- //
//      Contient toutes les données du programme       //
// --------------------------------------------------- //

//-
#include <QDebug>
#include "data.h"
//-

Data *Data::data = 0;


Data::Data() : mainWindows(0), screenRender(0), systray(0)
{
    this->setting       = new Setting();
    this->serialPort    = new SerialPort();
}

void Data::setMainWindows(MainWindow *value)
{
    if(data->mainWindows != 0)
        qDebug() << "MainWindows set twice";
    data->mainWindows = value;
}
MainWindow *Data::getMainWindows()
{
    if(data->mainWindows == 0)
        qDebug() << "MainWindows == 0";
    return data->mainWindows;
}
void Data::addMainText(QString text)
{
    if(data->mainWindows == 0)
    {
        qDebug() << "MainWindows not set!";
        return;
    }
    data->mainWindows->addText(text);
}

void Data::addSysTrayText(QString text)
{
    if(!Data::getMainWindows()->isVisible())
        Data::getSystray()->showMessage("ChipCom", text, QSystemTrayIcon::Information,1000);
}


void Data::setSerialPort(SerialPort *value)
{
    if(data->serialPort != 0)
        qDebug() << "SerialPort set twice";
    data->serialPort = value;
}
SerialPort *Data::getSerialPort()
{
    if(data->serialPort == 0)
    {
        setSerialPort(new SerialPort());
    }
    return data->serialPort;
}



void Data::setScreenRender(ScreenRender *screenRender)
{
    if(data->screenRender != 0)
        qDebug() << "ScreenRender set twice";
    data->screenRender = screenRender;
}

ScreenRender *Data::getScreenRender()
{
    if(data->screenRender == 0)
    {
        data->screenRender = new ScreenRender();
    }
    return data->screenRender;
}

void Data::setSystray(QSystemTrayIcon *value)
{
    if(data->systray != 0)
        qDebug() << "Systray set twice";
    data->systray = value;
}

QSystemTrayIcon *Data::getSystray()
{
    if(data->systray == 0)
    {
        data->systray = new QSystemTrayIcon(Data::getMainWindows());
    }
    return data->systray;
}

void Data::setSetting(Setting *value)
{
    if(data->setting != 0)
        qDebug() << "Setting set twice";
    data->setting = value;
}

Setting *Data::getSetting()
{
    if(data->setting == 0)
    {
        data->setting = new Setting();
    }
    return data->setting;
}

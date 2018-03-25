// ----------------------------------------------------------------- //
//            Contient tout les paramètres de l'application          //
// ----------------------------------------------------------------- //
//-
#include <QApplication>
#include <QSerialPort>
#include <QDebug>
#include "setting.h"
#include "data.h"
#include "mainwindow.h"
//-

Setting::Setting(QObject *parent) : QObject(parent), setting("Dexy", "ChipCom")
{
    this->mainWindowsW      = 778;
    this->mainWindowsH      = 404;
    this->systrayIcone      = QApplication::style()->standardIcon(QStyle::SP_ComputerIcon);
    this->tsScreenWidth     = 320;
    this->tsScreenHeight    = 240;

    this->baudRate          = QSerialPort::Baud9600;
    this->scanPortsSpeed    = 10;
    this->sendDataSpeed     = 1;
    this->reponseTimeout    = 1000;

    openPortColor           = "#008000";
    sendingColor            = "#000099";
    receivingColor          = "#cc0000";

    this->autoconnect       = true;

    this->oscilloWidgetWidth    = 1200;
    this->oscilloWidgetHeight   = 200;


}

void Setting::loadSetting()
{
    this->autoconnect = setting.value("autoconnect", true).toBool();
}

void Setting::saveSetting()
{
    setting.setValue("autoconnect", this->autoconnect);

}

void Setting::setAutoConnect()
{
    this->autoconnect = this->autoconnect ? false : true;
    saveSetting();
    Data::getMainWindows()->updateAll();
}

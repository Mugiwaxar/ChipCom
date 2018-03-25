// --------------------------------------------------- //
//      Contient toutes les données du programme       //
// --------------------------------------------------- //

#ifndef DATA_H
#define DATA_H

//-
#include <QSystemTrayIcon>
#include "mainwindow.h"
#include "serialport.h"
#include "screenrender.h"
#include "setting.h"

//-


class Data
{

public:

    Data();
    static Data *data;

    static void setMainWindows(MainWindow *value);
    static MainWindow *getMainWindows();
    static void addMainText(QString text);
    static void addSysTrayText(QString text);

    static void setSerialPort(SerialPort *value);
    static SerialPort *getSerialPort();

    static void setScreenRender(ScreenRender *screenRender);
    static ScreenRender *getScreenRender();

    static void setSystray(QSystemTrayIcon *value);
    static QSystemTrayIcon *getSystray();

    static void setSetting(Setting *value);
    static Setting *getSetting() ;

private:

    MainWindow      *mainWindows;
    SerialPort      *serialPort;
    ScreenRender    *screenRender;
    QSystemTrayIcon *systray;
    Setting         *setting;

};

#endif // DATA_H

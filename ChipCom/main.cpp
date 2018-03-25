
//-
#include <QApplication>
#include <QStyle>
#include <QTimer>
#include "mainwindow.h"
#include "data.h"
#include "commandinterpreter.h"
#include "oscillo.h"
//-

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName("Dexy");
    QCoreApplication::setOrganizationDomain("http://www.yvelis.com");
    QCoreApplication::setApplicationName("ChipCom");

    Data::data = new Data();
    Data::getSetting()->loadSetting();

    MainWindow *mainWindows = new MainWindow();
    Data::setMainWindows(mainWindows);
    mainWindows->show();
    QApplication::setQuitOnLastWindowClosed(false);

    //CommandInterpreter::readCommand("ConnectToPort COM3");
    CommandInterpreter::readCommand("startscanning");

    return app.exec();
}

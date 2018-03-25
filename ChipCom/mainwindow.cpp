// ----------------------------------------------------------------- //
//                      Fenêtre principale du projet                 //
// ----------------------------------------------------------------- //


//-
#include <QMenu>
#include <QLabel>
#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "commandinterpreter.h"
#include "texthelper.h"
#include "data.h"
#include "setting.h"
#include "serialdata.h"
//-



// ------------------ Constructeur ------------------- //
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(Data::getSetting()->mainWindowsW, Data::getSetting()->mainWindowsH);

    QMenu *sysTrayMenu = new QMenu(this);
    sysTrayMenu->addAction("Quitter", this, &MainWindow::quit);

    QSystemTrayIcon *sysTray = new QSystemTrayIcon(this);
    Data::setSystray(sysTray);
    sysTray->setContextMenu(sysTrayMenu);
    sysTray->setIcon(Data::getSetting()->systrayIcone);
    sysTray->show();

    connectSignals();
    updateAll();
}

// ------------------- Destructeur ------------------- //
MainWindow::~MainWindow()
{
    delete ui;
}

// ------------ Connect Signals to Slots ------------- //
void MainWindow::connectSignals()
{
    ui->lineEdit->connect(ui->lineEdit, &QLineEdit::returnPressed,
                          this,         &MainWindow::enterPressed);
    connect(ui->autoConnectButton,      &QPushButton::released,
            Data::getSetting(),         &Setting::setAutoConnect);
    connect(ui->quitButton,             &QPushButton::released,
            this,                       &MainWindow::quit);
}

// ------------------ Ajouter du text ----------------- //
void MainWindow::addText(QString text)
{
    ui->textEdit->append(text);
}

void MainWindow::updateAll()
{
    this->ui->autoConnectButton->setText(Data::getSetting()->autoconnect ? "Auto Connect" : "Manual Connect");

    this->ui->portsList->clear();
    foreach(SerialData *data, *Data::getSerialPort()->connectedPorts)
    {
     this->ui->portsList->append("<font color='" + data->color + "'>" + data->portName + "</font>");
    }

    this->ui->portsNumber->setText("");
    this->ui->portsNumber->setText("Ports: " + QString::number(Data::getSerialPort()->connectedPorts->length()));
}

// -------------------- Touche entrer ----------------- //
void MainWindow::enterPressed()
{
    if(ui->lineEdit->text().length() <= 0)
        return;

    QString text = ui->lineEdit->text();

    ui->textEdit->append(TextHelper::ToBlue(ui->lineEdit->text()));
    ui->lineEdit->clear();

    bool ok = CommandInterpreter::readCommand(text);

    if(!ok)
    {
        ui->textEdit->append(TextHelper::ToRed("Unrecognized command!"));
    }

}

// ---------------------- x Event --------------------- //
void MainWindow::closeEvent(QCloseEvent *event)
{
    connect(Data::getSystray(),         &QSystemTrayIcon::activated,
            this,                       &MainWindow::iconeActivated);
    event->ignore();
    hide();
    updateAll();
    Data::getSetting()->saveSetting();
    //qApp->exit();
}

// ---------------- Systray interaction --------------- //
void MainWindow::iconeActivated(QSystemTrayIcon::ActivationReason reason)
{
    if(reason != QSystemTrayIcon::Trigger)
        return;

    updateAll();
    show();
    showNormal();
}

void MainWindow::quit()
{
    Data::getSystray()->deleteLater();
    Data::getSetting()->saveSetting();
    qApp->quit();
}

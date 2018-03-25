// -------------------------------------------- //
//     Gère la connexion avec le port série     //
// -------------------------------------------- //

#ifndef SERIALPORT_H
#define SERIALPORT_H

//-
#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QThread>
#include <QTimer>
#include "serialdata.h"
//-


class SerialPort : public QObject
{
    Q_OBJECT

public:
    SerialPort();
    ~SerialPort();

    void scanPorts(QList<SerialData *> *portsList);
    QList<QSerialPortInfo> listPort(bool showInfos = false);

    void startScanning();
    void startReading(SerialData *serial);
    void startSending(SerialData *serial);

    SerialData *getPort(QString portName);
    void sendText(QString text, QString portName);
    void messageReceived(SerialData *serialData);

private slots:
    void scanPortsSlot();
    void connectToPort(QString portName, bool autoConnect);
    void disconnectPort(QString serialPortName);
    void dataDetected();
    void sendData(SerialData *serialData);

signals:
    void portConnectedSignal(QString portName, bool autoConnect);
    void portDisconnectedSignal(QString portName);

public:
    QList<SerialData *> *connectedPorts;

private:
    QTimer               portScanerTimer;

};

#endif // SERIALPORT_H

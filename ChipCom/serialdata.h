// ----------------------------------------------------------------- //
//             Contient les informations d'un port serial            //
// ----------------------------------------------------------------- //

#ifndef SERIALDATA_H
#define SERIALDATA_H

#include <QObject>
#include <QSerialPort>
#include <QList>
#include <QTimer>

class SerialData : public QObject
{
    Q_OBJECT
public:
    explicit SerialData(QSerialPort *serialPort);

public slots:
    void sendTimerSlot();

signals:
    void sendTimerSignal(SerialData*);

public:

    QSerialPort    *serialPort;
    QString         portName;
    QList<QChar>    charList;
    bool            messageReceived;
    QTimer          sendTimer;
    int             timeOut;
    QString         color;

};

#endif // SERIALDATA_H

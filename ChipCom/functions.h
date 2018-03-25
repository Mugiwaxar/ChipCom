#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QObject>
#include <QTimer>
#include "serialdata.h"

class Functions : public QObject
{
    Q_OBJECT

public:
    static void setUpTime(SerialData *serialData);


private:
    static QTimer clockTimer;
};

#endif // FUNCTIONS_H

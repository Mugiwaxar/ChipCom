#ifndef DATAINTERPRETER_H
#define DATAINTERPRETER_H

#include <QObject>
#include <QStringList>
#include "serialdata.h"

class DataInterpreter
{
public:
    static void readData(QString data, SerialData *serialData);
};

#endif // DATAINTERPRETER_H

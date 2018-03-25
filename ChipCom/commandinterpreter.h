// -------------------------------------- //
//        Interprète les commandes        //
// -------------------------------------- //

#ifndef COMMANDINTERPRETER_H
#define COMMANDINTERPRETER_H

//-
#include <QString>
#include "serialdata.h"
//-


class CommandInterpreter
{
public:

    static bool readCommand(QString command, SerialData *serialData = 0);

};

#endif // COMMANDINTERPRETER_H

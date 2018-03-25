#ifndef SETTING_H
#define SETTING_H
// ----------------------------------------------------------------- //
//            Contient tout les paramètres de l'application          //
// ----------------------------------------------------------------- //
#include <QObject>
#include <QIcon>
#include <QStyle>
#include <QSettings>

class Setting : public QObject
{
    Q_OBJECT
private:
    QSettings setting;

public:
    explicit Setting(QObject *parent = 0);
    void loadSetting();
    void saveSetting();


public slots:
    void setAutoConnect();


public:

    // --------------------------- CONSTANT ---------------------------- //
    int     mainWindowsW;
    int     mainWindowsH;
    QIcon   systrayIcone;
    int     tsScreenWidth;
    int     tsScreenHeight;

    qint32  baudRate;
    int     scanPortsSpeed;
    int     sendDataSpeed;
    int     reponseTimeout;

    QString openPortColor;
    QString sendingColor;
    QString receivingColor;

    int oscilloWidgetWidth;
    int oscilloWidgetHeight;


    // ------------------------- ENREGISTRER --------------------------- //

    bool autoconnect;



    // ----------------------- NON ENREGISTRER ------------------------- //
};

#endif // SETTING_H

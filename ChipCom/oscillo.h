#ifndef OSCILLO_H
#define OSCILLO_H

#include <QObject>
#include <QTimer>
#include <QWidget>

class Oscillo : public QWidget
{
    Q_OBJECT
public:
    explicit Oscillo(QString data, QWidget *parent = 0);

protected slots:
    void paintEvent(QPaintEvent *);

private:
    int screenWidth;
    int screenHeight;
    QString rawData;
    QStringList dataList;
    int listPos;
    QTimer updateTimer;
};

#endif // OSCILLO_H

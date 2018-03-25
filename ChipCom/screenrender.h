// ----------------------------------------------------------------- //
//                     Creation d'un widget de rendu                 //
// ----------------------------------------------------------------- //

#ifndef SCREENRENDER_H
#define SCREENRENDER_H

//-
#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QStringList>
//-

class ScreenRender : public QWidget
{
    Q_OBJECT
public:
    explicit ScreenRender(QWidget *parent = 0);

    void addPoint(QString point);
    void setFontColor(QString hexColor);

signals:

private slots:
    void paintEvent(QPaintEvent *);

private:
    QStringList pointsList;

};
#endif // SCREENRENDER_H

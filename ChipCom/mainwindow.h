// ----------------------------------------------------------------- //
//                      Fenêtre principale du projet                 //
// ----------------------------------------------------------------- //
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//-
#include <QMainWindow>
#include <QCloseEvent>
#include <QSystemTrayIcon>
//-


namespace Ui {class MainWindow;}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void connectSignals();

    void addText(QString text);

private:
    Ui::MainWindow *ui;

public slots:
    void updateAll();

private slots:
    void enterPressed();
    void closeEvent(QCloseEvent *event);
    void iconeActivated(QSystemTrayIcon::ActivationReason reason);
    void quit();

};

#endif // MAINWINDOW_H

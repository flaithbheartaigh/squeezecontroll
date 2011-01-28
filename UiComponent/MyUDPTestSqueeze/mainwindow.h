#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QDebug>
#include <QtGlobal>



namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QUdpSocket *udpSocket;


private:
    int sendingFlag;
    int currentDatagram;
    QTimer *timer;
    Ui::MainWindow *ui;
    void initSocket();
    void Send_to_server();
    void Send_Array_to_server();



private slots:
    void readPendingDatagrams();
    void on_pushButton_clicked();
};





#endif // MAINWINDOW_H

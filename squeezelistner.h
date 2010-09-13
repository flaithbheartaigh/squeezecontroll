#ifndef SQUEEZELISTNER_H
#define SQUEEZELISTNER_H

#include <QObject>
#include <QTcpSocket>
#include <QtDebug>
#include <QMessageBox>
#include <QFile>
#include "database_struct.h"

class squeezeListner : public QObject
{
Q_OBJECT
public:
    squeezeListner(QObject *parent,QString mIpaddr,QString mPortNr);
    ~squeezeListner();
    void subscribeTo(QString subscribe);
    bool connectTo(QString mIpaddr,QString mPortNr);

private:
    void displayError(QAbstractSocket::SocketError socketError);
    QTcpSocket *tcpSocket;
    QString ip_addr;
    QString port_nr;
    bool connected;

private slots:
    void readData1();
    void disConnected();
signals:
    void sendStatus(QString datastring);


};

#endif // SQUEEZELISTNER_H

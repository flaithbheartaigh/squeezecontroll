#include "squeezelistner.h"

squeezeListner::squeezeListner(QObject *parent,QString mIpaddr,QString mPortNr)
 :QObject ( parent )
{
    bool ret;
    ret=false;

    port_nr=mPortNr;
    ip_addr=mIpaddr;
    tcpSocket = new QTcpSocket(this);
    if (QObject::connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readData1())));
        qDebug()<<"Signal ok";
    QObject::connect(tcpSocket, SIGNAL(disconnected()),this,SLOT(disConnected()));

    tcpSocket->abort();
    tcpSocket->connectToHost(ip_addr,port_nr.toInt());

    if (tcpSocket->waitForConnected(1000))
    {
        ret=true;
        qDebug("Connected!");
    }
}

void squeezeListner::disConnected()
{
    tcpSocket->close();
    connected=false;

}

squeezeListner::~squeezeListner()
{
    if (tcpSocket->isOpen())
        tcpSocket->close();
}

bool squeezeListner::connectTo(QString mIpaddr, QString mPortNr)
{
    bool ret;
    ret=false;
   connected=false;
    tcpSocket->abort();
    tcpSocket->connectToHost(mIpaddr,mPortNr.toInt());

    if (tcpSocket->waitForConnected(3000))
    {
        ret=true;
        qDebug("Connected!");
        connected=true;
    }



    return ret;
}

void squeezeListner::readData1()
{
    QString text,text1,command;
    text="";

    while (tcpSocket->canReadLine())
    {
        text1 = tcpSocket->readLine();
        text =text+ text1;
//        qDebug()<<"readline="<<text1;
    }
  //  qDebug()<<" ";
  //  qDebug()<<"Server Data "<<text;
    emit sendStatus(text);




}

void squeezeListner::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        //        QMessageBox::information(this, tr("Fortune Client"),
        //                                 tr("The host was not found. Please check the "
        //                                    "host name and port settings."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        //        QMessageBox::information(this, tr("Fortune Client"),
        //                                 tr("The connection was refused by the peer. "
        //                                    "Make sure the fortune server is running, "
        //                                    "and check that the host name and port "
        //                                    "settings are correct."));
        break;

        //        QMessageBox::information(this, tr("Fortune Client"),
        //                                 tr("The following error occurred: %1.")
        //                                 .arg(tcpSocket->errorString()));
    default: ;
    }
}

void squeezeListner::subscribeTo(QString subscribe)
{
    if (tcpSocket->isOpen())
    {
    qDebug()<<"Sending Data"<< subscribe;

    QTextStream stream(tcpSocket);
    stream <<subscribe;
    }

}

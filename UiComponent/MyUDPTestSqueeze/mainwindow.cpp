#include "mainwindow.h"
#include "ui_mainwindow.h"

QByteArray Datastr[]={"43"};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initSocket();

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::initSocket()
 {
    qDebug()<<"Init Socket";
    udpSocket = new QUdpSocket(this);
    bool res;
    res=udpSocket->bind(9000, QUdpSocket::ShareAddress);
    connect(udpSocket, SIGNAL(readyRead()),this, SLOT(readPendingDatagrams()));
    qDebug()<<"connected/listning"<<" result:"<<res;

 }
void MainWindow::readPendingDatagrams()
{
   //qDebug()<<"Navdata package recieved :-) ";
    while (udpSocket->hasPendingDatagrams())
   {

        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        udpSocket->readDatagram(datagram.data(), datagram.size(),
                                &sender, &senderPort);
        qDebug()<<"rx data";
        qDebug()<<"data recieved :-) size"<<datagram.size()<<" Data0; 0x"<<datagram.toHex()<<" str"<<datagram.data();
   }
}



void MainWindow::Send_Array_to_server()
{
    QHostAddress reciever;
    int res=0;
    reciever=QHostAddress::QHostAddress("255.255.255.255");
  /*  "e",                                                           -- new discovery packet
            'IPAD', string.char(0x00),                                     -- request IP address of server
            'NAME', string.char(0x00),                                     -- request Name of server
            'JSON', string.char(0x00),                                     -- request JSONRPC port
            'VERS', string.char(0x00),                                     -- request version
            'UUID', string.char(0x00),                                     -- request uuid
            'JVID', string.char(0x06, 0x12, 0x34, 0x56, 0x78, 0x12, 0x34), -- My ID - FIXME mac of no use!*/
    QByteArray str="6549504144004e414d45004a534f4e00564552530055554944004a56494406123456781234";

    QByteArray data= QByteArray::fromHex(str);
    //data = {0x65,0x49,0x50,0x41,0x44,0x00,0x4e,0x41,0x4d,0x45,0x00,0x4a,0x53,0x4f,0x4e,0x00,0x56,0x45,0x52,0x53,0x00,0x55,0x55,0x49,0x44,0x00,0x4a,0x56,0x49,0x44,0x06,0x12,0x34,0x56,0x78,0x12,0x34};
            //"eIPAD.NAME.JSON.";//e"+"IPAD"+"NAME"+"JSON"+"VERS"+"UUID";//'JVID';//+char(0x06)+ char(0x12) +char(0x34)+ char(0x56) +char(0x78)+ char(0x12)+ char(0x34);//QByteArray::fromHex(Datastr[currentDatagram]);

    //data=Datastr[i].toInt(&ok,16);
    res=udpSocket->writeDatagram(data,reciever,3483);
    qDebug()<<"Sending data  on port: 3483 result:"<<res;
}


void MainWindow::on_pushButton_clicked()
{
    Send_Array_to_server();
}

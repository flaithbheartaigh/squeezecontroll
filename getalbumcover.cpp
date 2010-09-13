#include "getalbumcover.h"

GetAlbumCover::GetAlbumCover(QObject *parent):
        QObject(parent)
{
    ready_for_request=true;
    http = new QHttp(this);

    connect(http, SIGNAL(done(bool)),
            this, SLOT(getImage(bool)));
    connect(http, SIGNAL(responseHeaderReceived(QHttpResponseHeader)),
            this, SLOT(readResponseHeader(QHttpResponseHeader)));

    albumArt = new QPixmap(":/icon/NoCover.jpg");
    qDebug()<<"Connecting to http server";
}
GetAlbumCover::~GetAlbumCover()
{

}
void GetAlbumCover::getCurrentAlbumCover(QString ip_addr, int port_nr,QString path)
{

    if (ready_for_request)
    {

        ready_for_request=false;
        http->setHost(ip_addr,port_nr);
        http->get(path);
        qDebug()<<"Senden Get request to "<<path;
    }

}
void GetAlbumCover::getImage(bool error)
{
    QByteArray myArray;

    qDebug()<<"Receiving data ERROR state="<<error;

    if (!error) {
        QImage image;
        if (image.loadFromData(http->readAll())) {
            QPixmap pixmap = QPixmap::fromImage(image);
            emit sendCurrentAlbumCover(&pixmap);
        }
    }
    ready_for_request=true;
}
void GetAlbumCover::readResponseHeader(const QHttpResponseHeader &responseHeader)
{
    qDebug()<<"Got Header info "<<responseHeader.statusCode();
    if (responseHeader.hasKey("Content-Type"))
    {
        qDebug()<<"Got Content Type"<<responseHeader.value("Content-Type");
        if (responseHeader.value("Content-Type")=="image/jpeg")
        {
            qDebug()<<"Image Size="<<responseHeader.value("Content-Length");
            if (responseHeader.value("Content-Length").toInt()>700000)
            {
                http->abort();
                emit sendCurrentAlbumCover(albumArt);
            }
        }


    }
    else
        http->abort();
}

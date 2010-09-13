#ifndef GETALBUMCOVER_H
#define GETALBUMCOVER_H

#include <QObject>
#include <QHttp>
#include <QDebug>
#include <QPixmap>

class GetAlbumCover : public QObject
{
Q_OBJECT
public:
    GetAlbumCover(QObject *parent);
    ~GetAlbumCover();

void getCurrentAlbumCover(QString ip_addr,int port_nr,QString path);

private:
bool ready_for_request;
QPixmap *albumArt;
QHttp *http;

public slots:
void getImage(bool error);
void readResponseHeader(const QHttpResponseHeader &responseHeader);

signals:
    void sendCurrentAlbumCover(QPixmap *p);


};
#endif // GETALBUMCOVER_H

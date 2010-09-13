/*
    Copyright (C) 2010 Michael Rahr

    This file is part of SqueezeRemote.

    SqueezeRemote is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License.

    SqueezeRemote is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with SqueezeRemote.  If not, see <http://www.gnu.org/licenses/>.
*/


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

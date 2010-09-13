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


#ifndef SQUEEZECLI_H
#define SQUEEZECLI_H

#include <QObject>
#include <QTcpSocket>
#include <QtDebug>
#include <QMessageBox>
#include <QFile>
#include "database_struct.h"


class squeezeCli : public QObject
{
Q_OBJECT
public:
    squeezeCli(QObject *parent,QString mIpaddr,QString mPortNr);
    ~squeezeCli();

    bool connect();
    bool closeConnection();
    void getTotalAlbum();
    void getTotalArtists();
    void getTotalSongs();
    void getAlbum(QString Nr_of_album);
    void getAlbumFromto(QString mStart,QString mEnd);
    bool isConnected();
    void play();
    void stop();
    void pause();
    void mode();
    void time();
    void genre();
    void artist();
    void album();
    void title();
    void duration();
    void remote();
    void current_title();
    void path();
    void playlist_play(QString CommandStr,QString fadein);
    void playlist_add(QString CommandStr);
    void playlist_insert(QString CommandStr);
    void playlist_loadalbum(QString CommandStr);
    void playlist_addalbum(QString CommandStr);
    void playlist_loadtracks(QString CommandStr);
    void playlist_addtracks(QString CommandStr);
    void playlist_insertalbum(QString CommandStr);
    void playlist_clear();
    void playlist_zap();
    void playlist_name();
    void playlist_url();
    void playlist_playlistsinfo();
    void playlist_artist();
    void playlist_album();
    void playlist_title();
    void playlist_path();
    void playlist_remote();
    void playlist_duration();
    void playlist_tracks();
    void playlist_shuffle();
    void playlist_repeat();
    void playlist_index(QString index);
    void player_count();
    void player_name(QString index);
    void player_id(QString index);
    void player_uid(QString index);
    void player_ip(QString index);
    void player_model(QString index);
    void status();
    void statusTrack(QString command);
    void search(QString CommandStr);
    void power(QString command);
    void volume(QString command);
    void addData(QString datatosend);
    void sendData();
    void favorites(QString mStart,QString mEnd);
    void setConnectionData(QString mIpAddr,QString mPortNr);




private:
    QTcpSocket *tcpSocket;
    QString ip_addr;
    QString port_nr;
    bool ok_to_send;
    bool readyToSend;
    int total_albums;
    bool connected;
    QList<allAlbum> allAlbums;
    QList<QString> sendBuffer;
    allAlbum myAlbum;

    void displayError(QAbstractSocket::SocketError socketError);


    QString getCommand(QString text);
    int getNumber(QString text);
    void analyzeAlbums(QString text);
    QString getAlbumID(QString text);
    QString getAlbumName(QString text);
private slots:
    void readData();
    void disConnected();

signals:
    void sendString(QString datastring);










};


#endif // SQUEEZECLI_H

/*
 Copyright 2010 Michael Rahr

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

#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <QtSql>
#include <QSqlError>
#include "database_struct.h"
class QSqlQueryModel;

class dataBaseHandler : public QObject
{
public:
    dataBaseHandler(QObject *parent = 0);
     ~dataBaseHandler();
     //Table operations
     bool openDB();                         //Opens database
     bool deleteDB();                       //Removes the actual db file
     bool createTables();                   //Creates album and track tavles and indicies
     void deleteTabel();                    //Deletes tables and indicies

     //Album operations
     int insertAlbum( QString visiblename, QString realname);       //Adds an album to the database
     int Update(QString album,QString path);                        //Adds a "path" to the album given by Album "VisibleName"
     QString getCoverPath(QString album);                           //retrieve the cover path from album
     QString getAlbumId(QString album);                             //Gets album unique ID by "VisibleName"
     void deleteAlbum(QString album);                               //Deletes the album and all the tracks fro that album
     int albumTrackCount(QString albumId);                          //Identifies the amount os tracks on an album

     //Album clustered operation
     void getAlbums(QList<allAlbum> *p);
     void getArtist(QList<allAlbum> *p);

     //Track operations
     void getTracksByAlbum(QString albumId, QList<allTrackInfo> *p);
     //QSqlQueryModel* getTracksByAlbum(int albumId);
     void setTracksByAlbum(int albumId, QStringList albumInfo );

     void syncDatabase(QList<allAlbum> *p);
     QSqlError lastError();
     allAlbum myAlbum;

 private:
     QSqlDatabase db;


};

#endif // DATABASEHANDLER_H

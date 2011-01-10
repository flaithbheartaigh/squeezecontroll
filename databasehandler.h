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

#include <QObject>
#include <QSqlDatabase>
 #include <QSqlRecord>
#include <QSqlError>
#include <QSqlQuery>
#include <QFile>
#include <QtDebug>
#include <qvariant.h>
#include "database_struct.h"
class dataBaseHandler : public QObject
{
public:
    dataBaseHandler(QObject *parent = 0);
     ~dataBaseHandler();
     bool openDB();
     bool deleteDB();
     bool deleteTabel();
     bool createPersonTable();
     int insertAlbum(int id, QString visiblename, QString realname);
     int Update(int albumID,QString album,QString path);
     QString getCoverPath(QString album);
     QString getAlbumId(QString album);
     void syncDatabase(QList<allAlbum> *p);
     void getAlbums(QList<allAlbum> *p);
     void getArtist(QList<allAlbum> *p);
     QSqlError lastError();
     allAlbum myAlbum;

 private:
     QSqlDatabase db;


};

#endif // DATABASEHANDLER_H

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

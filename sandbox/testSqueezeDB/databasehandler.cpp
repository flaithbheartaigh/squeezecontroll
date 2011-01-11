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

#include "databasehandler.h"
#include "database_struct.h"
#include <QMessageBox>
#include <QtSql>

dataBaseHandler::dataBaseHandler(QObject *parent)
{
}

dataBaseHandler::~dataBaseHandler()
{
}

bool dataBaseHandler::createTables()
{    // Create table "person"
    bool ret = false;
    if (db.isOpen())
    {
        QSqlQuery query;
        if(!query.exec("create table albums"
                         "(id integer primary key, "                         
                         "VisibleName varchar(30), "
                         "RealName varchar(30) unique,    "
                         "albumPath varchar(60),   "
                         "albumArtist varchar(30), "
                         "Mark bool) "))
            return(ret);
        if(!query.exec("create table tracks"                         
                         "(albumId integer, "
                         "trackNo integer, "
                         "trackName varchar(30), "
                         "trackTime varchar(5), "
                         "constraint track1 foreign key (albumId) references albums(id) on delete cascade)"))
            return(ret);

        if(!query.exec("CREATE INDEX idIndex ON tracks (albumId)"))
            qDebug() << "Create index on tracks failed";

    }
    return ret;
}

void dataBaseHandler::getTracksByAlbum(const QString albumId, QList<allTrackInfo> *p)
{
    QSqlQuery q1;
    q1.prepare("select * from tracks where albumId = ? order by trackNo asc");
    q1.bindValue(0,albumId);
    q1.exec();
    qDebug()<<"Get Tracks from album";
    allTrackInfo myTracks; // = new allTrackInfo();
    //allTrackInfoList* p = new allTrackInfoList();

    while (q1.next())
    {
        QString albumId= q1.value(0).toString();
        QString trackNo = q1.value(1).toString();
        QString trackName = q1.value(2).toString();
        QString trackTime = q1.value(3).toString();
        myTracks.albumId = albumId;
        myTracks.trackName = trackName;
        myTracks.trackNo = trackNo;
        myTracks.trackTime = trackTime;

        p->append(myTracks);
        qDebug() << "getTracksByAlbum: " << albumId <<" " << trackNo << " " << trackName << " " << trackTime;
    }
    //return p;
}

void dataBaseHandler::setTracksByAlbum(int albumId, QStringList albumInfo )
{

    foreach (QString str, albumInfo) {
        QStringList values = str.split(";", QString::SkipEmptyParts);
        QSqlQuery query;
        //make sql statement with values[0..4]
        query.prepare("INSERT INTO tracks (albumId, trackNo, trackName, trackTime) VALUES (:id, :trackNo, :trackName,:trackTime)");
        query.bindValue(":id",albumId);
        query.bindValue(":trackNo",values[0]);
        query.bindValue(":trackName",values[1]);
        query.bindValue(":trackTime",values[2]);
        qDebug()<<"Adding track="<< values[0]<<"Name="<<values[1]<<" Time="<< values[2];
        if(!query.exec())
        {
            qFatal("Failed to add track to album");
        }
        qDebug() << "Success";
    }

}

int dataBaseHandler::insertAlbum(QString visiblename, QString realname)
{

    bool ret = false;
    if (db.isOpen())
    {
        //http://www.sqlite.org/autoinc.html
        // NULL = is the keyword for the autoincrement to generate next value
        QSqlQuery query;
        //INSERT INTO test1(rowid, a, b) VALUES(NULL, 'ole', 'hello');
        QString sqlStatement = QString("INSERT INTO albums(id,VisibleName,RealName) values(NULL,'%1','%2')").arg(visiblename).arg(realname);
        ret = query.exec(sqlStatement);
    }
    return ret;
}

int dataBaseHandler::Update(QString album, QString path)
{
    bool ret = false;

    qDebug()<<"Update album art path to ="<<path<<" Album VisibleName="<<album;

    if (db.isOpen())
    {
        //http://www.sqlite.org/autoinc.html
        // NULL = is the keyword for the autoincrement to generate next value
        QSqlQuery query;
        query.prepare("update albums set albumPath = ? where VisibleName = ?");
        query.addBindValue(path);
        query.addBindValue(album);
        return query.exec();
    }
    return ret;
}

QString dataBaseHandler::getCoverPath(QString album)
{
    if (db.isOpen())
    {

        QSqlQuery query("select albumPath from albums where VisibleName = ?");
        query.bindValue(0,album);
        query.exec();
        query.first();
        qDebug()<<"Album Path="<<query.value(0).toString();
        return query.value(0).toString();

    }
  return "";
}

QString dataBaseHandler::getAlbumId(QString album)
{


    if (db.isOpen())
    {

        QSqlQuery query("select id from albums where VisibleName = ?");
        query.bindValue(0,album);
        query.exec();
        query.first();
        qDebug()<<"Album ID="<<query.value(0).toString();
        return query.value(0).toString();

    }
  return "";
}

void dataBaseHandler::deleteAlbum(QString album)
{
    if(db.isOpen())
    {
        QSqlQuery query("DELETE FROM albums where VisibleName = ?");
        query.bindValue(0,album);
        if(!query.exec())
            qDebug()<<"Deleting Album: " << album << " from the current database failed";
    }
}

int dataBaseHandler::albumTrackCount(QString albumId)
{
    int rowCount = 0;
    QSqlQuery query("select * FROM tracks where albumId = ?");
    query.bindValue(0,albumId);
    if(query.exec())
    {
        while (query.next()){
            rowCount++;
        }
    }
    return rowCount;
}

bool dataBaseHandler::openDB()
{    // Find QSLite driver
    db = QSqlDatabase::addDatabase("QSQLITE");
#ifdef Q_OS_SYMBIAN
    db.setDatabaseName("music.db.sqlite");
#else
    db.setDatabaseName("music.db.sqlite");
#endif
    //db.setDatabaseName(":memory:");


    if (!db.open()) {
        QMessageBox::critical(0, ("Cannot open database"),
                              ("Unable to establish a database connection.\n"
                                       "You will not be able to sync against SqueezeServer \n "
                                       ), QMessageBox::Cancel);

    }
    return db.open();
}

QSqlError dataBaseHandler::lastError()
{    // If opening database has failed user can ask     // error description by
    // error description by QSqlError::text()

    qDebug()<<"Database Error="<<db.lastError();

    return db.lastError();
}

bool dataBaseHandler::deleteDB()
{    // Close database
    db.close();
#ifdef Q_OS_LINUX    // NOTE: We have to store database file into user home folder in Linux
    QString path(QDir::home().path());
    path.append(QDir::separator()).append("my.db.sqlite");
    path = QDir::toNativeSeparators(path);
    return QFile::remove(path);
#else     // Remove created database binary file
    return QFile::remove("music.db.sqlite");
#endif
}

//allAlbumList* dataBaseHandler::getAlbums(void)
void dataBaseHandler::getAlbums(QList<allAlbum> *p)
{
    QSqlQuery q1("SELECT * FROM albums order by VisibleName asc");
    qDebug()<<"Get albums from database";
    //allAlbumList* p = new allAlbumList();

    while (q1.next())
    {
        allAlbum myAlbum;// = new allAlbum();
        QString id= q1.value(0).toString();
        QString visName = q1.value(1).toString();
        QString relName = q1.value(2).toString();
        QString albumPath = q1.value(3).toString();
        QString albumArtist = q1.value(4).toString();
        //bool Mark = q1.value(5).toBool();
        myAlbum.id=id;
        myAlbum.albumName=visName;
        myAlbum.albumRealName=relName;
        myAlbum.albumArtPath=albumPath;
        myAlbum.albumArtist=albumArtist;
        p->append(myAlbum);
        qDebug()<<id<<" "<<relName<<" "<<visName<<" "<<albumPath<<" "<<albumArtist;
    }
    //return p;
}

//allAlbumList* dataBaseHandler::getArtist()
void dataBaseHandler::getArtist(QList<allAlbum> *p)
{
    QSqlQuery q1("SELECT * FROM albums order by albumArtist asc");
    qDebug()<<"Get albums from database";
    //allAlbumList* p = new allAlbumList();

    while (q1.next())
    {
        allAlbum myAlbum;// = new allAlbum();
        QString id= q1.value(0).toString();
        QString visName = q1.value(1).toString();
        QString relName = q1.value(2).toString();
        QString albumPath = q1.value(3).toString();
        QString albumArtist = q1.value(4).toString();
        myAlbum.id=id;
        myAlbum.albumName=visName;
        myAlbum.albumRealName=relName;
        myAlbum.albumArtPath=albumPath;
        myAlbum.albumArtist=albumArtist;
        p->append(myAlbum);
        qDebug()<<id<<" "<<relName<<" "<<visName<<" "<<albumPath<<" "<<albumArtist;
    }
    //return p;
}

void dataBaseHandler::deleteTabel()
{
    QSqlQuery query;

    if(!query.exec("DELETE FROM albums")) //Clear all albums from database
        qDebug()<<"Deleting Album from the current database";
    if(!query.exec("DELETE FROM tracks")) //Clear all albums from database
        qDebug()<<"Deleting Tracks from the current database";
    if(!query.exec("DROP INDEX idIndex ON tracks"))
        qDebug() << "Drop index on itemTags failed";
}

void dataBaseHandler::syncDatabase(QList<allAlbum> *p)
{
    qDebug()<<"Starting the sync process";
    qDebug()<<"elements in array"<<p->count();
    QSqlQuery query;    
    QSqlQuery query_temp;
    int a;
    //First create a temporary table with all the albums from the squeeze
    // and L Join is then used to delete the albums from the album table that is not in the new squeeze table
    if(!query.exec("create table temp_albums"
                     "(id integer primary key, "
                     "VisibleName varchar(30), "
                     "RealName varchar(30) unique,    "
                     "albumPath varchar(60),   "
                     "albumArtist varchar(30) )"))
        qDebug() << "error in creating temp_albums. Not fatal " << db.lastError();

    if (db.transaction())
    {        
        query.prepare("INSERT INTO albums  (id, VisibleName, RealName,albumPath,albumArtist) VALUES (NULL, :visiblename, :realname,:path, :albumartist)");
        query_temp.prepare("INSERT INTO temp_albums  (id, VisibleName, RealName,albumPath,albumArtist) VALUES (NULL, :visiblename, :realname,:path, :albumartist)");

        qDebug()<<"Albums to sync"<<p->count();
        int mydebug=0;

        for (a=0;a<p->count();a++)

        {
            //query.bindValue(":id",NULL);
            query.bindValue(":visiblename", QVariant(p->at(a).albumName));
            query.bindValue(":realname", QVariant(p->at(a).albumRealName));
            query.bindValue(":path","");
            query.bindValue(":albumartist",QVariant(p->at(a).albumArtist));

            query_temp.bindValue(":visiblename", QVariant(p->at(a).albumName));
            query_temp.bindValue(":realname", QVariant(p->at(a).albumRealName));
            query_temp.bindValue(":path","");
            query_temp.bindValue(":albumartist",QVariant(p->at(a).albumArtist));

            if(!query.exec())
            {
                qDebug()<<"Failed to add album nr="<<mydebug++<<"Name="<<p->at(a).albumName<<" Album Artist="<<p->at(a).albumArtist;
                //qFatal("Failed to add album");

            }

            if(!query_temp.exec())
            {
                qDebug()<<"Failed to add temp_album nr="<<mydebug++<<"Name="<<p->at(a).albumName<<" Album Artist="<<p->at(a).albumArtist;
                //qFatal("Failed to add temp_album");

            }
            qDebug()<<"album nr="<<mydebug++<<"Name="<<p->at(a).albumName<<" Album Artist="<<p->at(a).albumArtist;
        }



//        QSqlQuery q("select * from albums");
//        QSqlRecord rec = q.record();
//        rec.clearValues();
//        qDebug() << "Number of columns: " << rec.count();
//
//        QSqlQuery q1("SELECT * FROM albums");
//        int fieldNo = q1.record().indexOf("visiblename");
//        int num=0;
//
//        while (q1.next()) {
//            QString country = q1.value(fieldNo).toString();
//            qDebug()<<num++<<country;
//        }
        db.commit();
    }

    //if(!updateQuery.exec("UPDATE albums LEFT JOIN temp_albums ON albums.VisibleName = temp_albums.VisibleName SET Mark = 'True' WHERE (((temp_albums.VisibleName) Is Null));"))
    if(!query.exec("SELECT albums.VisibleName, temp_albums.VisibleName FROM albums LEFT JOIN temp_albums ON albums.VisibleName = temp_albums.VisibleName WHERE ((temp_albums.VisibleName) Is Null)"))
        qDebug() << "Updating albums with obsolete titles failed";
    while(query.next())
    {
        QString deleteAlbum;
        QString tempAlbum;
        deleteAlbum = query.value(0).toString();
        tempAlbum = query.value(1).toString();
        QString mySql = QString("DELETE FROM albums WHERE albums.Visiblename = '%0'").arg(deleteAlbum);
        QSqlQuery deleteQuery(mySql);

        if(deleteQuery.exec())
            qDebug()<< "Deleting the album: " << deleteAlbum;

    }


    if(!query.exec("DROP TABLE temp_albums"))
        qDebug() << "Last error = " << db.lastError();

}

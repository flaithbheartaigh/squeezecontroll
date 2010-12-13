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
                         "RealName varchar(30),    "
                         "albumPath varchar(60),   "
                         "albumArtist varchar(30) )"))
            return(ret);
        if(!query.exec("create table tracks"                         
                         "albumId integer, "
                         "trackNo integer, "
                         "trackName varchar(30), "
                         "trackTime varchar(5) )"))
            return(ret);

        if(!query.exec("CREATE INDEX idIndex ON tracks (albumId)"))
            qDebug() << "Create index on tracks failed";
    }
    return ret;
}

QSqlQueryModel* dataBaseHandler::getTracksByAlbum(int albumId)
{
    QSqlQuery tracksByAlbum;
    if(db.isOpen()){
        tracksByAlbum.prepare("select * from tracks where albumId = ?");
        tracksByAlbum.bindValue(0,albumId);
        QSqlQueryModel* retModel = new QSqlQueryModel();
        retModel->setQuery(tracksByAlbum);
        return(retModel);
    }
    return(NULL);
}

void dataBaseHandler::setTracksByAlbum(int albumId, QStringList albumInfo )
{
    //Delete the tracks if any at first???
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

int dataBaseHandler::insertAlbum(int id, QString visiblename, QString realname)
{

    bool ret = false;
    if (db.isOpen())
    {
        //http://www.sqlite.org/autoinc.html
        // NULL = is the keyword for the autoincrement to generate next value
        QSqlQuery query;
        ret = query.exec(QString("update albums values('%0','%1','%2')")
                         .arg(id).arg(visiblename).arg(realname));         // Get database given autoincrement value

    }
    return ret;
}

int dataBaseHandler::Update(int albumID, QString album, QString path)
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

void dataBaseHandler::getAlbums(QList<allAlbum> *p)
{
    QSqlQuery q1("SELECT * FROM albums order by VisibleName asc");
    qDebug()<<"Get albums from database";
    
    while (q1.next())
    {
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
}

void dataBaseHandler::getArtist(QList<allAlbum> *p)
{
    QSqlQuery q1("SELECT * FROM albums order by albumArtist asc");
    qDebug()<<"Get albums from database";

    while (q1.next())
    {
        QString id= q1.value(0).toString();
        QString visName = q1.value(1).toString();
        QString relName = q1.value(2).toString();
        QString albumPath = q1.value(3).toString();
        QString albumArtist = q1.value(4).toString();
        myAlbum.id=id;
        myAlbum.albumName=albumArtist;
        myAlbum.albumRealName=relName;
        myAlbum.albumArtPath=albumPath;
        myAlbum.albumArtist=visName;
        p->append(myAlbum);
        qDebug()<<id<<" "<<relName<<" "<<visName<<" "<<albumPath<<" "<<albumArtist;
    }
}

bool dataBaseHandler::deleteTabel()
{
    QSqlQuery query;
    bool del=query.exec("DELETE FROM albums"); //Clear all albums from database
            qDebug()<<"Deleting the current database"<<del;
            return del;
}

void dataBaseHandler::syncDatabase(QList<allAlbum> *p)
{
    qDebug()<<"Starting the sync process";
    qDebug()<<"elements in array"<<p->count();
    QSqlQuery query;
    QSqlRecord qrecord;

    int a;

    if (db.transaction())
    {
//        bool del=query.exec("DELETE FROM albums"); //Clear all albums from database
//        qDebug()<<"Deleting the current database"<<del;




        query.prepare("INSERT INTO albums  (id, VisibleName, RealName,albumPath,albumArtist) VALUES (:id, :visiblename, :realname,:path, :albumartist)");

        qDebug()<<"Albums to sync"<<p->count();
        int mydebug=0;

        for (a=0;a<p->count();a++)

        {


            query.bindValue(":id",QVariant(p->at(a).id));
            query.bindValue(":visiblename", QVariant(p->at(a).albumName));
            query.bindValue(":realname", QVariant(p->at(a).albumRealName));
            query.bindValue(":path","");
            query.bindValue(":albumartist",QVariant(p->at(a).albumArtist));

//qDebug()<<"ID="<<p->at(1).id;
//            query.bindValue(":id",p->at(a).id);
//            query.bindValue(":visiblename", "dewd");
//            query.bindValue(":realname", "de");

            if(!query.exec())
            {
                qDebug()<<"album nr="<<mydebug++<<"Name="<<p->at(a).albumName<<" Album Artist="<<p->at(a).albumArtist;
                qFatal("Failed to add album");

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

}

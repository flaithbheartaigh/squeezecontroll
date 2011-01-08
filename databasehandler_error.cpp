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

dataBaseHandler::dataBaseHandler(QObject *parent)
{
}

dataBaseHandler::~dataBaseHandler()
{
}

bool dataBaseHandler::createPersonTable()
{    // Create table "person"
    bool ret = false;    if (db.isOpen())
    {
        QSqlQuery query;
        ret = query.exec("create table albums"
                         "(id integer primary key, "
                         "VisibleName varchar(30), "
                         "RealName varchar(30))");
    }
    return ret;
}

int dataBaseHandler::insertAlbum(int id, QString visiblename, QString realname)
{

    bool ret = false;
    if (db.isOpen())
    {
        //http://www.sqlite.org/autoinc.html
        // NULL = is the keyword for the autoincrement to generate next value
        QSqlQuery query;
        ret = query.exec(QString("insert into albums values('%0','%1','%2')")
                         .arg(id).arg(visiblename).arg(realname));         // Get database given autoincrement value

    }
    return ret;
}



bool dataBaseHandler::openDB()
{    // Find QSLite driver
    db = QSqlDatabase::addDatabase("QSQLITE");
#ifdef Q_OS_LINUX    // NOTE: We have to store database file into user home folder in Linux
    QString path(QDir::home().path());    path.append(QDir::separator()).append("my.db.sqlite");
    path = QDir::toNativeSeparators(path);    db.setDatabaseName(path);
#else    // NOTE: File exists in the application private folder, in Symbian Qt implementation
    db.setDatabaseName("music.db.sqlite");
    //db.setDatabaseName(":memory:");
#endif     // Open databasee
    return db.open();
}

QSqlError dataBaseHandler::lastError()
{    // If opening database has failed user can ask     // error description by
    // error description by QSqlError::text()
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
    QSqlQuery q1("SELECT * FROM albums");

    int num=0;
    while (q1.next())
    {
        QString id= q1.value(0).toString();
        QString visName = q1.value(1).toString();
        QString relName = q1.value(2).toString();
        myAlbum.id=id;
        myAlbum.albumName=visName;
        myAlbum.albumRealName=relName;
        p->append(myAlbum);
        qDebug()<<id<<" "<<relName<<" "<<visName;
    }
}

void dataBaseHandler::syncDatabase(QList<allAlbum> *p)
{
    qDebug()<<"elements in array"<<p->count();
    QSqlQuery query;
    QSqlRecord qrecord;

    int a;

    if (db.transaction())
    {
    bool del=query.exec("DELETE FROM albums"); //Clear all albums from database
    qDebug()<<del;




    query.prepare("INSERT INTO albums  (id, VisibleName, RealName) "
                  "VALUES (:id, :visiblename, :realname)");

qDebug()<<"Albums to sync"<<p->count();
int mydebug=0;
for (a=0;a<p->count();a++)

    {


        query.bindValue(":id",QVariant(p->at(a).id));
        query.bindValue(":visiblename", QVariant(p->at(a).albumName));
        query.bindValue(":realname", QVariant(p->at(a).albumRealName));
        query.exec();
        qDebug()<<"album nr="<<mydebug++;
    }

         QSqlQuery q("select * from albums");
         QSqlRecord rec = q.record();
         rec.clearValues();
         qDebug() << "Number of columns: " << rec.count();

          QSqlQuery q1("SELECT * FROM albums");
          int fieldNo = q1.record().indexOf("visiblename");
          int num=0;

          while (q1.next()) {
             QString country = q1.value(fieldNo).toString();
             qDebug()<<num++<<country;
         }
      db.commit();
      }

}

#include <QtGui/QApplication>
#include "database_struct.h"
#include "databasehandler.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    dataBaseHandler* myMusic;
    QList<allAlbum> allAlbums;
    bool databaseResult = false;

    myMusic = new dataBaseHandler(NULL);
    databaseResult=myMusic->openDB();    qDebug()<<"Database open result="<<databaseResult;
    if (databaseResult!=true)qFatal("DataBase not open");
    databaseResult=myMusic->createTables();
    qDebug()<<"Database create result="<<databaseResult;
    // databaseResult=myMusic->Update(1,"hjkhjk","c:/test/bla");
    //myMusic->getCoverPath("Abbey Road");
    qDebug()<<"Database Update result="<<databaseResult;
    myMusic->getAlbums(&allAlbums);
    //upDateAlbumList();

    return a.exec();
}

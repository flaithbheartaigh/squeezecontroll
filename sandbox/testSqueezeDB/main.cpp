#include <QtGui/QApplication>
#include "database_struct.h"
#include "databasehandler.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    dataBaseHandler* myMusic;
    QList<allAlbum> allAlbums;
    QList<allTrackInfo> allTracks;
    bool databaseResult = false;

    myMusic = new dataBaseHandler(NULL);
    databaseResult=myMusic->openDB();    qDebug()<<"Database open result="<<databaseResult;
    if (databaseResult!=true)qFatal("DataBase not open");
    databaseResult=myMusic->createTables();    
    qDebug()<<"Database create result="<<databaseResult;
    myMusic->insertAlbum("Ole","Ole Madsen");
    databaseResult=myMusic->Update("Ole","c:/test/bla");
    QString albumId = myMusic->getAlbumId("Ole");
    QStringList myTracks;
    myTracks << "1; Track1; 13:10";
    myTracks << "2; Track2; 14:10";
    myTracks << "3; Track3; 15:10";
    myTracks << "4; Track4; 16:10";
    myMusic->setTracksByAlbum(albumId.toInt(), myTracks);
    qDebug() << "Number of tracks in Ole = " << myMusic->albumTrackCount(albumId);
    //myMusic->getCoverPath("Abbey Road");
    qDebug()<<"Database Update result="<<databaseResult;
    myMusic->getAlbums(&allAlbums);
    myMusic->getTracksByAlbum(albumId, &allTracks);
    //Delete the album and see if the tracks are still there
    myMusic->deleteAlbum("Ole");
    //Can you see the album still?
    albumId = myMusic->getAlbumId("Ole");
    qDebug() << "Number of tracks in Ole = " << myMusic->albumTrackCount(albumId);
    myMusic->getTracksByAlbum(albumId, &allTracks);
    //upDateAlbumList();

    return a.exec();
}

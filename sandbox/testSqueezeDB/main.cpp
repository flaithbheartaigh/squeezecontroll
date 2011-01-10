#include <QtGui/QApplication>
#include "database_struct.h"
#include "databasehandler.h"

QList<allAlbum> allTempAlbums;
QList<allAlbum> allAlbums;
QList<allTrackInfo> allTracks;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    dataBaseHandler* myMusic;
    bool databaseResult = false;

    myMusic = new dataBaseHandler(NULL);
    databaseResult=myMusic->openDB();    qDebug()<<"Database open result="<<databaseResult;
    if (databaseResult!=true)qFatal("DataBase not open");
    databaseResult=myMusic->createTables();    
    qDebug()<<"Database create result="<<databaseResult;
    myMusic->insertAlbum("Ole","Ole Madsen");
    myMusic->insertAlbum("Ole","Ole Madsen");
    //Adding several albums with same name to see if they are ignored as there is already one
    //I have added a UNIQUE to realName in the album table, so we avoid duplicates
    myMusic->insertAlbum("Ole","Ole Madsen");
    myMusic->insertAlbum("Peter","Peter Madsen");

    myMusic->insertAlbum("Annie","Annie Madsen");
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
    //delete allTracks;
    //Delete the album and see if the tracks are still there
    myMusic->deleteAlbum("Ole");
    //Can you see the album still?
    albumId = myMusic->getAlbumId("Ole");
    qDebug() << "Number of tracks in Ole = " << myMusic->albumTrackCount(albumId);
    myMusic->getTracksByAlbum(albumId, &allTracks);
    //upDateAlbumList();
    //Sync the database
    myMusic->insertAlbum("Ole","Ole Madsen"); // So we have Ole, Peter & Annie in table

    allAlbum myAlbum;
    myAlbum.albumName = "Annie";
    myAlbum.albumRealName = "Annie Madsen";
    allTempAlbums.append(myAlbum);
    myAlbum.albumName = "Peter";
    myAlbum.albumRealName = "Peter Madsen";
    allTempAlbums.append(myAlbum);
    myAlbum.albumName = "John";
    myAlbum.albumRealName = "John Madsen";   //New member is John and Ole is gone from Squeeze
    allTempAlbums.append(myAlbum);
    myMusic->syncDatabase(&allTempAlbums);
    allAlbums.clear();
    myMusic->getAlbums(&allAlbums);
    albumId = myMusic->getAlbumId("Ole"); //Should be missing now
    qDebug() << "Number of tracks in Ole = " << myMusic->albumTrackCount(albumId);
    myMusic->getTracksByAlbum(albumId, &allTracks);
    return a.exec();
}

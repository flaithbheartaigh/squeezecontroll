#include "squeezeboxhelper.h"
#include <qdebug.h>

squeezeboxHelper::squeezeboxHelper(QObject *parent) :
        QObject(parent)
{
}

squeezeboxHelper::~squeezeboxHelper()
{
}

QString squeezeboxHelper::getSqueezeboxCommand(QString text)
{

    QString player_id="";
    QString new_command_string="";

    qDebug()<<text;


    qDebug()<<"Number of char="<<text.length()<<text[0];
    qDebug()<<"Number of commands="<<squeezeCommands->count();

    new_command_string=text.mid(0,text.indexOf(" ",1));
    //new_command_string=text;
    qDebug()<<new_command_string;

    for (int a=0;a<12;a++)
    {

        if (new_command_string.contains(squeezeCommands[a]))
        {

            if (squeezeCommands[a]=="player")
            {
            for(int a=0;a<4;a++)
              if (text.contains(squeezeSubCommands[a]))
              return "player "+squeezeSubCommands[a];
            }

            if (squeezeCommands[a]=="info")
            {
            for(int a=0;a<3;a++)
              if (text.contains(squeezeInfoSubCommands[a]))
              return "info "+squeezeInfoSubCommands[a];
            }

            if (squeezeCommands[a]=="favorites")
            {
                for(int a=0;a<1;a++)
                  if (text.contains(squeezeFavSubCommands[a]))
                  return squeezeFavSubCommands[a];
            }



         return squeezeCommands[a];
        }

    }


    return("");

}

//*****************************************************
//Helper functions
int squeezeboxHelper::getNumber(QString text)
{
    QString command;
    int a;
    bool ok;
    int startpos=0;


    if ((text[0]=='%') || ((text[0]>='0')&&(text[0]<='9')))
        startpos=text.indexOf(" ")+1;

    for (a=startpos;a<text.length();a++)
    {


        if (((text[a]>='0')&&(text[a]<='9')))
            command+=text[a];

    }

    qDebug()<<command;
    return(command.toInt(&ok,10));

}
void squeezeboxHelper::analyzeAlbums(QString text,QList<allAlbum> *p)
{
    int numberOfAlbums;
    int album1,album2,albumCount,count,textPos,len;
    QString album;
    numberOfAlbums=text.count("album%",Qt::CaseSensitive);


    count=0;
    albumCount=0;
    while (albumCount<numberOfAlbums)
    {
        album1=text.indexOf("id%",count);
        album2=text.indexOf("id%",album1+3);
        if (albumCount==numberOfAlbums-1)
            album2=text.indexOf(" count",album1+3);
        album=text.mid(album1,(album2-album1));

        count=album2;




        myAlbum.albumName=getAlbumName(album);


        textPos=album.indexOf("album%3A")+8;
        len=album.indexOf(" ",textPos);
        myAlbum.albumRealName=album.mid(textPos,len-textPos);

        textPos=album.indexOf("artist%3A")+9;
        len=album.indexOf(" ",textPos);
        myAlbum.albumArtist=removeBadChar(album.mid(textPos,len-textPos));

        myAlbum.id=getAlbumID(album);




        if ((myAlbum.albumName!="")&&(myAlbum.albumRealName!="")&&(myAlbum.albumArtist!="")&&(myAlbum.id!=""))
            p->append(myAlbum);
        else
            qDebug()<<"Allbum error on "<<myAlbum.albumArtist<<myAlbum.albumName<<myAlbum.id<<myAlbum.id;


        albumCount++;

    }


}
void squeezeboxHelper::analyzeFav(QString text, QList<allAlbum> *p)
{
    int numberOfAlbums;
    int album1,album2,albumCount,count,textPos,len;
    QString album;
    numberOfAlbums=text.count("id%",Qt::CaseSensitive);


    count=0;
    albumCount=0;
    while (albumCount<numberOfAlbums)
    {
        album1=text.indexOf("id%",count);
        album2=text.indexOf("id%",album1+3);
        if (albumCount==numberOfAlbums-1)
            album2=text.indexOf(" count",album1+3);

        album=text.mid(album1,(album2-album1));
        count=album2;




        textPos=album.indexOf("name%3A")+7;
        len=album.indexOf(" ",textPos);
        myAlbum.albumName=removeBadChar(album.mid(textPos,len-textPos));

        textPos=album.indexOf("id%3A")+5;
        len=album.indexOf(" ",textPos);
        myAlbum.id=album.mid(textPos,len-textPos);

        p->append(myAlbum);
        albumCount++;

    }


}
void squeezeboxHelper::analyzeTrack(QString text,QList<allAlbum> *p)
{
    int numberOfTrack;
    int track1,track2,trackCount,count;
    QString trackTitle;
    QString interMidiateString;

    p->clear();
    track1=text.indexOf("playlist_tracks%3A",Qt::CaseSensitive)+18;
    track2=text.indexOf(" ",track1);

    interMidiateString=text.mid(track1,track2-track1);
    numberOfTrack=interMidiateString.toInt();


    count=0;
    trackCount=0;
    qDebug()<<"Track Text="<<text;
    while (trackCount<numberOfTrack)
    {
        track1=text.indexOf("playlist%20index%3A"+QString::number(trackCount)); //find the track index in the string
        track2=text.indexOf("title%3A",track1); //find the title index for the current track index
        track1=text.indexOf(" ",track2);
        trackTitle=text.mid(track2+8,(track1-(track2+8)));
        qDebug()<<"Track Number="<<trackCount<<" "<<trackTitle;
        qDebug()<<"Track ok"<<removeBadChar(trackTitle);

        myAlbum.albumName=removeBadChar(trackTitle);
        myAlbum.albumRealName="";
        myAlbum.id="";


        p->append(myAlbum);


        trackCount++;

    }



}
void squeezeboxHelper::StatusUpdate(QString text,SqueezeStatus *status)
{
    QString status_field;
    int textPos,len;
    float perc;

    textPos=text.indexOf("player_name%3A")+14;
    status_field=text.mid(textPos,text.indexOf(" ",textPos)-textPos);
    status->playerName=status_field;
    qDebug()<<"Player name"<<status_field;

    textPos=text.indexOf("player_connected")+19;
    len=text.indexOf(" ",textPos);
    status->playerConnected=text.mid(textPos,len-textPos);
    qDebug()<<"Player Connected"<<status->playerConnected;

    textPos=text.indexOf("player_ip%3A")+12;
    len=text.indexOf("%3A",textPos);
    status->playerIp=text.mid(textPos,len-textPos);
    qDebug()<<"Player IP"<<status->playerIp;

    textPos=text.indexOf("mode%3A")+7;
    len=text.indexOf(" ",textPos);
    status->playerMode=text.mid(textPos,len-textPos);
    qDebug()<<"Player mode"<<status->playerMode;

    textPos=text.indexOf("power%3A")+8;
    len=text.indexOf(" ",textPos);
    status->playerStatus=text.mid(textPos,len-textPos);
    qDebug()<<"Player mode"<<status->playerMode;

    textPos=text.indexOf("mixer%20volume%3A")+17;
    len=text.indexOf(" ",textPos);
    status->current_volumen=(text.mid(textPos,len-textPos).toInt());
    qDebug()<<"Player Volumen"<<status->current_volumen;



    textPos=text.indexOf("playlist_tracks%3A")+18;
    len=text.indexOf(" ",textPos);
    status->playListTrack=text.mid(textPos,len-textPos);
    qDebug()<<"Player Tracks"<<status->playListTrack;

    textPos=text.indexOf("title%3A")+8;
    len=text.indexOf(" ",textPos);
    status->currentTitle=removeBadChar(text.mid(textPos,len-textPos));

    qDebug()<<"Current Title"<<status->currentTitle;

    textPos=text.indexOf("playlist_cur_index%3A")+21;
    len=text.indexOf(" ",textPos);
    status->playlistCurrentIndex=text.mid(textPos,len-textPos).toInt()+1;
    qDebug()<<"Current Index "<<status->playlistCurrentIndex;

    textPos=text.indexOf("power%3A")+8;
    len=text.indexOf(" ",textPos);
    status->current_power_state=text.mid(textPos,len-textPos).toInt();
    qDebug()<<"Current Power State "<<status->current_power_state;

    textPos=text.indexOf("artist%3A")+9;
    len=text.indexOf(" ",textPos);
    status->artist=removeBadChar(text.mid(textPos,len-textPos));
    status->currentArtist=status->artist;
    qDebug()<<"Artist "<<status->artist;

    textPos=text.indexOf("album%3A")+8;
    len=text.indexOf(" ",textPos);
    status->album=removeBadChar(text.mid(textPos,len-textPos));
     status->currentAlbum=status->album;
    qDebug()<<"Album "<<status->album;

    textPos=text.indexOf("playlist%20repeat%3A")+20;
    len=text.indexOf(" ",textPos);
    status->playListRepeat=removeBadChar(text.mid(textPos,len-textPos));
    qDebug()<<"playListRepeat "<<status->playListRepeat;

    textPos=text.indexOf("playlist%20shuffle%3A")+21;
    len=text.indexOf(" ",textPos);
    status->playListShuffle=removeBadChar(text.mid(textPos,len-textPos));
    qDebug()<<"playListShuffle "<<status->playListShuffle;

    textPos=text.indexOf("time%3A")+7;
    len=text.indexOf(" ",textPos);
    status->time=text.mid(textPos,len-textPos).toFloat();
    qDebug()<<"Time "<<status->time;

    textPos=text.indexOf("duration%3A")+11;
    len=text.indexOf(" ",textPos);
    status->duration=text.mid(textPos,len-textPos).toInt();
    qDebug()<<"duration "<<status->duration;

    perc=(100/status->duration)*status->time;
    qDebug()<<"Song played in perc="<<perc;
    status->playedInPerc=perc;

    textPos=text.indexOf("showBriefly%3A")+14;
    if (textPos>13)
    {
        len=text.indexOf(" ",textPos);
        status->playerShowB=text.mid(textPos,len-textPos);
        status->showBr=removeBadChar(status->playerShowB);

    }



}

void squeezeboxHelper::analyzeStatus(QString text,QList<allAlbum> *p,SqueezeStatus *status)
{
    QString status_field;
    int textPos,len;

    textPos=text.indexOf("player_name%3A")+14;
    status_field=text.mid(textPos,text.indexOf(" ",textPos)-textPos);
    qDebug()<<"Player name"<<status_field;

    textPos=text.indexOf("player_connected")+19;
    len=text.indexOf(" ",textPos);
    status->playerConnected=text.mid(textPos,len-textPos);
    qDebug()<<"Player Connected"<<status->playerConnected;

    textPos=text.indexOf("player_ip%3A")+12;
    len=text.indexOf("%3A",textPos);
    status->playerIp=text.mid(textPos,len-textPos);
    qDebug()<<"Player IP"<<status->playerIp;

    textPos=text.indexOf("mode%3A")+7;
    len=text.indexOf(" ",textPos);
    status->playerMode=text.mid(textPos,len-textPos);
    qDebug()<<"Player mode"<<status->playerMode;


    textPos=text.indexOf("mixer%20volume%3A")+17;
    len=text.indexOf(" ",textPos);
    status->current_volumen=(text.mid(textPos,len-textPos).toInt());
    qDebug()<<"Player Volumen"<<status->current_volumen;

    textPos=text.indexOf("artist%3A")+9;
    len=text.indexOf(" ",textPos);
    status->artist=removeBadChar(text.mid(textPos,len-textPos));
    status->currentArtist=status->artist;
    qDebug()<<"Artist "<<status->artist;

    textPos=text.indexOf("album%3A")+8;
    len=text.indexOf(" ",textPos);
    status->album=removeBadChar(text.mid(textPos,len-textPos));
    status->currentAlbum=status->album;
    qDebug()<<"Album "<<status->album;

    textPos=text.indexOf("playlist_tracks%3A")+18;
    len=text.indexOf(" ",textPos);
    status->playListTrack=text.mid(textPos,len-textPos);
    qDebug()<<"Player Tracks"<<status->playListTrack;

    textPos=text.indexOf("playlist_cur_index%3A")+21;
    len=text.indexOf(" ",textPos);
    status->playlistCurrentIndex=text.mid(textPos,len-textPos).toInt()+1;
    qDebug()<<"Current Index "<<status->playlistCurrentIndex;

    textPos=text.indexOf("power%3A")+8;
    len=text.indexOf(" ",textPos);
    status->current_power_state=text.mid(textPos,len-textPos).toInt();
    qDebug()<<"Current Power State "<<status->current_power_state;



    textPos=text.indexOf("showBriefly%3A")+14;
    if (textPos>13)
    {
        len=text.indexOf(" ",textPos);
        status->playerShowB=text.mid(textPos,len-textPos);
        status->showBr=removeBadChar(status->playerShowB);

        //qDebug()<<statusbar;
        //qDebug()<<"Playeing now"<<removeBadChar(playerShowB);
    }

    if (text.count("id%")>0)
        analyzeTrack(text,p);

}
void squeezeboxHelper::anslyzeSearch(QString text,QList<SqueezeSearchAlbum> *Album,QList<SqueezeSearchTrack> *Track,QList<SqueezeSearchContributor> *Contributor)
{
    qDebug()<<"Searching command found";
    qDebug()<<text;

    int numberOfAlbums,count;
    int album1,album2,albumCount,id1,id2;
    QString album,id;
    numberOfAlbums=text.count("album_id%3A",Qt::CaseSensitive);


    count=0;
    album1=0;
    id1=0;
    albumCount=0;
    Album->clear();

    while (albumCount<numberOfAlbums)
    {
        album1=text.indexOf("album%3A",album1+albumCount);
        album2=text.indexOf(" ",album1+3);

        id1=text.indexOf("album_id%3A",id1+albumCount);
        id2=text.indexOf(" ",id1+3);

        album=text.mid(album1,(album2-album1));

        id=text.mid(id1+11,(id2-(id1+11)));



        album_Search.albumName=getAlbumName(album);
        album_Search.albumId=id;
        qDebug()<<"Album Name="<<album_Search.albumName;
        qDebug()<<"Album ID="<<album_Search.albumId;
        Album->append(album_Search);


        albumCount++;

    }


    numberOfAlbums=text.count("contributor_id%3A",Qt::CaseSensitive);

    count=0;
    album1=0;
    id1=0;
    albumCount=0;
    Contributor->clear();

    while (albumCount<numberOfAlbums)
    {
        album1=text.indexOf("contributor%3A",album1+albumCount);
        album2=text.indexOf(" ",album1+3);
        if (album2==-1)album2=text.count();

        id1=text.indexOf("contributor_id%3A",id1+albumCount);
        id2=text.indexOf(" ",id1+3);
        if (id2==-1)id2=text.count();

        album=text.mid(album1,(album2-album1));

        id=text.mid(id1+17,(id2-(id1+17)));



        contributor_Search.ContributorName=getAlbum(album,"contributor%3A");
        contributor_Search.ContributorId=id;
        qDebug()<<"Contributor Name="<<contributor_Search.ContributorName;
        qDebug()<<"Contributor ID="<<contributor_Search.ContributorId;
        Contributor->append(contributor_Search);


        albumCount++;

    }
 numberOfAlbums=text.count("track_id%3A",Qt::CaseSensitive);
    count=0;
    album1=0;
    id1=0;
    albumCount=0;
    Track->clear();

    while (albumCount<numberOfAlbums)
    {
        album1=text.indexOf("track%3A",album1+albumCount);
        album2=text.indexOf(" ",album1+3);
        if (album2==-1)album2=text.count();

        id1=text.indexOf("track_id%3A",id1+albumCount);
        id2=text.indexOf(" ",id1+3);
        if (id2==-1)id2=text.count();

        album=text.mid(album1,(album2-album1));

        id=text.mid(id1+11,(id2-(id1+11)));



        track_Search.trackName=getAlbum(album,"track%3A");
        track_Search.trackId=id;
        qDebug()<<"Track Name="<<track_Search.trackName;
        qDebug()<<"Track ID="<<track_Search.trackId;
        Track->append(track_Search);


        albumCount++;

    }



}
QString squeezeboxHelper::getAlbumName(QString text)
{
    QString albumName,string1,command;
    bool ok;
    int a,start,index;
    start=text.indexOf("album%3A")+8;

    index=start;
    for (a=start;a<text.length();a++)
    {

        if (text[a]=='%')
        {
            string1=text.mid(a+1,2);
            if (string1=="C3")
            {
                string1=text.mid(a+4,2);
                if (string1=="86") {string1="Æ";}
                if (string1=="A6") {string1="æ";}
                if (string1=="98") {string1="Ø";}
                if (string1=="B8") {string1="ø";}
                if (string1=="85") {string1="Å";}
                if (string1=="A5") {string1="å";}
                a=a+3;
            }
            else
                string1=(char) string1.toInt(&ok,16);

            command+=string1;
            a=a+2;
        }
        else if(text[a]==' ') break;
        else
            command+=text[a];
    }

    return(command);
}
QString squeezeboxHelper::removeBadChar(QString text)
{
    QString albumName,string1,command;
    bool ok;
    int a;
    command="";
    for (a=0;a<text.length();a++)
    {

        if (text[a]=='%')
        {

            string1=text.mid(a+1,2);
            if (string1=="C3")
            {
                string1=text.mid(a+4,2);
                if (string1=="86") {string1="Æ";}
                if (string1=="A6") {string1="æ";}
                if (string1=="98") {string1="Ø";}
                if (string1=="B8") {string1="ø";}
                if (string1=="85") {string1="Å";}
                if (string1=="A5") {string1="å";}
                a=a+3;
            }
            else
            string1=(char) string1.toInt(&ok,16);

            command+=string1;
            a=a+2;
        }
        else if(text[a]==' ') break;
        else
            command+=text[a];
    }

    return(command);
}
QString squeezeboxHelper::getAlbum(QString text,QString scrStr)
{
    bool ok;
    int start,index;
    QString string1,command;
    start=text.indexOf(scrStr)+scrStr.length();

    index=start;
    for (int a=start;a<text.length();a++)
    {

        if (text[a]=='%')
        {
            string1=text.mid(a+1,2);
            if (string1=="C3")
            {
                string1=text.mid(a+4,2);
                if (string1=="86") {string1="Æ";}
                if (string1=="A6") {string1="æ";}
                if (string1=="98") {string1="Ø";}
                if (string1=="B8") {string1="ø";}
                if (string1=="85") {string1="Å";}
                if (string1=="A5") {string1="å";}
                a=a+3;
            }
            else
            string1=(char) string1.toInt(&ok,16);

            command+=string1;
            a=a+2;
        }

        else
            command+=text[a];
    }

    return(command);
}
QString squeezeboxHelper::getAlbumID(QString text)
{
    int a;
    QString command;
    for (a=5;a<text.length();a++)
    {


        if (((text[a]>='0')&&(text[a]<='9')))
            command+=text[a];
        else break;


    }

    return(command);
}



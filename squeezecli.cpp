#include "squeezecli.h"
#include <QtGui>


squeezeCli::squeezeCli(QObject *parent,QString mIpaddr,QString mPortNr)
    :QObject ( parent )
{
    port_nr=mPortNr;
    ip_addr=mIpaddr;
    tcpSocket = new QTcpSocket(this);
    ok_to_send=true;
    readyToSend=true;
    QObject::connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readData()));
    QObject::connect(tcpSocket, SIGNAL(disconnected()),this,SLOT(disConnected()));

}

squeezeCli::~squeezeCli()
{
    if (tcpSocket->isOpen())
        tcpSocket->close();
}
void squeezeCli::setConnectionData(QString mIpAddr, QString mPortNr)
{
    port_nr=mPortNr;
    ip_addr=mIpAddr;
}

bool squeezeCli::connect()
{
    bool ret;
    ret=false;
   connected=false;
    tcpSocket->abort();
    tcpSocket->connectToHost(ip_addr,port_nr.toInt());

    if (tcpSocket->waitForConnected(1000))
    {
        ret=true;
        qDebug("Connected!");
        connected=true;
    }



    return ret;
}
bool squeezeCli::isConnected()
{
    return(tcpSocket->isOpen());

}
bool squeezeCli::closeConnection()
{
    bool ret;
    ret=false;

    return ret;

}
void squeezeCli::disConnected()
{
    tcpSocket->close();
    connected=false;

}

void squeezeCli::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        //        QMessageBox::information(this, tr("Fortune Client"),
        //                                 tr("The host was not found. Please check the "
        //                                    "host name and port settings."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        //        QMessageBox::information(this, tr("Fortune Client"),
        //                                 tr("The connection was refused by the peer. "
        //                                    "Make sure the fortune server is running, "
        //                                    "and check that the host name and port "
        //                                    "settings are correct."));
        break;

        //        QMessageBox::information(this, tr("Fortune Client"),
        //                                 tr("The following error occurred: %1.")
        //                                 .arg(tcpSocket->errorString()));
    default: ;
    }


}
void squeezeCli::readData()
{
    QString text,text1,command;
    text="";

    while (tcpSocket->canReadLine())
    {
        text1 = tcpSocket->readLine();
        text =text+ text1;
        //        qDebug()<<"readline="<<text1;
    }
    //  qDebug()<<" ";
    // qDebug()<<"Server Data "<<text;
    emit sendString(text);
    ok_to_send=true;
    readyToSend=true;
    sendData();




}

QString squeezeCli::getCommand(QString text)
{
    int a;
    QString command;
    qDebug()<<text;


    qDebug()<<"Number of char="<<text.length();
    for (a=0;a<text.length();a++)
    {

        if ((text[a]>='a') && (text[a]<='y') )
            command+=text[a];
        if ((text[a]=='%') || ((text[a]>='0')&&(text[a]<='9')))
            break;
    }

    qDebug()<<command;
    return(command);
}

int squeezeCli::getNumber(QString text)
{
    QString command;
    int a;
    bool ok;

    for (a=0;a<text.length();a++)
    {


        if (((text[a]>='0')&&(text[a]<='9')))
            command+=text[a];

    }

    qDebug()<<command;
    return(command.toInt(&ok,10));

}

void squeezeCli::getTotalAlbum()
{

    addData("info total albums ?\n");

}

void squeezeCli::getTotalArtists()
{


    addData("info total artists ?\n");
}
void squeezeCli::getTotalSongs()
{
    addData("info total songs ?\n");
}
void squeezeCli::getAlbum(QString Nr_of_album)
{
    addData("albums 0 "+Nr_of_album+" tags:al\n");
}
void squeezeCli::getAlbumFromto(QString mStart, QString mEnd)
{
 addData("albums "+mStart+" "+mEnd+" tags:al\n");
}

void squeezeCli::analyzeAlbums(QString text)
{
    int numberOfAlbums;
    int album1,album2,albumCount,count;
    QString album;
    numberOfAlbums=text.count("id%",Qt::CaseSensitive);




    //allAlbum *albumdata = allAlbums.data();

    count=0;
    albumCount=0;
    while (albumCount<numberOfAlbums)
    {
        album1=text.indexOf("id%",count);
        album2=text.indexOf("id%",album1+3);
        album=text.mid(album1,(album2-album1));

        count=album2;

        myAlbum.albumName=getAlbumName(album);
        myAlbum.albumRealName=album.mid(album.indexOf("album%3A")+8,album.length());
        myAlbum.id=getAlbumID(album);
        allAlbums.append(myAlbum);

        albumCount++;

    }

    qDebug()<<"Album Array Count="<<allAlbums.count();


}

QString squeezeCli::getAlbumID(QString text)
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

QString squeezeCli::getAlbumName(QString text)
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
            string1=(char) string1.toInt(&ok,16);
            command+=string1;
            a=a+2;
        }
        else
            command+=text[a];
    }
    return(command);
}

//New command implemented
void squeezeCli::play()
{
    addData("play\n");
}
void squeezeCli::pause()
{
    addData("pause\n");
}
void squeezeCli::stop()
{
    addData("stop\n");
}
void squeezeCli::mode()
{
    addData("mode ?\n");
}
void squeezeCli::time()
{
    addData("time ?\n");
}
void squeezeCli::genre()
{
    addData("genre ?\n");
}
void squeezeCli::artist()
{
    addData("artist ?\n");
}
void squeezeCli::album()
{
    addData("album ?\n");
}
void squeezeCli::title()
{
    addData("title ?\n");
}
void squeezeCli::duration()
{
    addData("duration ?\n");
}
void squeezeCli::remote()
{
    addData("remote ?\n");
}
void squeezeCli::current_title()
{
    addData("current_title ?\n");
}
void squeezeCli::path()
{
    //TBD
}
void squeezeCli::playlist_play(QString CommandStr,QString fadein)
{
    addData("playlist play "+CommandStr+" "+fadein+"\n");
}
void squeezeCli::playlist_add(QString CommandStr)
{
    addData("playlist add "+CommandStr+"\n");
}
void squeezeCli::playlist_insert(QString CommandStr)
{
    addData("playlist add "+CommandStr+"\n");
}
void squeezeCli::playlist_loadalbum(QString CommandStr)
{
    addData("playlist loadalbum * * "+CommandStr+"\n");
}
void squeezeCli::playlist_addalbum(QString CommandStr)
{
    addData("playlist addalbum "+CommandStr+"\n");
}
void squeezeCli::playlist_loadtracks(QString CommandStr)
{
    addData("playlist loadtracks "+CommandStr+"\n");
}
void squeezeCli::playlist_addtracks(QString CommandStr)
{
    addData("playlist addtracks "+CommandStr+"\n");
}
void squeezeCli::playlist_insertalbum(QString CommandStr)
{
    addData("playlist insertalbum "+CommandStr+"\n");
}
void squeezeCli::playlist_clear()
{
    addData("playlist clear\n");
}
void squeezeCli::playlist_zap()
{
    //TBD
}
void squeezeCli::playlist_name()
{
    //TBD
}
void squeezeCli::playlist_url()
{
    //TBD
}
void squeezeCli::playlist_playlistsinfo()
{
    addData("playlist playlistsinfo\n");
}
void squeezeCli::playlist_artist()
{
    //TBD
}
void squeezeCli::playlist_album()
{
    //TBD
}
void squeezeCli::playlist_title()
{
    //TBD
}
void squeezeCli::playlist_path()
{
    //TBD
}
void squeezeCli::playlist_remote()
{
    //TBD
}
void squeezeCli::playlist_duration()
{
    //TBD
}
void squeezeCli::playlist_tracks()
{
    addData("playlist tracks ?\n");
}
void squeezeCli::playlist_shuffle()
{
    addData("playlist shuffle ?\n");
}
void squeezeCli::playlist_repeat()
{
    addData("playlist repeat ?\n");
}
void squeezeCli::player_count()
{
    addData("player count ?\n");
}
void squeezeCli::player_id(QString index)
{
    addData("player id "+index+" ?\n");
}
void squeezeCli::player_ip(QString index)
{
    addData("player ip "+index+" ?\n");
}
void squeezeCli::player_model(QString index)
{
    addData("player model "+index+" ?\n");
}
void squeezeCli::player_name(QString index)
{
    addData("player name "+index+" ?\n");
}
void squeezeCli::player_uid(QString index)
{
    addData("player uid "+index+" ?\n");
}
void squeezeCli::favorites(QString mStart, QString mEnd)
{
 addData("favorites items "+mStart+" "+mEnd+"\n");
}

void squeezeCli::status()
{
    addData("status\n");
}
void squeezeCli::statusTrack(QString command)
{
    addData("status 0 "+command+"\n");
    //addData("status 0 14\n");
}
void squeezeCli::playlist_index(QString index)
{
    addData("playlist index "+index+"\n");
}
void squeezeCli::power(QString command)
{
    addData("power "+command+"\n");
}
void squeezeCli::volume(QString command)
{

    addData("mixer volume "+command+"\n");
}
void squeezeCli::search(QString CommandStr)
{
    addData("search 0 100 term:"+CommandStr+"\n");
}

void squeezeCli::addData(QString datatosend)
{
    sendBuffer.append(datatosend);
    sendData();

}

void squeezeCli::sendData()
{

qDebug()<<"Server connection="<<isConnected();
    if (connected)
    {

        if ((readyToSend==true)&&(sendBuffer.count()>0))
        {
            qDebug()<<"Sending Data"<<"DataBuffer Count="<<sendBuffer.count();
            QTextStream stream(tcpSocket);
            QString databuffer = sendBuffer.takeFirst();

            qDebug()<<"data to send="<<databuffer;
            stream <<databuffer;
            readyToSend=false;
        }
    }
    else
     if(connect())
         sendData();

}

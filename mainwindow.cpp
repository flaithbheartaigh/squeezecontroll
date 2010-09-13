/*
    Copyright (C) 2010 Michael Rahr

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


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString.h>
#include <QBitmap>
#include "squeezeboxhelper.h"
#include <QtNetwork>
#ifdef Q_OS_SYMBIAN
//#include "sym_iap_util.h"
#include <PathInfo.h>
#endif

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    //*************************************************
    //Check and set network connection

    QNetworkConfigurationManager manager;
    const bool selectIap = (manager.capabilities()& QNetworkConfigurationManager::CanStartAndStopInterfaces);
    QNetworkConfiguration defaultIap = manager.defaultConfiguration();
    if(!defaultIap.isValid() && (!selectIap && defaultIap.state() != QNetworkConfiguration::Active))
    {        // let the user know that there is no access point available
    }
        session = new QNetworkSession(defaultIap,this);
        session->open();

#ifdef Q_OS_SYMBIAN




    //qt_SetDefaultIap();
    // Get the root path of Phone Memory.
    TFileName path = PathInfo::MemoryCardRootPath();

    QString myString = QString::fromUtf16(path.Ptr(), path.Length());
    qDebug()<<"Path for phone ="<<myString;

    QDir dir(myString+"squeezedata");
    if (!dir.exists(myString+"squeezedata"))
    {
        dir.mkdir(myString+"squeezedata");
        qDebug()<<"Dir did not exists we created it";
    }
    qDebug()<<"Setting current path="<<dir.setCurrent(myString+"squeezedata");

#else
    QDir dir("c:/squeezedata");
    if (!dir.exists("c:/squeezedata"))
    {
        dir.mkdir("c:/squeezedata");
        qDebug()<<"Dir did not exists we created it";
    }
    qDebug()<<"Setting current path="<<dir.setCurrent("c:/squeezedata");
#endif

    //*************************************************
    currentView="Album List";
    bool databaseResult;
    ui->setupUi(this);
    qDebug()<<"Working dir="<<QDir::currentPath();
    curIndex=0;
    getSettings();
    upDateUI();
    ui->sync->hide();
    albumArt=new QPixmap();
    maxFav="300";                                                           //hardcoded max number of favorites, TODO. fix this
    playmode=mode_album;
    mySqueezeHelper = new squeezeboxHelper(this);
    t = new QTimer( this );
    connect( t, SIGNAL(timeout()), SLOT(removePanel()));

    UITimeout = new QTimer( this );
    connect( UITimeout, SIGNAL(timeout()), SLOT(startAniTimer()));


    UIInsertPanelTimer = new QTimer( this );
    connect( UIInsertPanelTimer, SIGNAL(timeout()), SLOT(insertPanel()));

    //************************************'
    //init
    state=s_none;
    get_track=false;
    networkGroup=false;
    ignor_volume_command=false;
    curIndex=0;
    nowLabel="playing Now";
    resetStatus();

    myMusic = new dataBaseHandler(this);
    databaseResult=myMusic->openDB();    qDebug()<<"Database open result="<<databaseResult;
    if (databaseResult!=true)qFatal("DataBase not open");
    databaseResult=myMusic->createPersonTable();
    qDebug()<<"Database create result="<<databaseResult;
    // databaseResult=myMusic->Update(1,"hjkhjk","c:/test/bla");
    //myMusic->getCoverPath("Abbey Road");
    qDebug()<<"Database Update result="<<databaseResult;
    myMusic->getAlbums(&allAlbums);
    upDateAlbumList();

    ui->ListTrack->setBackgroundColor(QColor(0,0,0));
    ui->ListTrack->setTextColor(QColor(220, 215, 218));
    ui->ListTrack->setSelectedColor(QColor(91, 81, 111));
    ui->ListTrack->setHighLightedColor(QColor(91, 81, 111));

    ui->myList->setNumOfTextToDisplay(2);

    myClihandler = new squeezeCli(this,ip_addr,port_nr);
    mySqueezeListner = new squeezeListner(this,ip_addr,port_nr);
    mySqueezeListner->subscribeTo("status - 1 subscribe:5\n");
    myAlbumCover = new GetAlbumCover(this);

    //************************************
    //Connections
    connect(myClihandler,SIGNAL(sendString(QString)),this,SLOT(receiveString(QString)));
    connect(mySqueezeListner,SIGNAL(sendStatus(QString)),this,SLOT(receiveStatus(QString)));
    //connect(ui->albumlist,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(playItem(QListWidgetItem*)));

    //connect(ui->nowTrackList,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(playTrack(QListWidgetItem*)));
    connect(ui->ListTrack,SIGNAL(doubleClick(int)),this,SLOT(playTrack(int)));
    connect(ui->stackedWidget,SIGNAL(currentChanged(int)),this,SLOT(widgetChanged(int)));
    connect(ui->myList,SIGNAL(doubleClick(int)),this,SLOT(flickPlayAlbum(int)));

    connect(ui->myList,SIGNAL(endOfScroll(int)),this,SLOT(end_of_offset(int)));
    connect(ui->myList,SIGNAL(longPress(int)),this,SLOT(longPress(int)));


    if(connect(myAlbumCover,SIGNAL(sendCurrentAlbumCover(QPixmap*)),this,SLOT(on_receive_albumcover(QPixmap*))))
        qDebug()<<"Album cover signal ok";
    else
        qDebug()<<"ERROR on signal";


    if (myClihandler->connect())
        qDebug()<<"Connection ok";
    else
        qDebug()<<"No connection";


    get_track=true;
    getServerStatus();
    ui->stackedWidget->setCurrentIndex(curIndex);
    myAlbumCover->getCurrentAlbumCover(ip_addr,http_port_nr.toInt(),"/music/current/cover.jpg");


    //All connection
    //**********************************************************************************
    //Setting up animation for ControlPanel
    animation = new QPropertyAnimation(ui->ControlBox, "geometry");
    animation->setDuration(150);
    animation->setStartValue(QRect(0, 0, 360, 91));
    animation->setEndValue(QRect(0, -91, 360, 91));

    insertAnimation=new QPropertyAnimation(ui->ControlBox, "geometry");
    insertAnimation->setDuration(150);
    insertAnimation->setStartValue(QRect(0, -91, 360, 91));
    insertAnimation->setEndValue(QRect(0, 0, 360, 91));

    networkGroupAnimation = new QPropertyAnimation(ui->Network,"geometry");
    networkGroupAnimation->setDuration(150);
    networkGroupAnimation->setStartValue(QRect(10,120,341,35));
    networkGroupAnimation->setEndValue(QRect(10,120,341,320));

    squeezeCenterGroupAnimation= new QPropertyAnimation(ui->SqueezeCenter,"geometry");
    squeezeSyncAnimation= new QPropertyAnimation(ui->sync,"geometry");

    //**********************************************************************************

    ui->Network->setGeometry      (10,120,341,35);
    ui->SqueezeCenter->setGeometry(10,170,341,35);
    getNumberOfPlayers();
    ui->verticalSlider->setMaximum(ui->myList->getScrollListOffset());



    //**********************************************************************************
    //Check network connection before starting, if not connected then go to settings
    //Page and expand the network pane
    if (myClihandler->isConnected())
    {
        qDebug()<<"Connection ok";
        ui->isConnected->setText("Connection ok");
    }
    else
    {
        qDebug()<<"No connection";
        ui->isConnected->setText("Error in connection");
        curIndex=3;
        ui->stackedWidget->setCurrentIndex(curIndex);
        ui->Network->setChecked(true);
        networkGroupAnimation->setStartValue(QRect(10,120,341,35));
        networkGroupAnimation->setEndValue(QRect(10,120,341,341));
        networkGroupAnimation->setDuration(250);
        networkGroupAnimation->start();
        ui->SqueezeCenter->show();
    }


}

MainWindow::~MainWindow()
{
    delete ui;
    delete myMusic;
    delete myClihandler;
    delete mySqueezeHelper;
    delete myAlbumCover;
    delete animation;
    delete insertAnimation;
    delete networkGroupAnimation;
    delete squeezeCenterGroupAnimation;




}


//Mouse handling for swipe between page
void MainWindow::mouseMoveEvent(QMouseEvent *e)
{


    // qDebug()<<"Mouse Position "<<QCursor::pos();
}
void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{

    //    if (QCursor::pos().x()-oldPos.x()>100)
    //       rollwidget(1);
    //    else if (QCursor::pos().x()-oldPos.x()<-100)
    //        rollwidget(0);

    qDebug()<<"Release Pos "<<QCursor::pos();
}
void MainWindow::mousePressEvent(QMouseEvent *e)
{

    oldPos=QCursor::pos();
    qDebug()<<"Press Position"<<QCursor::pos();
    //ui->frame_2->setGeometry(10,570,461,61);
    if (myClihandler->isConnected())
    {
        if (QCursor::pos().y()<70){
            qDebug()<<"in insert panel function";
            if (ui->ControlBox->pos().y()<0)
                insertPanel();
            else

                UITimeout->start(3000);
        }
    }
    else
    {
        if (curIndex!=3)
        {
            curIndex=3;
            ui->stackedWidget->setCurrentIndex(curIndex);
        }
    }

}

//********************************************************
//Control functions
void MainWindow::getServerStatus()
{
    state=s_start;
    myClihandler->artist();
}
void MainWindow::rollwidget(bool dir)
{
    QString number;

    if (dir==true) curIndex++;
    else
        curIndex--;

    if (curIndex<0) curIndex=3;
    if (curIndex>3) curIndex=0;






    upDateUI();
    if (ui->sync->isVisible())ui->sync->hide();
    ui->stackedWidget->setCurrentIndex(curIndex);
    qDebug()<<"Current widget in View="<<curIndex;
}
void MainWindow::getSettings()
{
    QSettings settings("RahrSoft", "SqueezeRemote");
    settings.beginGroup("NETWORK");
    ip_addr = settings.value("ip_addr","127.0.0.1").toString();
    port_nr = settings.value("port_nr","9090").toString();
    http_port_nr = settings.value("http_port_nr","9001").toString();
    autoconnect= settings.value("autoconnect",false).toBool();
    qDebug()<<"Ip_addr="<<ip_addr<<" Port Nr="<<port_nr;
    settings.endGroup();
}
void MainWindow::setSettings()
{
    QSettings settings("RahrSoft", "SqueezeRemote");
    settings.beginGroup("NETWORK");
    settings.setValue("ip_addr", ip_addr);
    settings.setValue("port_nr", port_nr);
    settings.setValue("http_port_nr", http_port_nr);
    settings.setValue("autoconnect",autoconnect);
    settings.endGroup();
    qDebug()<<"set settings"<<"Ip_addr="<<ip_addr<<" Port Nr="<<port_nr;
}
void MainWindow::on_pushButton_clicked()
{
    ip_addr=ui->server_ip->text();
    port_nr=ui->server_port->text();
    http_port_nr=ui->server_port_2->text();
    ui->isConnected->setText("Trying to connect til SQUEEZEBOX");
    ui->centralWidget->repaint();
    autoconnect=ui->server_autoconnect->checkState();
    myClihandler->setConnectionData(ip_addr,port_nr);

    if(myClihandler->connect())
    {
        ui->isConnected->setText("Connected to SQUEEZEBOX on ip "+ip_addr);
        getServerStatus();
    }
    else
        ui->isConnected->setText("Error on connection to ip "+ip_addr);

    mySqueezeListner->connectTo(ip_addr,port_nr);
    mySqueezeListner->subscribeTo("status - 1 subscribe:5\n");
    setSettings();
}
void MainWindow::on_pushButton_2_clicked()
{
    upDateUI();
}
void MainWindow::on_pushButton_3_clicked()
{

    if (myClihandler->isConnected())
    {
        ui->sync->show();
        ui->Network->show();
        ui->SqueezeCenter->show();
        ui->Network->setGeometry(QRect(10,130,341,35));
        ui->SqueezeCenter->setGeometry(QRect(10,170,341,35));
        ui->Network->setChecked(false);
        ui->SqueezeCenter->setChecked(false);
        squeezeSyncAnimation->setEndValue(QRect(10,220,341,291));
        squeezeSyncAnimation->setStartValue(QRect(10,120,341,0));
        squeezeSyncAnimation->setDuration(150);
        squeezeSyncAnimation->start();
        syncDatabase();
    }
}
void MainWindow::upDateUI()
{
    ui->server_ip->setText(ip_addr);
    ui->server_port_2->setText(http_port_nr);
    ui->server_port->setText(port_nr);
    ui->server_autoconnect->setChecked(autoconnect);



}
void MainWindow::upDateUIPage()
{

    qDebug()<<"UI setting Volumen="<<myStatus.current_volumen;
    if (myStatus.current_power_state==0)
    {

        ui->label_6->setText("<h3>Remote Control</h3>"+myStatus.currentAlbum+"<br><b>""</b><br>""</br></font>");
        ui->label_7->setText("<h3>"+currentView+"</h3>"+myStatus.currentAlbum+"<br><b>""</b><br>""</br></font>");

    }
    else
    {

        ui->label_6->setText("<h3>Remote Control</h3>"+myStatus.currentAlbum+"<br><b>"+myStatus.currentTitle+"</b><br>"+myStatus.currentArtist+"</br></font>");
        ui->label_7->setText("<h3>"+currentView+"</h3>"+myStatus.currentAlbum+"<br><b>"+myStatus.currentTitle+"</b><br>"+myStatus.currentArtist+"</br></font>");
        ui->label_8->setText("<h3>Search</h3>"+myStatus.currentAlbum+"<br><b>"+myStatus.currentTitle+"</b><br>"+myStatus.currentArtist+"</br></font>");
        ui->label_9->setText("<h3>Settings Menu</h3>"+myStatus.currentAlbum+"<br><b>"+myStatus.currentTitle+"</b><br>"+myStatus.currentArtist+"</br></font>");
        ui->track_2->setText("Playing "+QString::number(myStatus.playlistCurrentIndex)+" of "+myStatus.playListTrack);
        ui->track_4->setText("Playing "+QString::number(myStatus.playlistCurrentIndex)+" of "+myStatus.playListTrack);
if (myStatus.playerMode=="pause")
    ui->play->setStyleSheet("border-image: url(:/icon/pause.png) 3 3 2 3");
else
    ui->play->setStyleSheet("border-image: url(:/icon/play.png) 3 3 2 3");


    }
    ui->page_3->update();
    ui->ServerName->setText("Server IP: "+ip_addr);
    ui->PlayerName->setText("Player Name: "+myStatus.playerName);
    ui->NumOfPlayer->setText("Number of players: "+QString::number(myStatus.numbers_of_players));
    ui->PlayerIP->setText("Player IP:"+myStatus.playerIp);

    if (myStatus.playerStatus=="1")
        ui->PlayerStatus->setText("Player on");
    else
        ui->PlayerStatus->setText("Player off");

    ui->NumOfArtist->setText("Number of Artist: "+QString::number(myStatus.number_of_artist));
    ui->NumOfAlbums->setText("Number of Albums: "+QString::number(myStatus.number_of_albums));
    ui->NumOfTracks->setText("Number of Tracks: "+QString::number(myStatus.number_of_tracks));
}
void MainWindow::upDateAlbumList()
{
    ui->myList->setList(&allAlbums);
    ui->myList->setBackgroundColor(QColor(0,0,0));
    ui->myList->setTextColor(QColor(220, 215, 218));
    ui->myList->setSelectedColor(QColor(91, 81, 111));
    ui->myList->setHighLightedColor(QColor(91, 81, 111));
    ui->myList->setLineColor(QColor(110,110,110));


    //    ui->albumlist->clear();
    //    for (int a=0;a<allAlbums.count();a++)
    //    {
    //        ui->albumlist->addItem(allAlbums.at(a).albumName);
    //    }


    //ui->albumlist->sortItems(Qt::AscendingOrder);
}
void MainWindow::syncDatabase()
{
    if (!myClihandler->isConnected())
        QMessageBox::information(this, tr("Error"),
                                 tr("Not connected to server "
                                    "Check host name and port settings."));
    else
    {

        int numOfAlbums=myStatus.number_of_albums;
        divider=20;

        answer = div(numOfAlbums,divider);
        numOfIttr=answer.quot;


        if (answer.rem>0)numOfIttr++;
        qDebug()<<"num of ittr="<<numOfIttr;

        ui->progressBar->setMaximum(numOfIttr);
        ui->progressBar->setValue(0);

        myMusic->deleteTabel();
        state=s_sync; //Set the start state
        allAlbums.clear();
        myClihandler->getTotalAlbum();
    }
    //myMusic->syncDatabase(&allAlbums);
}



void MainWindow::nextState()
{
    QString number;
    //State mashine for handling the received signal
    switch (state)
    {
    case s_none:break;
    case s_sync:getAllAlbums();break;
    case s_analyze:
        upDateAlbumList();
        state=s_none;break;
    case s_power:
        {
            if (myStatus.current_power_state==0)
            {
                myClihandler->power("1");
            }
            else
                myClihandler->power("0");

            myClihandler->status();
            state=s_none;
            break;
        }
    case s_start: myClihandler->volume("?");state=s_start2;break;
    case s_start2: myClihandler->album();state=s_start3;break;
    case s_start3: myClihandler->getTotalAlbum();myClihandler->getTotalArtists();myClihandler->getTotalSongs();state=s_start4;break;
    case s_start4: myClihandler->status();
    case s_start5: myClihandler->title();if (get_track==true)state=s_start6;else state=s_none;break;
    case s_start6:
        {
            if (myStatus.playListTrack.toInt()>150) number="150";
            else if(myStatus.playListTrack.toInt()<1) number="150";
            else
                number=myStatus.playListTrack;

            myClihandler->statusTrack(number);
            state=s_none;
            get_track=false;
        }; break;

    }
}




void MainWindow::getAllAlbums()
{

    int a=answer.quot-(numOfIttr-1);
    ui->progressBar->setValue(a);

    if (numOfIttr>1)
    {
        qDebug()<<"from="<<a*divider<<" to="<<divider;
        myClihandler->getAlbumFromto(QString::number(a*divider),QString::number(divider));
    }
    else
    {
        qDebug()<<"from="<<a*divider<<" to="<<answer.rem;
        myClihandler->getAlbumFromto(QString::number(a*divider),QString::number(answer.rem));
    }

    state=s_analyze;
}

void MainWindow::getPlayerInfo()
{
    SqueezePlayer myPlayer;
    QString num;
    for (int a=0;a<myStatus.numbers_of_players;a++)
    {
        num.setNum(a);
        myPlayer.playerCanPowerOff="";
        myPlayer.playerDisplayType="";
        myPlayer.playerID="";
        myPlayer.playerIP="";
        myPlayer.playerIsPlayer="";
        myPlayer.playerModel="";
        myPlayer.playerName="";
        myPlayer.playerUID="";
        myClihandler->player_id(num);
        myClihandler->player_ip(num);
        myClihandler->player_model(num);
        myClihandler->player_name(num);
        myClihandler->player_uid(num);



    }
}
void MainWindow::getNumberOfPlayers()
{
    qDebug()<<"Get numbers of players in system";
    myClihandler->player_count();
}
void MainWindow::resetStatus()
{

    myStatus.number_of_albums=0;
    myStatus.number_of_artist=0;
    myStatus.number_of_tracks=0;
    myStatus.numbers_of_players=0;
    myStatus.playlistCurrentIndex=0;
    myStatus.current_power_state=0;
    myStatus.current_volumen=0;
    myStatus.time=0;
    myStatus.duration=0;
    myStatus.playedInPerc=0;
    myStatus.playedinper=0;
    myStatus.playerName="";
    myStatus.playerStatus="";
    myStatus.playerConnected="";
    myStatus.playerIp="";
    myStatus.playerSignalSt="";
    myStatus.playerMode="";
    myStatus.playTime="";
    myStatus.playListTrack="";
    myStatus.playListRepeat="";
    myStatus.playListShuffle="";
    myStatus.playerShowB="";
    myStatus.currentAlbum="";
    myStatus.currentArtist="";
    myStatus.currentTitle="";
    myStatus.artist="";
    myStatus.album="";
    myStatus.showBr="";
    myStatus.currentAlbumPath="";
}

//********************************************************
//Receiver slot
void MainWindow::receiveString(QString data)
{

    QString command;
    QString player_id;
    qDebug()<<"Received data from Server "<<data;


    //*************************************************************************
    //Get rid of player id, must use this to handle more that one player
    if (data[2]=='%')
        player_id=data.mid(0,data.indexOf(" ",0));

    if (player_id!="")
        data=data.mid(data.indexOf(" ")+1,data.count()-data.indexOf(" ",0));
    //*************************************************************************
    //command=getCommand(data);  //old stuff
    command=mySqueezeHelper->getSqueezeboxCommand(data);
    qDebug()<<"Command to execute="<<command;

    if (command=="info total albums")
    {
        myStatus.number_of_albums=mySqueezeHelper->getNumber(data);
        ui->sync_label->setText("Albums to sync = "+QString::number(myStatus.number_of_albums));
        nextState();
    }
    if (command=="info total artists")
    {
        myStatus.number_of_artist=mySqueezeHelper->getNumber(data);
        nextState();
    }
    if (command=="info total songs")
    {
        myStatus.number_of_tracks=mySqueezeHelper->getNumber(data);
        nextState();
    }
    if (command=="albums")
    {

        mySqueezeHelper->analyzeAlbums(data,&allAlbums);
        qDebug()<<"Number of albums="<<allAlbums.count();
        numOfIttr--;
        if (numOfIttr==0)
        {

            ui->sync_label->setText("Finish");
            ui->progressBar->setValue(ui->progressBar->maximum());
            myMusic->syncDatabase(&allAlbums);
            squeezeSyncAnimation->setStartValue(QRect(10,220,341,291));
            squeezeSyncAnimation->setEndValue(QRect(10,120,341,0));
            squeezeSyncAnimation->setDuration(150);
            squeezeSyncAnimation->start();
            state=s_analyze;
            nextState();
        }
        else
            getAllAlbums();
    }
    if (command=="power")
    {
        myStatus.current_power_state=mySqueezeHelper->getNumber(data);
        qDebug()<<"Current power state="<<myStatus.current_power_state;
        nextState();
    }
    if (command=="status")
    {
        mySqueezeHelper->analyzeStatus(data,&trackListe,&myStatus);
        ui->ListTrack->setList(&trackListe);
        ui->ListTrack->update();
        upDateUIPage();
        nextState();
    }
    if (command=="mixer")
    {

        if (ignor_volume_command==false)
        {
            myStatus.current_volumen=mySqueezeHelper->getNumber(data);
            ui->power->setValue(myStatus.current_volumen);

            ignor_volume_command=true;
        }
        nextState();
    }
    if (command=="album")
    {
        myStatus.currentAlbum=mySqueezeHelper->getAlbum(data," album");
        upDateUIPage();
        nextState();
    }
    if (command=="artist")
    {
        myStatus.currentArtist=mySqueezeHelper->getAlbum(data," artist");
        upDateUIPage();
        nextState();
    }
    if (command=="title")
    {
        myStatus.currentTitle=mySqueezeHelper->getAlbum(data," title");
        upDateUIPage();
        nextState();
    }
    if (command=="search"){

        mySqueezeHelper->anslyzeSearch(data,&searchAlbum,&searchTrack,&searchContributor);
        int a=0;
        while(a<searchAlbum.count())
        {
            ui->album->insertItem(a,searchAlbum.at(a).albumName);
            a++;
        }
        a=0;
        while(a<searchContributor.count())
        {
            ui->contributor->insertItem(a,searchContributor.at(a).ContributorName);
            a++;
        }
        a=0;
        while(a<searchTrack.count())
        {
            ui->trackliste->insertItem(a,searchTrack.at(a).trackName);
            a++;
        }
    }
    if (command=="player count")
    {
        myStatus.numbers_of_players=mySqueezeHelper->getNumber(data);
        getPlayerInfo();
    }
    if (command=="favorites items")
    {
        allFavorites.clear();
        mySqueezeHelper->analyzeFav(data,&allFavorites);
        qDebug()<<"Number of Fav="<<allFavorites.count();
        qDebug()<<"Fav 0"<<allFavorites.at(0).albumName;
        ui->myList->setList(&allFavorites);

    }
}
void MainWindow::receiveStatus(QString data)
{



    int tracks=oldNumOfTracks.toInt();
    mySqueezeHelper->StatusUpdate(data,&myStatus);
    upDateUIPage();
    qDebug()<<"data"<<data;

    qDebug()<<"myStatus tracks="<<myStatus.number_of_tracks;
    //ui->progressBar->setValue(myStatus.playedInPerc);



    QString currentTracks=myStatus.playListTrack;

    if (tracks!=currentTracks.toInt())
    {
        get_track=true;
        getServerStatus();

    }

    if (oldTitle!=myStatus.currentTitle)
    {
        get_track=true;
        getServerStatus();
    }

    if (oldAlbum!=myStatus.album)
    {
        get_track=true;
        getServerStatus();
        QString albumId=myMusic->getAlbumId(myStatus.album);
        QString alBumPath=QDir::currentPath()+"/"+albumId+".jpg";


        if (alBumPath!=myStatus.currentAlbumPath)
        {
            QColor myColor;
            myColor.setRgb(0,0,0);
            albumArt->fill(myColor);
            if (albumArt->load(alBumPath))
            {
                ui->pixture->setPixmap(*albumArt);
                myStatus.currentAlbumPath=alBumPath;
            }
            else //Something whent wrong, images not there, get new image
            {
                myAlbumCover->getCurrentAlbumCover(ip_addr,http_port_nr.toInt(),"/music/current/cover.jpg");
            }
        }
        else
            myAlbumCover->getCurrentAlbumCover(ip_addr,http_port_nr.toInt(),"/music/current/cover.jpg");

    }



    upDateUIPage();
    oldAlbum=myStatus.album;
    oldTitle=myStatus.currentTitle;
    oldNumOfTracks=myStatus.playListTrack;
}


void MainWindow::widgetChanged(int page)
{
    qDebug()<<"Widget change to="<<page;
    //myClihandler->album();
    //myClihandler->artist();

}
void MainWindow::playItem(QListWidgetItem* index)
{
    QString playlist;
    QString number;
    //playlist=allAlbums.at(ui->albumlist->currentRow()).albumRealName;
    playlist=allAlbums.at(ui->myList->getSelected()).id;
    qDebug()<<"album to load "<<playlist;

    QString alBumPath = myMusic->getCoverPath(allAlbums.at(ui->myList->getSelected()).albumName);
    if(alBumPath!="")
    {

    }


    myClihandler->playlist_loadalbum(playlist);
    get_track=true;
    getServerStatus();

    upDateUI();
    curIndex=2;
    ui->stackedWidget->setCurrentIndex(curIndex);



}
void MainWindow::flickPlayAlbum(int index)
{
    QString playlist;
    QString number;
    qDebug()<<"Index="<<index;
    qDebug()<<"Album Count="<<allAlbums.count();
    if (playmode==mode_album)
    {
        if (allAlbums.count()>index)
        {
            playlist=allAlbums.at(index).id;
            qDebug()<<"album to load "<<playlist;

            QString albumId=allAlbums.at(index).id;
            QString alBumPath = QDir::currentPath()+"/"+albumId+".jpg";



            if((alBumPath!="")&&(alBumPath!=myStatus.currentAlbumPath))
            {
                QColor myColor;
                myColor.setRgb(0,0,0);
                albumArt->fill(myColor);
                if(albumArt->load(alBumPath))
                {
                    ui->pixture->setPixmap(*albumArt);
                    myStatus.currentAlbumPath=alBumPath;
                }

            }


            myClihandler->playlist_cmd("load album_id:"+playlist);


            get_track=true;
            getServerStatus();

            upDateUI();
            curIndex=2;
            ui->stackedWidget->setCurrentIndex(curIndex);
        }
    }
    else
    {
        QString albumId=allFavorites.at(index).id;
        myClihandler->favorites_play(albumId,0);




        get_track=true;
        getServerStatus();

        upDateUI();
        curIndex=2;
        ui->stackedWidget->setCurrentIndex(curIndex);
        myAlbumCover->getCurrentAlbumCover(ip_addr,http_port_nr.toInt(),"/music/current/cover.jpg");
    }
}

void MainWindow::playTrack(int index)
{
    int row=ui->ListTrack->getSelected();
    myClihandler->playlist_index(QString::number(row));
    getServerStatus();

}
void MainWindow::on_receive_albumcover(QPixmap *p)
{
    qDebug()<<"Got a picture Investigate why now************************************************************";


    QString albumId=myMusic->getAlbumId(myStatus.album);
    QPixmap myPix;
    myPix=p->scaled(89,89);
    ui->pixture->setPixmap(myPix);
    myPix.save(albumId+".jpg");
    qDebug()<<"Working dir="<<QDir::currentPath();

    //int result=myMusic->Update(NULL,myStatus.album,QDir::currentPath()+"/"+myStatus.album+".jpg");
    myStatus.currentAlbumPath=QDir::currentPath()+"/"+albumId+".jpg";

}

void MainWindow::removePanel()
{
    //    int       y=ui->frame_2->pos().y()+3;
    //    int y_frame=ui->frame->pos().y()+1;
    //    ui->frame_2->setGeometry(10,y,341,61);
    //    //ui->frame->setGeometry(10,y_frame,461,121);
    //
    //    if (y>640)
    //    {
    //        t->stop();
    //        UITimeout->stop();
    //
    //
    //    }

    animation->start();

}
void MainWindow::insertPanel()
{

    insertAnimation->start();

    UITimeout->start(3000);


}
void MainWindow::startAniTimer()
{

    removePanel();
    UITimeout->stop();
}
void MainWindow::end_of_offset(int offset)
{
    ui->verticalSlider->setValue(offset);
}
void MainWindow::longPress(int index)
{
    flickPlayAlbum(index);
}

//*****************************************************
//UI functions
void MainWindow::on_on_2_clicked()
{

    state=s_power;
    myClihandler->power("?");
}
void MainWindow::on_stop_2_clicked()
{

    myClihandler->stop();
    nowLabel="player Stoped";
    upDateUIPage();
}
void MainWindow::on_skib_f_2_clicked()
{

    playmode=mode_fav;
    myClihandler->favorites("0",maxFav);


}
void MainWindow::on_skib_b_2_clicked()
{
    playmode=mode_album;
    currentView="Artist List";
    allAlbums.clear();
    myMusic->getArtist(&allAlbums);
    ui->myList->setList(&allAlbums);
    upDateUIPage();

}
void MainWindow::on_play_2_clicked()
{
    playmode=mode_album;
    currentView="Album List";
    allAlbums.clear();
    myMusic->getAlbums(&allAlbums);
    ui->myList->setList(&allAlbums);
    upDateUIPage();
}
void MainWindow::on_power_valueChanged(int value)
{
    QString myvalue;
    myvalue.setNum(value,10);
    //    ui->vol->setText("Vol: "+myvalue+" %");
    myStatus.current_volumen=value;

    myClihandler->volume(myvalue);
    if (ui->power->value()>0)
    {
        //ui->volume->setStyleSheet("border-image: url(:/icon/VolumeNormalBlue.png) 3 3 2 3");

    }

}
void MainWindow::on_power_sliderReleased()
{
    QString vol;
    vol.setNum(ui->power->value());

    myClihandler->volume(vol);
    myStatus.current_volumen=ui->power->value();
    if (ui->power->value()>0)
    {
        // ui->volume->setStyleSheet("border-image: url(:/icon/VolumeNormalBlue.png) 3 3 2 3");

    }
}
void MainWindow::on_skib_b_clicked()
{
    myClihandler->playlist_index("-1");
    myClihandler->status();
    myClihandler->title();
}
void MainWindow::on_play_clicked()
{
    int row=ui->ListTrack->getSelected();
qDebug()<<"Row="<<row;
if (row>-1)
{
    if ((trackListe.at(row).albumName!=myStatus.currentTitle))
    {
        myClihandler->playlist_index(QString::number(row));
        getServerStatus();
    }
    else
    {
      myClihandler->pause();

    }
}
else
{
    myClihandler->pause();

}

}
void MainWindow::on_stop_clicked()
{
    myClihandler->stop();
}
void MainWindow::on_skib_f_clicked()
{
    myClihandler->playlist_index("+1");
    myClihandler->status();
    myClihandler->title();

}
void MainWindow::on_volume_clicked()
{
    if (ui->power->value()==0)
    {
        ui->power->setValue(oldVolumen);
        myClihandler->volume(QString::number(oldVolumen));
        //ui->volume->setStyleSheet("border-image: url(:/icon/VolumeNormalBlue.png) 3 3 2 3");

    }
    else
    {
        //ui->volume->setStyleSheet("border-image: url(:/icon/VolumeNormalRed.png) 3 3 2 3");
        oldVolumen=ui->power->value();
        ui->power->setValue(0);
        myClihandler->volume(QString::number(0));
    }
}
void MainWindow::on_volume_2_clicked()
{
    //ui->volume->click();

}
void MainWindow::on_on_clicked()
{

    state=s_power;
    myClihandler->power("?");

}
void MainWindow::on_pause_clicked()
{
    myClihandler->pause();
    myClihandler->status();
    nowLabel="player Pause";
    upDateUIPage();
}
void MainWindow::on_skib_f_3_clicked()
{

    myClihandler->statusTrack("14");

}
void MainWindow::on_ff_clicked()
{
    ui->label_6->setText("<font color=blue><h3>Remote Control</h3>"+myStatus.currentAlbum+"<br><b>"+myStatus.currentTitle+"</b><br>"+myStatus.currentArtist+"</br></font>");
}


void MainWindow::on_forward_clicked()
{
    rollwidget(true);
}
void MainWindow::on_back_clicked()
{
    rollwidget(false);
}

void MainWindow::on_forward_2_clicked()
{
    rollwidget(true);
}
void MainWindow::on_back_2_clicked()
{
    rollwidget(false);
}


void MainWindow::on_forward_3_clicked()
{
    rollwidget(true);
}
void MainWindow::on_back_3_clicked()
{
    rollwidget(false);
}


void MainWindow::on_forward_4_clicked()
{
    rollwidget(true);
}
void MainWindow::on_back_4_clicked()
{
    rollwidget(false);
}
void MainWindow::on_Settings_clicked()
{
    curIndex=3;
    ui->stackedWidget->setCurrentIndex(curIndex);
}
void MainWindow::on_pushButton_4_clicked()
{
    curIndex=0;
    ui->stackedWidget->setCurrentIndex(curIndex);

}



void MainWindow::on_lineEdit_returnPressed()
{
    qDebug()<<"Got return from lineedit"<<"\n"<<ui->lineEdit->text();
    ui->album->clear();
    ui->contributor->clear();
    ui->trackliste->clear();

    if (ui->lineEdit->text()=="")
        ui->album->clear();
    else
        myClihandler->search(ui->lineEdit->text());
}
void MainWindow::on_pushButton_6_clicked()
{
    curIndex=3;
    ui->stackedWidget->setCurrentIndex(curIndex);

}
void MainWindow::on_pushButton_7_clicked()
{
    curIndex=1;
    ui->stackedWidget->setCurrentIndex(curIndex);

}
void MainWindow::on_pushButton_5_clicked()
{
    curIndex=2;
    ui->stackedWidget->setCurrentIndex(curIndex);

}
void MainWindow::on_ControlBox_clicked()
{

}



void MainWindow::on_TestButton_clicked()
{
    allAlbum myAlbum;
    allAlbums.clear();
    QString myStr;
    int a;
    for (a=0;a<200;a++)
    {
        myAlbum.albumName="Album Name ="+myStr.setNum(a);
        myAlbum.albumRealName="Album_Name_"+myStr.setNum(a);
        myAlbum.id=myStr.setNum(a);
        //myMusic->insertAlbum(a,myAlbum.albumName,myAlbum.albumRealName);
        allAlbums.append(myAlbum);

    }

    for (a=0;a<allAlbums.count();a++)
        qDebug()<<"Album Name      "<<allAlbums.at(a).albumName;

    qDebug()<<"Sending allAlbums to database sync";
    myMusic->syncDatabase(&allAlbums);
}



void MainWindow::on_Network_clicked()
{

    if (ui->Network->isChecked()==false)
    {
        networkGroupAnimation->setStartValue(QRect(10,120,341,341));
        networkGroupAnimation->setEndValue(QRect(10,120,341,35));
        networkGroupAnimation->setDuration(250);
        networkGroupAnimation->start();
        ui->SqueezeCenter->show();
    }
    else
    {
        ui->SqueezeCenter->hide();
        networkGroupAnimation->setStartValue(QRect(10,120,341,35));
        networkGroupAnimation->setEndValue(QRect(10,120,341,341));
        networkGroupAnimation->setDuration(150);
        networkGroupAnimation->start();
    }
}

void MainWindow::on_SqueezeCenter_clicked()
{
    if (ui->SqueezeCenter->isChecked()==false)
    {


        squeezeCenterGroupAnimation->setStartValue(QRect(10,120,341,320));
        squeezeCenterGroupAnimation->setEndValue(QRect(10,170,341,35));
        squeezeCenterGroupAnimation->setDuration(250);
        squeezeCenterGroupAnimation->start();

        ui->Network->setGeometry(QRect(10,120,341,35));
    }
    else
    {

        squeezeCenterGroupAnimation->setStartValue(QRect(10,170,341,35));
        squeezeCenterGroupAnimation->setEndValue(QRect(10,120,341,320));
        squeezeCenterGroupAnimation->setDuration(150);
        squeezeCenterGroupAnimation->start();
        ui->Network->setGeometry(QRect(10,120,341,0));

    }
}

void MainWindow::on_pushButton_8_clicked()
{
    if (myStatus.current_power_state==0)
        myClihandler->power("1");
    else
        myClihandler->power("0");
}

void MainWindow::on_search_clicked()
{
    ui->album->clear();
    ui->contributor->clear();
    ui->trackliste->clear();
    qDebug()<<"Got a Search command"<<"\n"<<ui->lineEdit->text();
    if (ui->lineEdit->text()=="")
        ui->album->clear();
    else
        myClihandler->search(ui->lineEdit->text());
}

void MainWindow::on_contributor_doubleClicked(QModelIndex index)
{
    int my_index=ui->contributor->currentRow();
    QString id=searchContributor.at(my_index).ContributorId;
    myClihandler->playlist_loadtracks("contributor.id="+id);
}

void MainWindow::on_album_doubleClicked(QModelIndex index)
{
    int my_index=ui->album->currentRow();
    QString id=searchAlbum.at(my_index).albumId;
    myClihandler->playlist_loadtracks("album.id="+id);
}

void MainWindow::on_trackliste_doubleClicked(QModelIndex index)
{
    int my_index=ui->trackliste->currentRow();
    QString id=searchTrack.at(my_index).trackId;
    myClihandler->playlist_loadtracks("track.id="+id);
}

void MainWindow::on_album_entered(QModelIndex index)
{

}

void MainWindow::on_album_clicked(QModelIndex index)
{

    ui->trackliste->setCurrentRow(-1);
    ui->contributor->setCurrentRow(-1);
}

void MainWindow::on_contributor_clicked(QModelIndex index)
{
    ui->trackliste->setCurrentRow(-1);
    ui->album->setCurrentRow(-1);
}

void MainWindow::on_trackliste_clicked(QModelIndex index)
{
    ui->album->setCurrentRow(-1);
    ui->contributor->setCurrentRow(-1);
}

void MainWindow::on_play_3_clicked()
{
    if (ui->album->currentRow()!=-1)
        myClihandler->playlist_loadtracks("album.id="+searchAlbum.at(ui->album->currentRow()).albumId);
    else
        if (ui->trackliste->currentRow()!=-1)
            myClihandler->playlist_loadtracks("track.id="+searchTrack.at(ui->trackliste->currentRow()).trackId);
    else
        if (ui->contributor->currentRow()!=-1)
            myClihandler->playlist_loadtracks("contributor.id="+searchContributor.at(ui->contributor->currentRow()).ContributorId);
}

void MainWindow::on_Add_clicked()
{
    if (ui->album->currentRow()!=-1)
        myClihandler->playlist_addtracks("album.id="+searchAlbum.at(ui->album->currentRow()).albumId);
    else
        if (ui->trackliste->currentRow()!=-1)
            myClihandler->playlist_addtracks("track.id="+searchTrack.at(ui->trackliste->currentRow()).trackId);
    else
        if (ui->contributor->currentRow()!=-1)
            myClihandler->playlist_addtracks("contributor.id="+searchContributor.at(ui->contributor->currentRow()).ContributorId);

}


void MainWindow::on_verticalSlider_sliderMoved(int position)
{
    ui->myList->scrolllist(ui->verticalSlider->value());
}

void MainWindow::on_play_released()
{

}

#ifndef SQUEEZEBOXHELPER_H
#define SQUEEZEBOXHELPER_H

#include <QObject>
#include "database_struct.h"
#include "SqueezeSearch.h"
#include "SqueezeStatus.h"
#include <QListWidget>
static const QString squeezeCommands[] = {"info", "albums","power","status","status","mixer","album","artist","title","search","player"};
static const QString squeezeSubCommands[]={"count","id","uuid","name","ip","model","isplayer","displaytype","canpoweroff"};
class squeezeboxHelper : public QObject
{
Q_OBJECT
public:
    explicit squeezeboxHelper(QObject *parent = 0);
~squeezeboxHelper();
QString getSqueezeboxCommand(QString text);
int getNumber(QString text);
void analyzeAlbums(QString text,QList<allAlbum> *p);
void analyzeTrack(QString text,QList<allAlbum> *p);
void analyzeStatus(QString text,QList<allAlbum> *p,SqueezeStatus *status);
void StatusUpdate(QString text,SqueezeStatus *status);
void anslyzeSearch(QString text,QList<SqueezeSearchAlbum> *Album,QList<SqueezeSearchTrack> *Track,QList<SqueezeSearchContributor> *Contributor);
QString getAlbumName(QString text);
QString removeBadChar(QString text);
QString getAlbumID(QString text);
QString getAlbum(QString text,QString srcStr);

allAlbum myAlbum;
SqueezeSearchAlbum album_Search;
SqueezeSearchTrack track_Search;
SqueezeSearchContributor contributor_Search;
signals:

public slots:

};

#endif // SQUEEZEBOXHELPER_H

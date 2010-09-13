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


#ifndef SQUEEZEBOXHELPER_H
#define SQUEEZEBOXHELPER_H

#include <QObject>
#include "database_struct.h"
#include "SqueezeSearch.h"
#include "SqueezeStatus.h"
#include <QListWidget>
static const QString squeezeCommands[] = {"info", "albums","power","status","status","mixer","album","artist","title","search","player","favorites"};
static const QString squeezeSubCommands[]={"count","id","uuid","name","ip","model","isplayer","displaytype","canpoweroff"};
static const QString squeezeInfoSubCommands[]={"total artists","total songs","total albums"};
static const QString squeezeFavSubCommands[]={"favorites items"};
class squeezeboxHelper : public QObject
{
Q_OBJECT
public:
    explicit squeezeboxHelper(QObject *parent = 0);
~squeezeboxHelper();
QString getSqueezeboxCommand(QString text);
int getNumber(QString text);
void analyzeAlbums(QString text,QList<allAlbum> *p);
void analyzeFav(QString text,QList<allAlbum> *p);
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

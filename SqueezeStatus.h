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


#ifndef SQUEEZESTATUS_H
#define SQUEEZESTATUS_H

 typedef struct{

    int number_of_albums;
    int number_of_artist;
    int number_of_tracks;
    int numbers_of_players;
    int playlistCurrentIndex;
    int current_power_state;
    int current_volumen;
    float time;
    float duration;
    int playedInPerc;
    int playedinper;
    QString playerName;
    QString playerStatus;
    QString playerConnected;
    QString playerIp;
    QString playerSignalSt;
    QString playerMode;
    QString playTime;
    QString playListTrack;
    QString playListRepeat;
    QString playListShuffle;
    QString playerShowB;
    QString currentAlbum;
    QString currentArtist;
    QString currentTitle;
    QString artist;
    QString album;
    QString showBr;
    QString currentAlbumPath;

} SqueezeStatus;
#endif // DATABASE_STRUCT_H

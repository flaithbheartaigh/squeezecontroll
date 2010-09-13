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

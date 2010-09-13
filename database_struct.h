#ifndef DATABASE_STRUCT_H
#define DATABASE_STRUCT_H

 typedef struct{
    QString                     id;
    QString              albumName;
    QString              albumRealName;
    QString              albumArtPath;
    QString              albumArtist;

} allAlbum;

 typedef struct{
     QString            favid;
     QString            favName;
     QString            favType;
 } allFavoritesStruct;


#endif // DATABASE_STRUCT_H

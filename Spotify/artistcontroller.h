#ifndef ARTISTCONTROLLER_H
#define ARTISTCONTROLLER_H


#include "playlistrepository.h"
#include<songrepository.h>
#include<albumrepository.h>
#include<vector>

class ArtistController
{
private:
    AlbumRepository& albumRepo;
    SongRepository& songRepo;
    PlaylistRepository& playlistRepo;
public:
    ArtistController(AlbumRepository& albumRepo , SongRepository& songRepo ,PlaylistRepository& playlistRepo );


    int createAlbum(int artistId , std::string name,const  QImage& cover = QImage());
    int createSong(int artistId , std::string title, std::string genre,
                   int releaseYear , std::string filePath , int albumId=0,QImage songImage = QImage());
    std::vector<Album> getArtistAlbums(int artistId);

    int editSong(int artistId , std::string title , std::string genre,
                 int releaseYear , std::string filePath , int songId,int albumId=0,QImage songImage = QImage());

    int editAlbum(int albumId , int artistId ,
                 const std::string& name,
                  const std::vector<int>& songIds , QImage cover = QImage()  );

    bool deleteSong(int songId , int artistId);
    bool deleteAlbum(int albumId , int artistId);

    std::vector<Song> getAlbumSongs(int albumId);
    std::vector<Song> getSingleSongs(int artistId);
    std::vector<Song> getAllSongs(int artistId);

    std::vector<Song> searchSong(int artistId , const std::string& query);
    std::vector<Song> filterByGenre(int artistId, const std::string& genre);
    std::vector<Song> filterByYear(int artistId , int year);
    std::optional<Album> getAlbumById(int albumId);
    std::optional<Song> getSongById(int songId);
};

#endif // ARTISTCONTROLLER_H

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


    int createAlbum(int artistId , std::string name);
    int createSong(int artistId , std::string title, std::string genre,
                   int releaseYear , std::string filePath , int albumId=0);
    std::vector<Album> getArtistAlbums(int artistId);

    int editSong(int artistId , std::string title , std::string genre,
                 int releaseYear , std::string filePath , int songId,int albumId=0);

    int editAlbum(int albumId , int artistId ,
                 const std::string& name,
                  const std::vector<int>& songIds   );

    bool deleteSong(int songId , int artistId);
    bool deleteAlbum(int albumId , int artistId);

    std::vector<Song> getAlbumSongs(int albumId);
    std::vector<Song> getSingleSongs(int artistId);
    std::vector<Song> getAllSongs(int artistId);
};

#endif // ARTISTCONTROLLER_H

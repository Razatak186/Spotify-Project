#ifndef LISTENERCONTROLLER_H
#define LISTENERCONTROLLER_H

#include "artistcontroller.h"
#include<playlistrepository.h>
#include<artistrepository.h>
#include<listenerrepository.h>
#include<albumrepository.h>
#include<songrepository.h>
#include<vector>


class ListenerController
{
private:
    PlaylistRepository& playlistRepo;
    ListenerRepository listenerRepo;
    ArtistRepository& artistRepo;
    SongRepository& songRepo;
    AlbumRepository& albumRepo;
    ArtistController& artistController;

public:
    ListenerController(PlaylistRepository& playlistRepo , SongRepository& songRepo ,
        AlbumRepository& albumRepo , ArtistRepository& artistRepo , ArtistController& artistco);


    std::vector<Account> seeAllArtists();
    std::vector<Album> getArtistAlbums(int artistId);
    std::vector<Song> getAlbumSongs(int albumId);

    int createPlaylist(int listenerId , const std::string& name);
    int editPlaylist(int playlistId , int listenerId , const std::string& newName);
    bool deletePlaylist(int playlistId , int listenerId);
    std::vector<Playlist> getListenerPlaylists(int listenerId);

    bool addSongToPlaylist(int playlistId , int listenerId , int songId);
    bool removeSongPlaylist(int playlistId , int listenerId , int songId);
    std::vector<Song> getPlaylistSongs(int playlistId);

    void likeSong(int listenerId, int songId);
    void unlikeSong(int listenerId , int songId);
    bool isLiked(int listenerId , int songId);
    std::vector<Song> getFavoriteSongs(int listenerId);

    std::vector<Song> searchSong(const std::string& query);
    std::vector<Song> filterByGenre(const std::string& genre);
    std::vector<Song> filterByYear(int year);
};

#endif // LISTENERCONTROLLER_H

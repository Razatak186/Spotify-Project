#include "listenercontroller.h"
#include "sorthelper.h"
#include<stdexcept>

ListenerController::ListenerController(PlaylistRepository& playlistRepo , SongRepository& songRepo ,
                                       AlbumRepository& albumRepo , ArtistRepository& artistRepo , ArtistController& artistco) : playlistRepo(playlistRepo), listenerRepo(playlistRepo),
    artistRepo(artistRepo) , songRepo(songRepo) , albumRepo(albumRepo) , artistController(artistco){}

std::vector<Account> ListenerController::seeAllArtists(){
    return artistRepo.getAllArtists();
}

std::vector<Album> ListenerController::getArtistAlbums(int artistId){
    return albumRepo.album(artistId);
}

std::vector<Song> ListenerController::getAlbumSongs(int albumId){
    return songRepo.getByAlbum(albumId);
}


int ListenerController::createPlaylist(int listenerId , const std::string& name){
    Playlist newPlaylist(0,name,listenerId);
    return playlistRepo.save(newPlaylist);
}

int ListenerController::editPlaylist(int playlistId , int listenerId,const std::string& newName){
    std::optional<Playlist> playlist = playlistRepo.search(playlistId);
    if(!playlist.has_value()){
        throw std::runtime_error("Playlist not found.");
    }

    if(playlist->getListenerId() != listenerId){
        throw std::runtime_error("You don't have permission to edit this playlist.");
    }

    Playlist updated = playlist.value();
    updated.setName(newName);
    return playlistRepo.save(updated);
}

bool ListenerController::deletePlaylist(int playlistId , int listenerId){
    std::optional<Playlist> playlist = playlistRepo.search(playlistId);
    if(!playlist.has_value()){
        throw std::runtime_error("Playlist not found.");
    }

    if(playlist->getListenerId() != listenerId){
        throw std::runtime_error("You don't have permission to delete this playlist.");
    }

    if(playlist->getName() == "Favorite Songs"){
        throw std::runtime_error("Cannot delete Favorite Songs playlist.");
    }

    return playlistRepo.remove(playlistId);
}

std::vector<Playlist> ListenerController::getListenerPlaylists(int listenerId){
    return playlistRepo.playlist(listenerId);
}


bool ListenerController::addSongToPlaylist(int playlistId , int listenerId , int songId){
    std::optional<Song> song = songRepo.search(songId);
    if(!song.has_value()){
        throw std::runtime_error("Song not found.");
    }

    std::optional<Playlist> playlist = playlistRepo.search(playlistId);
    if(!playlist.has_value()){
        throw std::runtime_error("Playlist not found.");
    }

    if(playlist->getListenerId() != listenerId){
        throw std::runtime_error("You don't have permission to modify this playlist.");
    }

    return playlistRepo.insertSong(playlistId,songId);
}

bool ListenerController::removeSongPlaylist(int playlistId , int listenerId , int songId){
    std::optional<Playlist> playlist = playlistRepo.search(playlistId);
    if(!playlist.has_value()){
        throw std::runtime_error("Playlist not found.");
    }

    if(playlist->getListenerId() != listenerId){
        throw std::runtime_error("You don't have permission to modify this playlist.");
    }

    return playlistRepo.removeSong(playlistId , songId);
}

std::vector<Song> ListenerController::getPlaylistSongs(int playlistId){
    std::optional<Playlist> playlist = playlistRepo.search(playlistId);
    if(!playlist.has_value()){
        return {};
    }
    return songRepo.getByPlaylist(playlist->getSongIds());
}

void ListenerController::likeSong(int listenerId, int songId){
    listenerRepo.updateLiked(listenerId , songId , true);
}

void ListenerController::unlikeSong(int listenerId, int songId){
    listenerRepo.updateLiked(listenerId,songId, false);
}

bool ListenerController::isLiked(int listenerId , int songId){
    return listenerRepo.isLiked(listenerId,songId);
}

std::vector<Song> ListenerController::getFavoriteSongs(int listenerId){
    std::vector<Playlist> playlists = playlistRepo.playlist(listenerId);
    for(const auto& pl : playlists){
        if(pl.getName() == "Favorite Songs"){
            return songRepo.getByPlaylist(pl.getSongIds());
        }
    }
    return {};
}

std::vector<Song> ListenerController::searchSong(const std::string& query){
    return SortHelper::searchByTitle(songRepo.getAll(), query);
}

std::vector<Song> ListenerController::filterByGenre(const std::string& genre){
    return SortHelper::filterByGenre(songRepo.getAll(), genre);
}

std::vector<Song> ListenerController::filterByYear(int year){
    return SortHelper::filterByYear(songRepo.getAll() , year);
}
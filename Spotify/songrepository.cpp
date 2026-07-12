#include "songrepository.h"
#include<algorithm>
int SongRepository::save(const Song& item){

    for( auto& song : songs ){
        if(song.getId()== item.getId()){
            song = item;
            return song.getId();
        }
    }

    Song newSong = item;
    int maxId=0;
    for(const auto& song : songs){
        if(song.getId() > maxId) maxId = song.getId();
    }

    int newId= maxId+1;
    newSong.setId(newId);
    songs.push_back(newSong);
    return newId;
}

bool SongRepository::remove(int id){
    auto it = std::find_if(songs.begin(),songs.end(), [id](const Song& a){return a.getId() == id;});
    if(it!=songs.end()){
        songs.erase(it);
        return true;
    }
    return false;
}

std::optional<Song> SongRepository::search(int id){
    for(const auto& song : songs){
        if(song.getId()== id){
            return song;
        }
    }
    return std::nullopt;
}

std::vector<Song> SongRepository::singleSongs(int artistId){
    std::vector<Song> result;
    for(const auto& song : songs){
        if(song.getArtistId()== artistId && song.getAlbumId()==0){
            result.push_back(song);
        }
    }
    return result;
}

std::vector<Song> SongRepository::getByAlbum(int albumId){
    std::vector<Song> result;
    for(const auto& song : songs){
        if(song.getAlbumId()== albumId){
            result.push_back(song);
        }
    }
    return result;
}

std::vector<Song> SongRepository::getByArtist(int artistId){
    std::vector<Song> result;
    for(const auto& song : songs){
        if(song.getArtistId()== artistId){
            result.push_back(song);
        }
    }
    return result;
}

std::vector<Song> SongRepository::getByPlaylist(const std::vector<int>& songIds){
    std::vector<Song> result;
    for(int id : songIds){
        std::optional<Song> song = search(id);
        if(song.has_value()){
            result.push_back(song.value());
        }
    }
    return result;
}

std::vector<Song> SongRepository::getByLikedSongs(const std::vector<int>& songIds){
    return getByPlaylist(songIds);
}
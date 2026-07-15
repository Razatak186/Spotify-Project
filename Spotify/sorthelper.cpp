#include "sorthelper.h"
#include<algorithm>

std::vector<Album> SortHelper::sortAlbumsByName(std::vector<Album> albums){
     std::sort(albums.begin(), albums.end() , [](const Album& a , const Album& b){
        return a.getName() < b.getName() ;
    });
    return albums;
}

std::vector<Playlist> SortHelper::sortPlaylistByName(std::vector<Playlist> playlists){
    std::sort(playlists.begin(), playlists.end() , [](const Playlist& a, const Playlist& b){
        return a.getName() < b.getName();
    });
    return playlists;
}

std::vector<Song> SortHelper::sortSongByName(std::vector<Song> songs){
    std::sort(songs.begin(), songs.end() , [](const Song& a , const Song& b){
        return a.getTitle() < b.getTitle();
    });
    return songs;
}

std::vector<Song> SortHelper::sortSongByYear(std::vector<Song> songs){
    std::sort(songs.begin(), songs.end() , [](const Song& a, const Song& b){
        return a.getReleaseYear() < b.getReleaseYear();
    });
    return songs;
}

std::vector<Song> SortHelper::filterByGenre(const std::vector<Song>& songs ,const std::string& genre){
    std::vector<Song> result;

    for(const auto& song : songs){
        if(song.getGenre() == genre){
            result.push_back(song);
        }
    }
    return result;
}

std::vector<Song> SortHelper::filterByYear(const std::vector<Song>& songs , int year){
    std::vector<Song> result;
    for(const auto& song : songs){
        if(song.getReleaseYear()== year){
            result.push_back(song);
        }
    }
    return result;
}

std::vector<Song> SortHelper::searchByTitle(const std::vector<Song>& songs , const std::string& query){
    std::vector<Song> result;

    for(const auto& song : songs){
        if(song.getTitle().find(query) != std::string::npos){
            result.push_back(song);
        }
    }
    return result;
}
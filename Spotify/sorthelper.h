#ifndef SORTHELPER_H
#define SORTHELPER_H

#include<album.h>
#include<playlist.h>
#include<song.h>
#include<vector>

class SortHelper
{
public:
    static std::vector<Album> sortAlbumsByName(std::vector<Album> albums);
    static std::vector<Playlist> sortPlaylistByName(std::vector<Playlist> playlists);
    static std::vector<Song> sortSongByName(std::vector<Song> songs);
    static std::vector<Song> sortSongByYear(std::vector<Song> songs);

    static std::vector<Song> filterByGenre(const std::vector<Song>& songs , const std::string& genre);
    static std::vector<Song> filterByYear(const std::vector<Song>& songs , int year);
    static std::vector<Song> searchByTitle(const std::vector<Song>& songs , const std::string& query);
};

#endif // SORTHELPER_H

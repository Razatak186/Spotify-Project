#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <string>
#include <vector>
class Playlist
{
private:
    int id;
    std::string name;
    int listenerId;
    std::vector<int> songIds;

public:
    Playlist();
    Playlist(int id , std::string name , int listenerId);

    int getId()const;
    std::string getName()const;
    int getListenerId()const;
    std::vector<int> getSongIds()const;

    void setId(int id);
    void setName(const std::string& name);
    void setListenerId(int listenerId);
    void setSongIds(const std::vector<int>& songIds);

    void addSong(int songId);
    void removeSong(int songId);
    bool hasSong(int songId)const;
    int getSongCount()const;

};

#endif // PLAYLIST_H

#ifndef ALBUM_H
#define ALBUM_H

#include"QImage"
#include<vector>
#include<string>
class Album
{
private:
    int id;
    std::string name;
    int artistId;
    std::vector<int>songsIds;
    QImage cover;
public:
    Album();
    Album(int id , std::string name , int artistId);

    int getId()const;
    std::string getName()const;
    int getArtistId()const;
    std::vector<int> getSongIds()const;
    QImage getCover()const;

    void setId(int id);
    void setName(const std::string& name);
    void setArtistId(int artistId);
    void setSongIds(const std::vector<int>& songIds);
    void setCover(const QImage& cover);

    void addSong(int songId);
    void removeSong(int songId);
    bool hasSong(int songId)const;
    int getSongCount()const;
};

#endif // ALBUM_H

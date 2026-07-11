#include "album.h"
#include<algorithm>
Album::Album() : id(0) , artistId(0) {}

Album::Album(int id , std::string name , int artistId)
    : id(id) , name(name) , artistId(artistId){}

int Album::getId() const{return id;}
std::string Album::getName() const{return name;}
int Album::getArtistId() const{return artistId;}
std::vector<int> Album::getSongIds() const{return songsIds;}
QImage Album::getCover() const{return cover;}

void Album::setId(int id){this->id = id;}
void Album::setName(const std::string& name){this->name = name;}
void Album::setArtistId(int artistId){this->artistId = artistId;}
void Album::setSongIds(const std::vector<int>& songIds){this->songsIds = songIds;}
void Album::setCover(const QImage& cover){this->cover = cover;}


void Album::addSong(int songId){
    if(!hasSong(songId)){
        songsIds.push_back(songId);
    }
}

void Album::removeSong(int songId){
    auto it = std::find(songsIds.begin(),songsIds.end(), songId);
    if(it != songsIds.end()){
        songsIds.erase(it);
    }
}

bool Album::hasSong(int songId) const{
    return std::find(songsIds.begin(), songsIds.end(), songId)!= songsIds.end();
}

int Album::getSongCount() const{
    return songsIds.size();
}
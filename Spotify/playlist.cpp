#include "playlist.h"
#include <algorithm>

Playlist::Playlist(): id(0), listenerId(0) {}


Playlist::Playlist(int id , std::string name , int listenerID)
    : id(id) , name(name) , listenerId(listenerID) {}

int Playlist::getId()const {return id;}
std::string Playlist::getName()const{return name;}
int Playlist::getListenerId()const {return listenerId;}
std::vector<int> Playlist::getSongIds()const{return songIds;}

void Playlist::setId(int id){this->id = id;}
void Playlist::setName(const std::string& name){this->name = name;}
void Playlist::setListenerId(int listenerID){this->listenerId = listenerID;}
void Playlist::setSongIds(const std::vector<int>& songIds){this->songIds = songIds;}

void Playlist::addSong(int songId){
    if(!hasSong(songId)){
        songIds.push_back(songId);
    }
}

void Playlist::removeSong(int songId){
    auto it = std::find(songIds.begin(),songIds.end(),songId);
    if(it != songIds.end()){
        songIds.erase(it);
    }
}

bool Playlist::hasSong(int songId)const{
    return std::find(songIds.begin(),songIds.end(),songId)!=songIds.end();
}

int Playlist::getSongCount()const{
    return songIds.size();
}
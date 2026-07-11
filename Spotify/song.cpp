#include "song.h"

Song::Song() : id(0) , releaseYear(0) , artistId(0), albumId(0) {}


Song::Song(int id , std::string title , std::string genre ,
int releaseYear , int artistId , int albumId )
    : id(id) , title(title) , genre(genre), releaseYear(releaseYear),
    artistId(artistId) , albumId(albumId){}

int Song::getId(){return id;}
std::string Song::getTitle(){return title;}
std::string Song::getGenre(){return genre;}
int Song::getReleaseYear(){return releaseYear;}
int Song::getArtistId(){return artistId;}
int Song::getAlbumId(){return albumId;}
std::string Song::getFilePath(){return filePath;}

void Song::setId(int id){this->id = id;}
void Song::setTitle(std::string& title){this->title = title;}
void Song::setGenre(std::string& genre){this->genre = genre;}
void Song::setReleaseYear(int year){this->releaseYear = year;}
void Song::setArtistId(int artistID){this->artistId = artistID;}
void Song::setAlbumId(int albumId){this->albumId = albumId;}
void Song::setFilePath(std::string& path){this->filePath = path;}


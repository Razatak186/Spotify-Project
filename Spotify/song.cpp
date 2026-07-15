#include "song.h"

Song::Song() : id(0) , releaseYear(0) , artistId(0), albumId(0) {}


Song::Song(int id , std::string title , std::string genre ,
int releaseYear , int artistId , int albumId )
    : id(id) , title(title) , genre(genre), releaseYear(releaseYear),
    artistId(artistId) , albumId(albumId){}

int Song::getId() const{return id;}
std::string Song::getTitle() const{return title;}
std::string Song::getGenre() const{return genre;}
int Song::getReleaseYear() const{return releaseYear;}
int Song::getArtistId() const{return artistId;}
int Song::getAlbumId() const{return albumId;}
std::string Song::getFilePath() const{return filePath;}
QImage Song::getSongImage() const{return songImage;}

void Song::setId(int id){this->id = id;}
void Song::setTitle(const std::string& title){this->title = title;}
void Song::setGenre(const std::string& genre){this->genre = genre;}
void Song::setReleaseYear(int year){this->releaseYear = year;}
void Song::setArtistId(int artistID){this->artistId = artistID;}
void Song::setAlbumId(int albumId){this->albumId = albumId;}
void Song::setFilePath(const std::string& path){this->filePath = path;}
void Song::setSongImage(const QImage songImage){this->songImage = songImage;}

QJsonObject Song::toJson()const{
    QJsonObject obj;
    obj["id"] = id;
    obj["title"] = QString::fromStdString(title);
    obj["genre"] = QString::fromStdString(genre);
    obj["releaseYear"] = releaseYear;
    obj["artistId"] = artistId;
    obj["albumId"] = albumId;
    obj["filePath"] = QString::fromStdString(filePath);
    return obj;
}

Song Song::fromJson(const QJsonObject& obj){
    Song s;
    s.setId(obj["id"].toInt());
    s.setTitle(obj["title"].toString().toStdString());
    s.setGenre(obj["genre"].toString().toStdString());
    s.setReleaseYear(obj["releaseYear"].toInt());
    s.setArtistId(obj["artistId"].toInt());
    s.setAlbumId(obj["albumId"].toInt());
    s.setFilePath(obj["filePath"].toString().toStdString());
    return s;
}
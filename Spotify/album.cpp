#include "album.h"
#include "qbuffer.h"
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

QJsonObject Album::toJson() const{
    QJsonObject obj;
    obj["id"] = id;
    obj["name"]= QString::fromStdString(name);
    obj["artistId"] = artistId;

    QJsonArray songsArray;
    for(int id : songsIds){
        songsArray.append(id);
    }
    obj["songsIds"] = songsArray;
    QByteArray coverData = coverToByteArray();

    obj["cover"] = QString::fromUtf8(coverData.toBase64());
    return obj;

}

Album Album::fromJson(const QJsonObject& obj){
    Album a;
    a.setId(obj["id"].toInt());
    a.setName(obj["name"].toString().toStdString());
    a.setArtistId(obj["artistId"].toInt());
    std::vector<int> songsIds;
    const QJsonArray arr = obj["songsIds"].toArray();
    for(const auto& val : arr){
        songsIds.push_back(val.toInt());
    }
    a.setSongIds(songsIds);
    QString base64 = obj["cover"].toString();
    if (!base64.isEmpty()) {
        QByteArray coverData = QByteArray::fromBase64(base64.toUtf8());
        a.setCoverFromByteArray(coverData);
    }
    return a;
}

QByteArray Album::coverToByteArray()const{
    QByteArray byteArray;
    if(cover.isNull()){

        return byteArray;
    }
    QBuffer buffer(&byteArray);
    cover.save(&buffer, "PNG");

    return byteArray;
}

void Album::setCoverFromByteArray(const QByteArray& data){
    cover.loadFromData(data);

}
#include "albumrepository.h"
#include<algorithm>
#include<stdexcept>

AlbumRepository::AlbumRepository(){
    loadFromFile();
}

int AlbumRepository::save(const Album& item){

    for(auto& album : albums){
        if(album.getId()== item.getId()){
            album = item;
            saveToFile();
            return album.getId();
        }
    }

    Album newAlbum = item;

    int maxId=0;
    for(const auto& album : albums){
        if(album.getId() > maxId) maxId = album.getId();
    }

    int newId= maxId+1;
    newAlbum.setId(newId);
    albums.push_back(newAlbum);
    saveToFile();
    return newId;
}

bool AlbumRepository::remove(int id){
    auto it = std::find_if(albums.begin(),albums.end(), [id](const Album& a){return a.getId() == id;});
    if(it!=albums.end()){
        albums.erase(it);
        saveToFile();
        return true;
    }
    return false;
}

std::optional<Album> AlbumRepository::search(int id){
    for(const auto& album : albums){
        if(album.getId()== id){
            return album;
        }
    }
    return std::nullopt;
}

std::vector<Album> AlbumRepository::album(int artistId){
    std::vector<Album> result;
    for(const auto& album : albums){
        if(album.getArtistId()== artistId){
            result.push_back(album);
        }
    }
    return result;
}

void AlbumRepository::saveToFile(){
    QJsonArray arr;
    for(const auto& album : albums){
        arr.append(album.toJson());
    }
    QJsonDocument doc(arr);
    QFile file("albums.json");
    if(file.open(QIODevice::WriteOnly)){
        file.write(doc.toJson());
        file.close();
    }else{
        throw std::runtime_error("File cant open");
    }
}

void AlbumRepository::loadFromFile(){
    QFile file("albums.json");
    if(!file.open(QIODevice::ReadOnly)){
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    const QJsonArray arr = doc.array();

    albums.clear();
    for(const auto& val : arr){
        QJsonObject obj = val.toObject();
        albums.push_back(Album::fromJson(obj));
    }
}
#include "playlistrepository.h"
#include<algorithm>

PlaylistRepository::PlaylistRepository(){
    loadFromFile();
}

int PlaylistRepository::save(const Playlist& item){
    for(auto& playlist : playlists){
        if(playlist.getId()== item.getId()){
            playlist = item;
            return playlist.getId();
        }
    }

    Playlist newPlaylist = item;
    int maxId=0;
    for(const auto& playlist : playlists){
        if(playlist.getId() > maxId) maxId = playlist.getId();
    }

    int newId= maxId+1;
    newPlaylist.setId(newId);
    playlists.push_back(newPlaylist);
    saveToFile();
    return newId;
}

bool PlaylistRepository::remove(int id){
    auto it = std::find_if(playlists.begin(),playlists.end(), [id](const Playlist& a){return a.getId() == id;});
    if(it!=playlists.end()){
        playlists.erase(it);
        saveToFile();
        return true;
    }
    return false;
}

std::optional<Playlist> PlaylistRepository::search(int id){
    for(const auto& playlist : playlists){
        if(playlist.getId()== id){
            return playlist;
        }
    }
    return std::nullopt;
}

bool PlaylistRepository::insertSong(int playlistId , int songId){
    for(auto& playlist : playlists){
        if(playlist.getId() == playlistId){
            playlist.addSong(songId);
            return true;
        }
    }
    return false;
}

bool PlaylistRepository::removeSong(int playlistId , int songId){
    for(auto& playlist : playlists){
        if(playlist.getId()== playlistId){
            playlist.removeSong(songId);
            return true;
        }
    }
    return false;
}

std::vector<Playlist> PlaylistRepository::playlist(int listenerId){
    std::vector<Playlist> result;
    for(const auto& playlist : playlists){
        if(playlist.getListenerId()== listenerId){
            result.push_back(playlist);
        }
    }
    return result;
}

void PlaylistRepository::removeSongFromAllPlaylists(int songId){
    for(auto& playlist : playlists){
        playlist.removeSong(songId);
    }
}

void PlaylistRepository::saveToFile(){
    QJsonArray arr;
    for(const auto& playlist : playlists){
        arr.append(playlist.toJson());
    }

    QJsonDocument doc(arr);
    QFile file("playlists.json");
    if(file.open(QIODevice::WriteOnly)){
        file.write(doc.toJson());
        file.close();
    }else{
        throw std::runtime_error("File cant open");
    }

}

void PlaylistRepository::loadFromFile(){
    QFile file("playlists.json");
    if(!file.open(QIODevice::ReadOnly)){
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    const QJsonArray arr = doc.array();

    for(const auto& val : arr){
        QJsonObject obj = val.toObject();
        playlists.push_back(Playlist::fromJson(obj));
    }
}
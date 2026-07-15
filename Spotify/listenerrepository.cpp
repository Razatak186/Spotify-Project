#include "listenerrepository.h"
#include<stdexcept>
#include<algorithm>

ListenerRepository::ListenerRepository(PlaylistRepository& playlistRepo) : playlistRepo(playlistRepo){loadFromFile();}

int ListenerRepository::save(const Account& item){
    if(!item.isListener()) throw std::invalid_argument("Invalid role for listener");

    bool isNew = true;
    for(auto& listener : listeners){
        if(listener.getId() == item.getId()){
            listener = item;
            return listener.getId();
        }

    }

    Account newAccount = item;
    int maxID=0;
    for(const auto& listener : listeners){
        if(listener.getId() > maxID) maxID = listener.getId();
    }
    int newID = maxID +1;
    newAccount.setId(newID);
    listeners.push_back(newAccount);
    if(isNew){
        Playlist favSongs(0,"Favorite Songs", newID);
        playlistRepo.save(favSongs);
    }
    saveToFile();
    return newID;

}

bool ListenerRepository::remove(int id){
    auto it = std::find_if(listeners.begin(), listeners.end(),[id](const Account& a){return a.getId()==id;} );
    if(it != listeners.end()){
        listeners.erase(it);
        saveToFile();
        return true;
    }
    return false;
}

std::optional<Account> ListenerRepository::search(int id){
    for(const auto& listener : listeners){
        if(listener.getId() == id){
            return listener;
        }
    }
    return std::nullopt;
}

std::optional<Account> ListenerRepository::searchByUserName(const std::string& userName){
    for(const auto& listener : listeners){
        if(listener.getUserName() == userName){
            return listener;
        }
    }
    return std::nullopt;
}

void ListenerRepository::updateLiked(int listenerId , int songId , bool liked){
    std::vector<Playlist> listenerPlaylists = playlistRepo.playlist(listenerId);

    for(const auto& pl : listenerPlaylists){
        if(pl.getName()== "Favorite Songs"){
            if(liked){
                playlistRepo.insertSong(pl.getId(), songId);
            }else{
                playlistRepo.removeSong(pl.getId(),songId);
            }
            return;
        }
    }
    throw std::runtime_error("Favorite Songs playlist not found for this listener");
}

bool ListenerRepository::isLiked(int listenerId , int songId){
    std::vector<Playlist> listenerPlaylists = playlistRepo.playlist(listenerId);

    for(const auto& pl : listenerPlaylists){
        if(pl.getName() == "Favorite Songs"){
            return pl.hasSong(songId);
        }
    }
    return false;
}

void ListenerRepository::saveToFile(){
    QJsonArray arr;
    for(const auto& listener : listeners){
        arr.append(listener.toJson());
    }
    QJsonDocument doc(arr);
    QFile file("listeners.json");
    if(file.open(QIODevice::WriteOnly)){
        file.write(doc.toJson());
        file.close();
    }else{
        throw std::runtime_error("File cant open");
    }
}

void ListenerRepository::loadFromFile(){
    QFile file("listeners.json");
    if(!file.open(QIODevice::ReadOnly)){
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    const QJsonArray arr = doc.array();

    listeners.clear();
    for(const auto& val : arr){
        QJsonObject obj = val.toObject();
        listeners.push_back(Account::fromJson(obj));
    }
}
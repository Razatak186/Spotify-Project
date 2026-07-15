#include "artistrepository.h"
#include<stdexcept>
#include<algorithm>
#include<stdexcept>

ArtistRepository::ArtistRepository(){
    loadFromFile();
}

int ArtistRepository::save(const Account& item){
    if(!item.isArtist()) throw std::invalid_argument("Invalid role for artist");

    for(auto& artist : artists){
        if(artist.getId()== item.getId()){
            artist = item;
            return artist.getId();
        }
    }

    Account newAccount = item;
    int maxID=0;
    for(const auto& artist : artists){
        if(artist.getId() > maxID) maxID = artist.getId();
    }
    int newID = maxID +1;
    newAccount.setId(newID);
    artists.push_back(newAccount);
    saveToFile();
    return newID;

}

bool ArtistRepository::remove(int id){
    auto it = std::find_if(artists.begin(), artists.end(),[id](const Account& a){return a.getId()==id;} );
    if(it != artists.end()){
        artists.erase(it);
        saveToFile();
        return true;
    }
    return false;
}

std::optional<Account> ArtistRepository::search(int id){
    for(const auto& artist : artists){
        if(artist.getId() == id){
            return artist;
        }
    }
    return std::nullopt;
}

std::optional<Account> ArtistRepository::searchByUserName(const std::string& userName){
    for(const auto& artist : artists){
        if(artist.getUserName() == userName){
            return artist;
        }
    }
    return std::nullopt;
}

std::vector<Account> ArtistRepository::getAllArtists(){
    std::vector<Account> result;
    for(auto& artist : artists){
        result.push_back(artist);
    }
    return result;
}

void ArtistRepository::saveToFile(){
    QJsonArray arr;
    for(const auto& artist : artists){
        arr.append(artist.toJson());
    }
    QJsonDocument doc(arr);
    QFile file("artists.json");
    if(file.open(QIODevice::WriteOnly)){
        file.write(doc.toJson());
        file.close();
    }else{
        throw std::runtime_error("File cant open");
    }
}

void ArtistRepository::loadFromFile(){
    QFile file("artists.json");
    if(!file.open(QIODevice::ReadOnly)){
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    const QJsonArray arr = doc.array();

    artists.clear();
    for(const auto& val : arr){
        QJsonObject obj = val.toObject();
        artists.push_back(Account::fromJson(obj));
    }
}
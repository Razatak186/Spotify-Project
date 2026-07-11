#include "artistrepository.h"
#include<stdexcept>
#include<algorithm>
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
    return newID;

}

bool ArtistRepository::remove(int id){
    auto it = std::find_if(artists.begin(), artists.end(),[id](const Account& a){return a.getId()==id;} );
    if(it != artists.end()){
        artists.erase(it);
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

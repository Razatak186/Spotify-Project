#include "albumrepository.h"
#include<algorithm>

int AlbumRepository::save(const Album& item){
    for(auto& album : albums){
        if(album.getId()== item.getId()){
            album = item;
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
    return newId;
}

bool AlbumRepository::remove(int id){
    auto it = std::find_if(albums.begin(),albums.end(), [id](const Album& a){return a.getId() == id;});
    if(it!=albums.end()){
        albums.erase(it);
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


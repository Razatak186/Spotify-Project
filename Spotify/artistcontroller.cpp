#include "artistcontroller.h"
#include<stdexcept>
int ArtistController::createAlbum(int artistId , std::string name){
    Album newAlbum(0,name , artistId);
    int newId = albumRepo.save(newAlbum);
    return newId;
}


int ArtistController::createSong(int artistId , std::string title, std::string genre,
                                 int releaseYear , std::string filePath , int albumId){
        Song newSong(0,title , genre , releaseYear , artistId , albumId);
        newSong.setFilePath(filePath);
        int newId = songRepo.save(newSong);

        if(albumId!=0){
        std::optional<Album> newAlbum = albumRepo.search(albumId);
        if(newAlbum.has_value()){
            if(newAlbum->getArtistId() == artistId){
                newAlbum->addSong(newId);
                albumRepo.save(newAlbum.value());
            }else{
                throw std::runtime_error("ArtistId is incorrect.");
            }
        }else{
            throw std::runtime_error("No album found");
        }
        }
        return newId;
}

std::vector<Album> ArtistController::getArtistAlbums(int artistId){
    return albumRepo.album(artistId);
}

int ArtistController::editSong(int  artistId , std::string title , std::string genre,
                                  int releaseYear , std::string filePath , int songId,int albumId){
    std::optional<Song> oldSong = songRepo.search(songId);
    if(oldSong.has_value()){
        if(oldSong.value().getArtistId() == artistId){
            int oldAlbumId = oldSong.value().getAlbumId();
            if(oldAlbumId !=0){
                std::optional<Album> oldAlbum = albumRepo.search(oldAlbumId);
                oldAlbum->removeSong(oldSong->getId());
                albumRepo.save(oldAlbum.value());
            }

            Song newSong(songId,title , genre , releaseYear , artistId , albumId);
            newSong.setFilePath(filePath);

            songRepo.save(newSong);

            if(albumId !=0){
                std::optional<Album> newAlbum = albumRepo.search(albumId);
                if(newAlbum.has_value()){
                    if(newAlbum->getArtistId() == artistId){
                        newAlbum->addSong(songId);
                        albumRepo.save(newAlbum.value());
                    }else{
                        throw std::runtime_error("ArtistId is incorrect");
                    }
                }else{
                    throw std::runtime_error("No album found.");
                }
            }

        }else{
            throw std::runtime_error("You cant edit this song.Because you dont have access to edit this song.");
        }
    }else{
        throw std::runtime_error("No song found.");
    }

    return songId;
}

int ArtistController::editAlbum(int albumId , int artistId,
                                const std::string& name , const std::vector<int>& songIds){
    std::optional<Album> oldAlbum = albumRepo.search(albumId);
    if(!oldAlbum.has_value()){
        throw std::runtime_error("Album not found.");
    }

    if(oldAlbum->getArtistId() != artistId){
        throw std::runtime_error("You don't have permission to edit this album.");
    }

    Album newAlbum = oldAlbum.value();
    newAlbum.setName(name);
    newAlbum.setSongIds(songIds);

    return albumRepo.save(newAlbum);
}

bool ArtistController::deleteSong(int songId , int artistId){
    std::optional<Song> song = songRepo.search(songId);
    if(!song.has_value()){
        throw std::runtime_error("Song not found.");
    }

    if(song->getArtistId() != artistId){
        throw std::runtime_error("You don't have permission to delete this song.");
    }

    int albumId = song->getAlbumId();
    if(albumId!=0){
        std::optional<Album> album = albumRepo.search(albumId);
        if(album.has_value()){
            album->removeSong(songId);
            albumRepo.save(album.value());
        }
    }

    if(playlistRepo != nullptr){
        playlistRepo->removeSongFromAllPlaylists(songId);
    }

    return songRepo.remove(songId);
}

bool ArtistController::deleteAlbum(int albumId , int artistId){
    std::optional<Album> album = albumRepo.search(albumId);
    if(!album.has_value()){
        throw std::runtime_error("Album not found.");
    }

    if(album->getArtistId() != artistId){
        throw std::runtime_error("You don't have permission to delete this album.");
    }

    std::vector<int> songIds = album->getSongIds();
    for(int songId : songIds){
        deleteSong(songId , artistId);
    }

    return albumRepo.remove(albumId);
}

std::vector<Song> ArtistController::getAlbumSongs(int albumId){
    std::optional<Album> album = albumRepo.search(albumId);
    if(!album.has_value()){
        return {};
    }
    return songRepo.getByAlbum(albumId);
}

std::vector<Song> ArtistController::getSingleSongs(int artistId){
    return songRepo.singleSongs(artistId);
}

std::vector<Song> ArtistController::getAllSongs(int artistId){
    return songRepo.getByArtist(artistId);
}
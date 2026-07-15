#ifndef SONGREPOSITORY_H
#define SONGREPOSITORY_H

#include<abstractrepository.h>
#include<song.h>
#include<vector>

class SongRepository : public AbstractRepository<Song>
{
private:
    std::vector<Song> songs;
public:

    int save(const Song& item)override;
    bool remove(int id) override;
    std::optional<Song> search(int id)override;

    std::vector<Song> singleSongs(int artistId);
    std::vector<Song> getByAlbum(int albumId);
    std::vector<Song> getByArtist(int artistId);
    std::vector<Song> getByPlaylist(const std::vector<int>& songIds);
    std::vector<Song> getByLikedSongs(const std::vector<int>& songIds);
    std::vector<Song> getAll() const;
};

#endif // SONGREPOSITORY_H

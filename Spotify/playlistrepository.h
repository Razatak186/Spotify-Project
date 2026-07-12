#ifndef PLAYLISTREPOSITORY_H
#define PLAYLISTREPOSITORY_H

#include "abstractrepository.h"
#include "playlist.h"
#include<vector>

class PlaylistRepository : public  AbstractRepository<Playlist>
{
private:
    std::vector<Playlist> playlists;
public:
    int save(const Playlist& item) override;
    bool remove(int id) override;
    std::optional<Playlist> search(int id) override;

    bool insertSong(int playlistId, int songId);
    bool removeSong(int playlistId, int songId);
    std::vector<Playlist> playlist(int listenerId);
};

#endif // PLAYLISTREPOSITORY_H

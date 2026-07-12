#ifndef ALBUMREPOSITORY_H
#define ALBUMREPOSITORY_H

#include "album.h"
#include<abstractrepository.h>
#include<vector>

class AlbumRepository : public AbstractRepository<Album>
{
private :
    std::vector<Album> albums;
public:
    int save(const Album& item)override;
    bool remove(int id) override;
    std::optional<Album> search(int id)override;

    std::vector<Album> album(int artistId);
};

#endif // ALBUMREPOSITORY_H

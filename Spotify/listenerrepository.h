#ifndef LISTENERREPOSITORY_H
#define LISTENERREPOSITORY_H

#include<accountrepository.h>
#include<playlistrepository.h>
#include<vector>
#include<QFile>
#include<QJsonArray>
#include<QJsonDocument>

class ListenerRepository : public AccountRepository
{
private:
    std::vector<Account> listeners;
    PlaylistRepository& playlistRepo;
    void saveToFile();
    void loadFromFile();
public:
    ListenerRepository(PlaylistRepository& playlistRepo);

    int save(const Account& item) override;
    bool remove(int id) override;
    std::optional<Account> search(int id)override;
    std::optional<Account> searchByUserName(const std::string& username)override;

    void updateLiked(int listenerId , int songId , bool liked);
    bool isLiked(int listenerId , int songId);
};

#endif // LISTENERREPOSITORY_H

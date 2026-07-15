#ifndef ARTISTREPOSITORY_H
#define ARTISTREPOSITORY_H

#include<accountrepository.h>
#include<vector>
#include<QFile>
#include<QJsonArray>
#include<QJsonDocument>

class ArtistRepository : public AccountRepository
{
private:
     std::vector<Account> artists;
    void saveToFile();
     void loadFromFile();
public:
     ArtistRepository();
    int save(const Account& item)override;
    bool remove(int id) override;
    std::optional<Account> search(int id)override;
    std::optional<Account> searchByUserName(const std::string& username)override;
    std::vector<Account> getAllArtists();
};

#endif // ARTISTREPOSITORY_H

#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include<listenerrepository.h>
#include<artistrepository.h>
#include<playlistrepository.h>

class AppController
{
private:
    ArtistRepository&  artist;
    ListenerRepository& listener;
public:
    AppController(ArtistRepository& artistRepo, ListenerRepository& listenerRepo);
    void registeration(std::string fullName , std::string userName , std::string password , int role,std::string bio="");
    Account login(std::string userName , std::string password);
    void editAccount(int accountid , bool isArtist , std::string newFullName , std::string newUserName , std::string newPassword);
    void deleteAccount(int accountid, bool isArtist);
    std::optional<Account> getAccount(int accountId , bool isArtist);
};

#endif // APPCONTROLLER_H

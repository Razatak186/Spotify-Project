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
    void registeration(std::string fullName , std::string userName , std::string password , int role);
    Account login(std::string userName , std::string password);
};

#endif // APPCONTROLLER_H

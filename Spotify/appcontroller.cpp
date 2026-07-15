#include "appcontroller.h"

AppController::AppController(ArtistRepository& artistRepo , ListenerRepository& listenerRepo) : artist(artistRepo), listener(listenerRepo){}

void AppController::registeration(std::string fullName , std::string userName , std::string password , int role){
    std::optional<Account> result = artist.searchByUserName(userName);
    if(result.has_value()){
        throw std::runtime_error("The username is already exist.");
    }


    std::optional<Account> result2 = listener.searchByUserName(userName);
    if(result2.has_value()){
        throw std::runtime_error("The username is already exist.");
    }

    Account newAccount(0,fullName,userName,password,role);
    if(role ==1){
        artist.save(newAccount);
    }else if(role==0){
        listener.save(newAccount);
    }
}

Account AppController::login(std::string userName , std::string password){
    std::optional<Account> result = artist.searchByUserName(userName);
    if(result.has_value()){
        if(result.value().getPassword() == password){
            return result.value();
        }else{
            throw std::runtime_error("Password is incorrect.");
        }
    }


    std::optional<Account> result2 = listener.searchByUserName(userName);
    if(result2.has_value()){
        if(result2.value().getPassword()== password){
            return result2.value();
        }else{
            throw std::runtime_error("Password is incorrect.");
        }
    }

     throw std::runtime_error("No account found whit this username.");
}

void AppController::editAccount(int accountId , bool isArtist , std::string newFullName , std::string newUserName , std::string newPassword){
    std::optional<Account> thisAccount;
    if(isArtist){
        thisAccount = artist.search(accountId);
    }else{
        thisAccount = listener.search(accountId);
    }
    if(!thisAccount.has_value()){
        throw std::runtime_error("No account found with this id.");
    }

    std::optional<Account> existingInArtist = artist.searchByUserName(newUserName);
    if(existingInArtist.has_value()){
        bool isSameAccount = isArtist && (existingInArtist->getId()== accountId);
        if(!isSameAccount){
            throw std::runtime_error("Account with this username already exists.");
        }

    }

    std::optional<Account> existInListener = listener.searchByUserName(newUserName);
    if(existInListener.has_value()){
        bool isSameAccount = !isArtist && (existInListener->getId() == accountId);
        if(!isSameAccount){
            throw std::runtime_error("Account with this username already exists.");
        }
    }

    thisAccount->setFullname(newFullName);
    thisAccount->setUsername(newUserName);
    thisAccount->setPassword(newPassword);

    if(isArtist){
        artist.save(thisAccount.value());
    }else{
        listener.save(thisAccount.value());
    }

}

void AppController::deleteAccount(int accountid, bool isArtist){
    std::optional<Account> account;
    if(isArtist){
        account = artist.search(accountid);
    }else{
        account = listener.search(accountid);
    }

    if(!account.has_value()){
        throw std::runtime_error("No account found.");
    }

    if(isArtist){
        artist.remove(accountid);
    }else{
        listener.remove(accountid);
    }

}
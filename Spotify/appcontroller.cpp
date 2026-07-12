#include "appcontroller.h"

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
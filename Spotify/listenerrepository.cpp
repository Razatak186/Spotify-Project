#include "listenerrepository.h"
#include<stdexcept>
#include<algorithm>

int ListenerRepository::save(const Account& item){
    if(!item.isListener()) throw std::invalid_argument("Invalid role for listener");

    for(auto& listener : listeners){
        if(listener.getId() == item.getId()){
            listener = item;
            return listener.getId();
        }

    }

    Account newAccount = item;
    int maxID=0;
    for(const auto& listener : listeners){
        if(listener.getId() > maxID) maxID = listener.getId();
    }
    int newID = maxID +1;
    newAccount.setId(newID);
    listeners.push_back(newAccount);
    return newID;

}

bool ListenerRepository::remove(int id){
    auto it = std::find_if(listeners.begin(), listeners.end(),[id](const Account& a){return a.getId()==id;} );
    if(it != listeners.end()){
        listeners.erase(it);
        return true;
    }
    return false;
}

std::optional<Account> ListenerRepository::search(int id){
    for(const auto& listener : listeners){
        if(listener.getId() == id){
            return listener;
        }
    }
    return std::nullopt;
}

std::optional<Account> ListenerRepository::searchByUserName(const std::string& userName){
    for(const auto& listener : listeners){
        if(listener.getUserName() == userName){
            return listener;
        }
    }
    return std::nullopt;
}


#ifndef LISTENERREPOSITORY_H
#define LISTENERREPOSITORY_H

#include<accountrepository.h>
#include<vector>
class ListenerRepository : public AccountRepository
{
private:
    std::vector<Account> listeners;
public:
    int save(const Account& item) override;
    bool remove(int id) override;
    std::optional<Account> search(int id)override;
    std::optional<Account> searchByUserName(const std::string& username)override;
};

#endif // LISTENERREPOSITORY_H

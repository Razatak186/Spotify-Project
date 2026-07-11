#ifndef ACCOUNTREPOSITORY_H
#define ACCOUNTREPOSITORY_H


#include<abstractrepository.h>
#include<account.h>


class AccountRepository : public AbstractRepository<Account>
{
public:
    virtual std::optional<Account> searchByUserName(const std::string& username)=0;
};

#endif // ACCOUNTREPOSITORY_H

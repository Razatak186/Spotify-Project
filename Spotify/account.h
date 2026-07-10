#ifndef ACCOUNT_H
#define ACCOUNT_H
#include<QImage>
#include <string>
class Account
{
private:
    int id;
    std::string fullname;
    std::string username;
    std::string bio;
    std::string password;
    int role;
    QImage profilePicture;
public:
    Account();
    Account(int id, std::string fullname, std::string username,
            std::string password, int role);


    int getId();
    std::string getFullName();
    std::string getUserName();
    std::string getBio();
    std::string getPassword();
    int getRole();
    QImage getProfilePicture();

    void setId(int id);
    void setFullname(const std::string& fullname);
    void setUsername(const std::string& username);
    void setBio(const std::string& bio);
    void setPassword(const std::string& password);
    void setRole(int role);
    void setProfilePicture(const QImage& profilePicture);

    bool isArtist();
    bool isListener();
};

#endif // ACCOUNT_H

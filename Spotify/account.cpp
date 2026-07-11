#include "account.h"

Account::Account() : id(0), role(0) {}


Account::Account(int id, std::string fullname, std::string username,
                 std::string password, int role)
    : id(id), fullname(fullname), username(username),
    password(password), role(role) {}

int Account::getId() {return id;}
std::string Account::getFullName()  { return fullname; }
std::string Account::getUserName()  { return username; }
std::string Account::getBio()  { return bio; }
std::string Account::getPassword()  { return password; }
int Account::getRole()  { return role; }
QImage Account::getProfilePicture() {return profilePicture;}

void Account::setId(int id) { this->id = id; }
void Account::setFullname(const std::string& fullname) { this->fullname = fullname; }
void Account::setUsername(const std::string& username) { this->username = username; }
void Account::setBio(const std::string& bio) { this->bio = bio; }
void Account::setPassword(const std::string& password) { this->password = password; }
void Account::setRole(int role) { this->role = role; }
void Account::setProfilePicture(const QImage& profilePicture) { this->profilePicture = profilePicture; }

bool Account::isArtist()  { return role == 1; }
bool Account::isListener()  { return role == 0; }
#include "account.h"
#include<QBuffer>

Account::Account() : id(0), role(0) {}


Account::Account(int id, std::string fullname, std::string username,
                 std::string password, int role)
    : id(id), fullname(fullname), username(username),
    password(password), role(role) {}

int Account::getId()const {return id;}
std::string Account::getFullName() const { return fullname; }
std::string Account::getUserName() const { return username; }
std::string Account::getBio() const { return bio; }
std::string Account::getPassword() const { return password; }
int Account::getRole() const  { return role; }
QImage Account::getProfilePicture()const {return profilePicture;}

void Account::setId(int id) { this->id = id; }
void Account::setFullname(const std::string& fullname) { this->fullname = fullname; }
void Account::setUsername(const std::string& username) { this->username = username; }
void Account::setBio(const std::string& bio) { this->bio = bio; }
void Account::setPassword(const std::string& password) { this->password = password; }
void Account::setRole(int role) { this->role = role; }
void Account::setProfilePicture(const QImage& profilePicture) { this->profilePicture = profilePicture; }

bool Account::isArtist() const { return role == 1; }
bool Account::isListener() const  { return role == 0; }

QJsonObject Account::toJson() const{
    QJsonObject obj;
    obj["id"] =id;
    obj["fullname"] = QString::fromStdString(fullname);
    obj["username"] = QString::fromStdString(username);
    obj["bio"] = QString::fromStdString(bio);
    obj["password"] = QString::fromStdString(password);
    obj["role"] = role;

    QByteArray imageData = imageToByteArray();
    obj["profilePicture"] = QString::fromUtf8(imageData.toBase64());
    return obj;
}

Account Account::fromJson(const QJsonObject& obj){
    Account a;
    a.setId(obj["id"].toInt());
    a.setFullname(obj["fullname"].toString().toStdString());
    a.setUsername(obj["username"].toString().toStdString());
    a.setBio(obj["bio"].toString().toStdString());
    a.setPassword(obj["password"].toString().toStdString());
    a.setRole(obj["role"].toInt());

    QString base64 = obj["profilePicture"].toString();
    if(!base64.isEmpty()){
        QByteArray imageData = QByteArray::fromBase64(base64.toUtf8());
        a.setImageByteArray(imageData);
    }
    return a;
}

QByteArray Account::imageToByteArray()const{
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    profilePicture.save(&buffer,"PNG");
    return byteArray;
}

void Account::setImageByteArray(const QByteArray& data){
    profilePicture.loadFromData(data);
}


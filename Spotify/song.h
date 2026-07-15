#ifndef SONG_H
#define SONG_H
#include"QImage"
#include<string>
#include<QJsonObject>
class Song
{
private:
    int id;
    std::string title;
    std::string genre;
    int releaseYear;
    int artistId;
    int albumId;
    std::string filePath;
    QImage songImage;
public:
    Song();
    Song(int id , std::string title , std::string genre , int releaseYear , int artistId, int albumId=0);


    int getId()const;
    std::string getTitle()const;
    std::string getGenre()const;
    int getReleaseYear()const;
    int getArtistId()const;
    int getAlbumId()const;
    std::string getFilePath()const;
    QImage getSongImage()const;

    void setId(int id);
    void setTitle(const std::string& title);
    void setGenre(const std::string& genre);
    void setReleaseYear(int year);
    void setArtistId(int ArtistID);
    void setAlbumId(int albumId);
    void setFilePath(const std::string& path);
    void setSongImage(const QImage songImage);

    QJsonObject toJson()const;
    static Song fromJson(const QJsonObject& obj);
};

#endif // SONG_H

#ifndef SONG_H
#define SONG_H

#include<string>
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
public:
    Song();
    Song(int id , std::string title , std::string genre , int releaseYear , int artistId, int albumId=0);


    int getId();
    std::string getTitle();
    std::string getGenre();
    int getReleaseYear();
    int getArtistId();
    int getAlbumId();
    std::string getFilePath();

    void setId(int id);
    void setTitle(std::string& title);
    void setGenre(std::string& genre);
    void setReleaseYear(int year);
    void setArtistId(int ArtistID);
    void setAlbumId(int albumId);
    void setFilePath(std::string& path);
};

#endif // SONG_H

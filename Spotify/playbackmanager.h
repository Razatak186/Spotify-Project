#ifndef PLAYBACKMANAGER_H
#define PLAYBACKMANAGER_H

#include <QObject>
#include<QMediaPlayer>
#include<QAudioOutput>
#include<vector>
#include<song.h>

class PlaybackManager : public QObject
{
    Q_OBJECT
public:
    explicit PlaybackManager(QObject *parent = nullptr);
    ~PlaybackManager();

    void setPlaylist(const std::vector<Song>& songs);
    void play();
    void pause();
    void stop();
    void next();
    void previous();
    void setVolume(int volume);
    int getVolume()const;
    bool isPlaying()const;

    Song getCurrentSong()const;
signals:
    void songChanged(const Song& song);
    void playbackStateChanged(bool isPlaying);
private slots:
    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);
private:
    QMediaPlayer* player;
    QAudioOutput* audioOutput;
    std::vector<Song> playlist;
    int currentIndex;
};

#endif // PLAYBACKMANAGER_H

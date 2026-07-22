#include "playbackmanager.h"
#include<QUrl>

PlaybackManager::PlaybackManager(QObject *parent)
    : QObject(parent)
    ,player(new QMediaPlayer(this))
    ,audioOutput(new QAudioOutput(this))
    ,currentIndex(-1)
{
    player->setAudioOutput(audioOutput);
    audioOutput->setVolume(0.5);

    connect(player, &QMediaPlayer::mediaStatusChanged,this,&PlaybackManager::onMediaStatusChanged);


}

PlaybackManager::~PlaybackManager()
{
    delete player;
    delete audioOutput;
}

void PlaybackManager::setPlaylist(const std::vector<Song>& songs){
    playlist = songs;
    currentIndex =-1;
    if(!playlist.empty()){
        currentIndex=0;
        emit songChanged(playlist[currentIndex]);
    }
}

void PlaybackManager::play(){
    if(playlist.empty())return;
    if(currentIndex == -1) currentIndex =0;
    QString filePath = QString::fromStdString(playlist[currentIndex].getFilePath());
    if(!filePath.isEmpty()){
        player->setSource(QUrl::fromLocalFile(filePath));
        player->play();
        emit playbackStateChanged(true);
    }
}

void PlaybackManager::pause(){
    player->pause();
    emit playbackStateChanged(false);
}

void PlaybackManager::stop(){
    player->stop();
    emit playbackStateChanged(false);
}

void PlaybackManager::next(){
    if(playlist.empty())return;
    currentIndex = (currentIndex+1)% playlist.size();
    emit songChanged(playlist[currentIndex]);
    play();
}

void PlaybackManager::previous(){
    if(playlist.empty())return;
    currentIndex = (currentIndex -1 + playlist.size())% playlist.size();
    emit songChanged(playlist[currentIndex]);
    play();
}

void PlaybackManager::setVolume(int volume){
    audioOutput->setVolume(volume/100.0);
}

int PlaybackManager::getVolume()const{
    return audioOutput->volume() *100;
}

bool PlaybackManager::isPlaying()const{
    return player->playbackState() == QMediaPlayer::PlayingState;
}

Song PlaybackManager::getCurrentSong()const{
    if(currentIndex >=0 && currentIndex < (int)playlist.size()){
        return playlist[currentIndex];
    }
    return Song();
}

void PlaybackManager::onMediaStatusChanged(QMediaPlayer::MediaStatus status){
    if(status == QMediaPlayer::EndOfMedia){
        next();
    }
}


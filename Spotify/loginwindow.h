#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H
#include<appcontroller.h>
#include<artistwindow.h>
#include <QWidget>
#include "artistcontroller.h"
#include "albumrepository.h"
#include "listenercontroller.h"
#include "songrepository.h"
#include "playlistrepository.h"
namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(AppController& appController,
                         ArtistController& artistController,
                         ListenerController& listenerController,
                         PlaylistRepository& playlistRepo,
                         SongRepository& songRepo,
                         AlbumRepository& albumRepo,
                         QWidget *parent = nullptr);
    ~LoginWindow();
private slots:
    void onLoginClicked();
    void onRegisterClicked();
    void onTogglePasswordClicked();
private:
    Ui::LoginWindow *ui;
    AppController& appCtrl;
    ArtistController& artistCtrl;
    ListenerController& listenerCtrl;
    PlaylistRepository& playlistRepo;
    SongRepository& songRepo;
    AlbumRepository& albumRepo;
};

#endif // LOGINWINDOW_H

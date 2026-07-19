#include <QApplication>
#include <QStyleFactory>
#include "loginwindow.h"
#include "appcontroller.h"
#include "artistrepository.h"
#include "listenerrepository.h"
#include "playlistrepository.h"
#include "songrepository.h"
#include "albumrepository.h"
#include <QPalette>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
     a.setQuitOnLastWindowClosed(false);
     QApplication::setStyle(QStyleFactory::create("Fusion"));


    PlaylistRepository playlistRepo;
    SongRepository songRepo;
    AlbumRepository albumRepo;
    ArtistRepository artistRepo;
    ListenerRepository listenerRepo(playlistRepo);

    AppController appCtrl(artistRepo, listenerRepo);
    ArtistController artistCtrl(albumRepo, songRepo, playlistRepo);
    ListenerController listenerCtrl(playlistRepo, songRepo, albumRepo, artistRepo, artistCtrl);
    LoginWindow loginWin(appCtrl, artistCtrl, listenerCtrl,
                         playlistRepo, songRepo, albumRepo);
    loginWin.show();

    return QApplication::exec();
}


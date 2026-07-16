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
     QApplication::setStyle(QStyleFactory::create("Fusion"));
    QPalette lightPalette;
    lightPalette.setColor(QPalette::Window, Qt::white);
    lightPalette.setColor(QPalette::WindowText, Qt::black);
    lightPalette.setColor(QPalette::Base, Qt::white);
    lightPalette.setColor(QPalette::Text, Qt::black);
    lightPalette.setColor(QPalette::Button, QColor(240, 240, 240));
    lightPalette.setColor(QPalette::ButtonText, Qt::black);
    QApplication::setPalette(lightPalette);

    PlaylistRepository playlistRepo;
    SongRepository songRepo;
    AlbumRepository albumRepo;
    ArtistRepository artistRepo;
    ListenerRepository listenerRepo(playlistRepo);

    AppController appCtrl(artistRepo, listenerRepo);

    LoginWindow loginWin(appCtrl);
    loginWin.show();

    return QApplication::exec();
}


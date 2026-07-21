#include "listenerwindow.h"
#include "editplaylistdialog.h"
#include "ui_listenerwindow.h"
#include<QMessageBox>
#include<editprofiledialog.h>
#include<sorthelper.h>
#include<addplaylistdialog.h>
#include<editprofiledialog.h>
#include<selectplaylistdialog.h>


ListenerWindow::ListenerWindow(int listenerId, ListenerController &controller, AppController &appController, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ListenerWindow)
    ,listenerCtrl(controller)
    ,appCtrl(appController)
    ,currentListenerId(listenerId)
    ,isDarkMode(false)
{
    ui->setupUi(this);

    ui->profilePhotoLabel->setFixedSize(50, 50);
    ui->profilePhotoLabel->setAlignment(Qt::AlignCenter);


    auto accountOpt = appCtrl.getAccount(listenerId,false);
    if(accountOpt.has_value()){
        ui->welcomeLabel->setText("👋 Welcome, "+ QString::fromStdString(accountOpt.value().getFullName())+ "!");
        QImage profilePic = accountOpt.value().getProfilePicture();
        if(!profilePic.isNull()){
            QPixmap pixmap = QPixmap::fromImage(profilePic);
            ui->profilePhotoLabel->setPixmap(pixmap.scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            ui->profilePhotoLabel->setScaledContents(true);
        }else{
            ui->profilePhotoLabel->setText("👤");
        }
    }else{
        ui->welcomeLabel->setText("👋 Welcome, Listener!");
        ui->profilePhotoLabel->setText("👤");
    }

    ui->playlistList->setAutoFillBackground(false);
    ui->artistList->setAutoFillBackground(false);
    ui->albumList->setAutoFillBackground(false);
    ui->songList->setAutoFillBackground(false);
    ui->favoriteList->setAutoFillBackground(false);
    ui->mainTab->setAutoFillBackground(false);

    ui->playlistList->viewport()->setAutoFillBackground(false);
    ui->artistList->viewport()->setAutoFillBackground(false);
    ui->albumList->viewport()->setAutoFillBackground(false);
    ui->songList->viewport()->setAutoFillBackground(false);
    ui->favoriteList->viewport()->setAutoFillBackground(false);

    applyTheme();
    refreshAll();

    connect(ui->addButton,&QPushButton::clicked,this, &ListenerWindow::onAddPlaylistClicked);
    connect(ui->editButton,&QPushButton::clicked,this,&ListenerWindow::onEditPlaylistClicked);
    connect(ui->deleteButton,&QPushButton::clicked,this,&ListenerWindow::onDeletePlaylistClicked);
    connect(ui->likeButton,&QPushButton::clicked,this,&ListenerWindow::onLikeClicked);
    connect(ui->unlikeButton,&QPushButton::clicked,this,&ListenerWindow::onUnlikeClicked);
    connect(ui->addToPlaylistButton,&QPushButton::clicked,this,&ListenerWindow::onAddToPlaylistClicked);
    connect(ui->searchButton,&QPushButton::clicked,this,&ListenerWindow::onSearchClicked);
    connect(ui->searchEdit,&QLineEdit::returnPressed,this,&ListenerWindow::onSearchClicked);
    connect(ui->filterCombo,&QComboBox::currentIndexChanged,this,&ListenerWindow::onFilterTypeChanged);
    connect(ui->filterValueCombo,&QComboBox::currentIndexChanged,this,&ListenerWindow::onFilterValueChanged);
    connect(ui->mainTab,&QTabWidget::currentChanged,this,&ListenerWindow::onTabChanged);
    connect(ui->artistList, &QListWidget::itemClicked, this, &ListenerWindow::onArtistClicked);
    connect(ui->albumList, &QListWidget::itemClicked, this, &ListenerWindow::onAlbumClicked);
    connect(ui->songList, &QListWidget::itemClicked, this, &ListenerWindow::onSongClicked);
    connect(ui->removeFromPlaylistButton,&QPushButton::clicked,this,&ListenerWindow::onRemoveFromPlaylistClicked);
    connect(ui->logoutButton, &QPushButton::clicked, this, &ListenerWindow::onLogoutClicked);
    connect(ui->darkModeButton, &QPushButton::clicked, this, &ListenerWindow::onDarkModeClicked);
    connect(ui->editProfileButton, &QPushButton::clicked, this, &ListenerWindow::onEditProfileClicked);
    connect(ui->deleteProfileButton, &QPushButton::clicked, this, &ListenerWindow::onDeleteProfileClicked);
    connect(ui->playlistList,&QListWidget::itemClicked,this,&ListenerWindow::onPlaylistClicked);
    connect(ui->playlistSongsList, &QListWidget::itemClicked,
            this, &ListenerWindow::onPlaylistSongsClicked);

    ui->filterCombo->addItem("None");
    ui->filterCombo->addItem("Genre");
    ui->filterCombo->addItem("Year");

    ui->addToPlaylistButton->setEnabled(false);
    ui->likeButton->setEnabled(false);
    ui->unlikeButton->setEnabled(false);
    ui->removeFromPlaylistButton->setEnabled(false);
}

ListenerWindow::~ListenerWindow()
{
    delete ui;
}

void ListenerWindow::applyTheme(){
    if(isDarkMode){
        this->setStyleSheet(DARK_STYLES);
        ui->darkModeButton->setText("☀️ Light");
    }else{
        this->setStyleSheet(LIGHT_STYLES);
        ui->darkModeButton->setText("🌙 Dark");
    }
}

void ListenerWindow::refreshAll(){
    loadPlaylists();
    loadArtists();
    loadFavorites();

    ui->albumList->clear();
    ui->songList->clear();

    ui->likeButton->setEnabled(false);
    ui->unlikeButton->setEnabled(false);
    ui->addToPlaylistButton->setEnabled(false);
    ui->removeFromPlaylistButton->setEnabled(false);
}

void ListenerWindow::loadPlaylists(){
    std::vector<Playlist> playlists = listenerCtrl.getListenerPlaylists(currentListenerId);
    ui->playlistList->clear();
    for(const auto& playlist : playlists){
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(playlist.getName()));
        item->setData(Qt::UserRole,playlist.getId());
        ui->playlistList->addItem(item);
    }
}

void ListenerWindow::loadArtists(){
    std::vector<Account> artists = listenerCtrl.seeAllArtists();
    ui->artistList->clear();
    for(const auto& artist : artists){
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(artist.getFullName()));
        item->setData(Qt::UserRole,artist.getId());
        QImage profilepic = artist.getProfilePicture();
        if(!profilepic.isNull()){
            QPixmap pixmap = QPixmap::fromImage(profilepic);
            QIcon icon(pixmap.scaled(40,40,Qt::KeepAspectRatio,Qt::SmoothTransformation));
            item->setIcon(icon);
        }else{
            item->setIcon(QIcon());
        }
        ui->artistList->addItem(item);
    }
}

void ListenerWindow::loadAlbums(int artistId){
    std::vector<Album> albums = listenerCtrl.getArtistAlbums(artistId);
    ui->albumList->clear();
    for(const auto& album : albums){
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(album.getName()));
        item->setData(Qt::UserRole,album.getId());
        ui->albumList->addItem(item);
    }

    std::vector<Song> singles = listenerCtrl.getSingleSongs(artistId);
    if(!singles.empty()){
        QListWidgetItem* singleItem = new QListWidgetItem("📌 Singles");
        singleItem->setData(Qt::UserRole,-1);
        ui->albumList->addItem(singleItem);
    }

    ui->songList->clear();
    ui->likeButton->setEnabled(false);
    ui->unlikeButton->setEnabled(false);
    ui->addToPlaylistButton->setEnabled(false);
    ui->removeFromPlaylistButton->setEnabled(false);
}

void ListenerWindow::loadSongs(int albumId){
    std::vector<Song> songs = listenerCtrl.getAlbumSongs(albumId);
    ui->songList->clear();
    for(const auto& song : songs){
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(song.getTitle()));
        item->setData(Qt::UserRole,song.getId());
        ui->songList->addItem(item);
    }
}

void ListenerWindow::loadFavorites(){
    std::vector<Song> songs = listenerCtrl.getFavoriteSongs(currentListenerId);
    ui->favoriteList->clear();
    for(const auto& song : songs){
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(song.getTitle()));
        item->setData(Qt::UserRole,song.getId());
        ui->favoriteList->addItem(item);
    }
}

int ListenerWindow::getCurrentTab(){
    return ui->mainTab->currentIndex();
}

int ListenerWindow::getSelectedItemId(QListWidget* list){
    QListWidgetItem* item = list->currentItem();
    if(item){
        return item->data(Qt::UserRole).toInt();
    }
    return -1;
}

void ListenerWindow::updateActionButtons(){
    int currentTab = getCurrentTab();
    bool hasSongSelected = false;

    if(currentTab ==0){
        hasSongSelected = (getSelectedItemId(ui->playlistSongsList)!=-1);
    }else{
        hasSongSelected = (getSelectedItemId(ui->songList)!=-1);
    }

    ui->likeButton->setEnabled(hasSongSelected);
    ui->unlikeButton->setEnabled(hasSongSelected);
    ui->addToPlaylistButton->setEnabled(hasSongSelected);
    ui->removeFromPlaylistButton->setEnabled(hasSongSelected);
}

void ListenerWindow::onTabChanged(int index){
    if(index == 0)loadPlaylists();
    else if(index == 1) loadArtists();
    else if(index == 2) loadFavorites();
}

void ListenerWindow::onArtistClicked(QListWidgetItem* item){
    int artistId = item->data(Qt::UserRole).toInt();
    loadAlbums(artistId);
}

void ListenerWindow::onAlbumClicked(QListWidgetItem* item){
    int albumId = item->data(Qt::UserRole).toInt();
    if(albumId ==-1){
        int artistId = getSelectedItemId(ui->artistList);
        if(artistId !=-1){
            std::vector<Song> singles = listenerCtrl.getSingleSongs(artistId);
            ui->songList->clear();
            for (const auto& song : singles) {
                QListWidgetItem* songItem = new QListWidgetItem(QString::fromStdString(song.getTitle()));
                songItem->setData(Qt::UserRole, song.getId());
                ui->songList->addItem(songItem);
            }
        }
        return;
    }
    loadSongs(albumId);
}

void ListenerWindow::onSongClicked(QListWidgetItem* item){
     Q_UNUSED(item);
    updateActionButtons();
}

void ListenerWindow::onLogoutClicked(){
    this->close();
    if(parentWidget()){
        parentWidget()->show();
    }
}

void ListenerWindow::onDarkModeClicked(){
    isDarkMode = !isDarkMode;
    applyTheme();
}

void ListenerWindow::onDeletePlaylistClicked(){
    int playlistId = getSelectedItemId(ui->playlistList);
    if(playlistId == -1){
        QMessageBox::warning(this , "Error", "Please select a playlist first.");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm Delete","Are you sure you want to delete this playlist?", QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes){
        try{
            listenerCtrl.deletePlaylist(playlistId ,currentListenerId);
            refreshAll();
            QMessageBox::information(this , "Success", "Playlist deleted successfully!");
        }catch(const std::exception& e){
            QMessageBox::warning(this , "Error", e.what());
        }
    }
}

void ListenerWindow::onLikeClicked(){
    int songId = getSelectedItemId(ui->songList);
    if(songId == -1){
        QMessageBox::warning(this , "Error","Please select a song first.");
        return;
    }

    try{
        listenerCtrl.likeSong(currentListenerId,songId);
        refreshAll();
        QMessageBox::information(this , "Succes", "Song liked!");
    }catch(const std::exception& e){
        QMessageBox::warning(this , "Error", e.what());
    }
}

void ListenerWindow::onUnlikeClicked(){
    int songId = getSelectedItemId(ui->songList);
    if(songId == -1){
        QMessageBox::warning(this , "Error" , "Please select a song first.");
        return;
    }

    try{
        listenerCtrl.unlikeSong(currentListenerId, songId);
        refreshAll();
        QMessageBox::information(this , "Succes", "Song unliked!");

    }catch(const std::exception& e){
        QMessageBox::warning(this , "Error",e.what());
    }
}

void ListenerWindow::onAddPlaylistClicked(){
    AddPlaylistDialog dialog(this);
    if(dialog.exec() == QDialog::Accepted){
        QString name = dialog.getPlaylistName();
        try{
            listenerCtrl.createPlaylist(currentListenerId,name.toStdString());
            refreshAll();
            QMessageBox::information(this , "Success", "Playlist created successfully!");
        }catch(const std::exception& e){
            QMessageBox::warning(this, "Error",e.what());
        }
    }
}

void ListenerWindow::onEditPlaylistClicked(){
    int playlistId = getSelectedItemId(ui->playlistList);
    if(playlistId == -1){
        QMessageBox::warning(this ,"Error","Please select a playlist first.");
        return;
    }

    auto playlistOpt = listenerCtrl.getPlaylistById(playlistId);
    if(!playlistOpt.has_value()){
        QMessageBox::warning(this, "Error", "Playlist not found.");
        return;
    }

    Playlist playlist = playlistOpt.value();
    EditPlaylistDialog dialog(this);
    dialog.setPlaylistName(QString::fromStdString(playlist.getName()));

    if(dialog.exec() == QDialog::Accepted){
        QString newName = dialog.getPlaylistName();
        try{
            listenerCtrl.editPlaylist(playlistId, currentListenerId, newName.toStdString());
            refreshAll();
            QMessageBox::information(this, "Success", "Playlist updated successfully!");
        }catch(const std::exception& e){
            QMessageBox::warning(this, "Error", e.what());
        }
    }
}

void ListenerWindow::onAddToPlaylistClicked(){
    int songId = getSelectedItemId(ui->songList);
    if(songId == -1){
        QMessageBox::warning(this,"Error","Please select a song first.");
        return;
    }

    std::vector<Playlist> playlists = listenerCtrl.getListenerPlaylists(currentListenerId);

    std::vector<Playlist> filteredPlaylists;
    for(const auto& p : playlists){
        if(p.getName() != "Favorite Songs"){
            filteredPlaylists.push_back(p);
        }
    }

    if(filteredPlaylists.empty()){
        QMessageBox::information(this, "Info", "You don't have any playlists to add to.");
        return;
    }

    SelectPlaylistDialog dialog(filteredPlaylists,this);
    if(dialog.exec() == QDialog::Accepted){
        int playlistId = dialog.getSelectedPlaylistId();
        if(playlistId !=-1){
            try{
                listenerCtrl.addSongToPlaylist(playlistId,currentListenerId,songId);
                QMessageBox::information(this, "Success", "Song added to playlist!");
            }catch(const std::exception& e){
                 QMessageBox::warning(this, "Error", e.what());
            }
        }
    }
}

void ListenerWindow::onSearchClicked(){
    QString query = ui->searchEdit->text().trimmed();
    int currentTab = getCurrentTab();

    if(query.isEmpty()){
        refreshAll();
        return;
    }

    if(currentTab==0){
        std::vector<Playlist> playlists = listenerCtrl.getListenerPlaylists(currentListenerId);
        std::vector<Playlist> result;
        for(const auto& p : playlists){
            if(QString::fromStdString(p.getName()).contains(query,Qt::CaseInsensitive)){
                result.push_back(p);
            }
        }
        ui->playlistList->clear();
        for(const auto& p : result){
            QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(p.getName()));
            item->setData(Qt::UserRole,p.getId());
            ui->playlistList->addItem(item);
        }
    }else if(currentTab == 1){
        std::vector<Account> artists = listenerCtrl.seeAllArtists();
        std::vector<Account> result;
        for(const auto& artist : artists){
            if(QString::fromStdString(artist.getFullName()).contains(query,Qt::CaseInsensitive)){
                result.push_back(artist);
            }
        }
        ui->artistList->clear();
        for(const auto& artist : result){
            QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(artist.getFullName()));
            item->setData(Qt::UserRole,artist.getId());
            ui->artistList->addItem(item);
        }
        ui->albumList->clear();
        ui->songList->clear();
    }else if(currentTab == 2){
        std::vector<Song> songs = listenerCtrl.getFavoriteSongs(currentListenerId);
        std::vector<Song> result;
        for(const auto& song : songs){
            if(QString::fromStdString(song.getTitle()).contains(query,Qt::CaseInsensitive)){
                result.push_back(song);
            }
        }
        ui->favoriteList->clear();
        for(const auto& song : result){
            QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(song.getTitle()));
            item->setData(Qt::UserRole,song.getId());
            ui->favoriteList->addItem(item);
        }

    }
}

void ListenerWindow::onFilterTypeChanged(){
    QString filterType = ui->filterCombo->currentText();
    ui->filterValueCombo->clear();

    if(filterType == "Genre"){
        ui->filterValueCombo->addItems({"Pop", "Rock", "Jazz", "Classical", "Hip Hop", "Electronic"});

    }else if(filterType == "Year"){
        for (int y = 2026; y >= 1980; --y) {
            ui->filterValueCombo->addItem(QString::number(y));
        }
    }else{
        applyCurrentFilter();
    }
}

void ListenerWindow::onFilterValueChanged(){
    applyCurrentFilter();
}

void ListenerWindow::applyCurrentFilter(){
    int currentTab = getCurrentTab();
    QString filterType = ui->filterCombo->currentText();
    QString filterValue = ui->filterValueCombo->currentText();

    if (currentTab == 1) {
        if (filterType == "None" || filterValue.isEmpty()) {
            int artistId = getSelectedItemId(ui->artistList);
            if (artistId != -1) {
                loadAlbums(artistId);
            }
            return;
        }

        int albumId = getSelectedItemId(ui->albumList);
        if (albumId == -1) return;

        std::vector<Song> songs = listenerCtrl.getAlbumSongs(albumId);

        if (filterType == "Genre") {
            songs = SortHelper::filterByGenre(songs, filterValue.toStdString());
        } else if (filterType == "Year") {
            songs = SortHelper::filterByYear(songs, filterValue.toInt());
        }

        ui->songList->clear();
        for (const auto& song : songs) {
            QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(song.getTitle()));
            item->setData(Qt::UserRole, song.getId());
            ui->songList->addItem(item);
        }
    }else if (currentTab == 0) {
        int playlistId = getSelectedItemId(ui->playlistList);
        if (playlistId == -1) return;

        std::vector<Song> songs = listenerCtrl.getPlaylistSongs(playlistId);

        if (filterType == "None" || filterValue.isEmpty()) {

            ui->playlistSongsList->clear();
            for (const auto& song : songs) {
                QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(song.getTitle()));
                item->setData(Qt::UserRole, song.getId());
                ui->playlistSongsList->addItem(item);
            }
            return;
        }

        if (filterType == "Genre") {
            songs = SortHelper::filterByGenre(songs, filterValue.toStdString());
        } else if (filterType == "Year") {
            songs = SortHelper::filterByYear(songs, filterValue.toInt());
        }

        ui->playlistSongsList->clear();
        for (const auto& song : songs) {
            QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(song.getTitle()));
            item->setData(Qt::UserRole, song.getId());
            ui->playlistSongsList->addItem(item);
        }
    }

}

void ListenerWindow::onEditProfileClicked() {
    auto accountOpt = appCtrl.getAccount(currentListenerId, false);
    if (!accountOpt.has_value()) {
        QMessageBox::warning(this, "Error", "Account not found.");
        return;
    }

    Account account = accountOpt.value();

    EditProfileDialog dialog(this);
    dialog.setFullName(QString::fromStdString(account.getFullName()));
    dialog.setUsername(QString::fromStdString(account.getUserName()));
    dialog.setPassword(QString::fromStdString(account.getPassword()));
    dialog.setProfileImage(account.getProfilePicture());

    if (dialog.exec() == QDialog::Accepted) {
        try {
            appCtrl.editAccount(
                currentListenerId,
                false,
                dialog.getFullName().toStdString(),
                dialog.getUsername().toStdString(),
                dialog.getPassword().toStdString(),
                dialog.getProfileImage()
                );


            auto updatedAccount = appCtrl.getAccount(currentListenerId, false);
            if (updatedAccount.has_value()) {
                QImage newPic = updatedAccount.value().getProfilePicture();
                if (!newPic.isNull()) {
                    QPixmap pixmap = QPixmap::fromImage(newPic);
                    ui->profilePhotoLabel->setPixmap(pixmap.scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation));
                    ui->profilePhotoLabel->setScaledContents(true);
                } else {
                    ui->profilePhotoLabel->setText("👤");
                }
            }

            ui->welcomeLabel->setText("👋 Welcome, " + dialog.getFullName() + "!");
            QMessageBox::information(this, "Success", "Profile updated successfully!");

        } catch (const std::exception& e) {
            QMessageBox::warning(this, "Error", e.what());
        }
    }
}

void ListenerWindow::onDeleteProfileClicked(){
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm Delete", "Are you sure you want to delete this account?",QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes){
        try{
            appCtrl.deleteAccount(currentListenerId,false);
             QMessageBox::information(this, "Success", "Account deleted successfully!");
            this->hide();
             if(parentWidget()){
                parentWidget()->show();
             }
        }catch (const std::exception& e) {
            QMessageBox::warning(this, "Error", e.what());
    }
}
}

void ListenerWindow::onPlaylistClicked(QListWidgetItem* item){
    int playlistId = item->data(Qt::UserRole).toInt();

    std::vector<Song> songs = listenerCtrl.getPlaylistSongs(playlistId);

    ui->playlistSongsList->clear();
    for(const auto& song: songs){
        QListWidgetItem* songItem = new QListWidgetItem(QString::fromStdString(song.getTitle()));
        songItem->setData(Qt::UserRole,song.getId());
        ui->playlistSongsList->addItem(songItem);
    }

    applyCurrentFilter();
}

void ListenerWindow::onRemoveFromPlaylistClicked(){
    int songId = getSelectedItemId(ui->playlistSongsList);
    if(songId == -1){
        QMessageBox::warning(this, "Error", "Please select a song first.");
        return;
    }

    int playlistId = getSelectedItemId(ui->playlistList);
    if(playlistId == -1){
        QMessageBox::warning(this, "Error", "Please select a playlist first.");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm Remove", "Are you sure you want to remove this song from playlist?", QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes){
        try{
            listenerCtrl.removeSongPlaylist(playlistId , currentListenerId, songId);
            QMessageBox::information(this, "Success", "Song removed from playlist!");
        }catch(const std::exception& e){
            QMessageBox::warning(this, "Error", e.what());
        }
    }
}

void ListenerWindow::onPlaylistSongsClicked(QListWidgetItem* item) {
    Q_UNUSED(item);
    updateActionButtons();
}
#include "artistwindow.h"
#include "ui_artistwindow.h"
#include<QMessageBox>
#include<QDebug>
#include<addsongdialog.h>
#include<editalbumdialog.h>
#include<editsongdialog.h>
#include<sorthelper.h>
#include<editprofiledialog.h>

ArtistWindow::ArtistWindow(int artistId,ArtistController& controller,AppController& appController,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ArtistWindow)
    ,artistCtrl(controller)
    ,appCtrl(appController)
    ,currentArtsitId(artistId)
    ,isDarkMode(false)
{
    ui->setupUi(this);

    ui->profilePhotoLabel->setFixedSize(50, 50);
    ui->profilePhotoLabel->setAlignment(Qt::AlignCenter);
    auto accountOpt = appCtrl.getAccount(artistId, true);
    if (accountOpt.has_value()) {
        ui->welcomeLabel->setText("👋 Welcome, " +
                                  QString::fromStdString(accountOpt.value().getFullName()) + "!");
        QImage profilePic = accountOpt.value().getProfilePicture();
        if(!profilePic.isNull()){
           QPixmap pixmap = QPixmap::fromImage(profilePic);
            ui->profilePhotoLabel->setPixmap(pixmap.scaled(50,50,Qt::KeepAspectRatio, Qt::SmoothTransformation));
               ui->profilePhotoLabel->setScaledContents(true);
        }else{
            ui->profilePhotoLabel->setText("👤");
        }
    } else {
        ui->welcomeLabel->setText("👋 Welcome, Artist!");
        ui->profilePhotoLabel->setText("👤");
    }

    ui->listWidget->setAutoFillBackground(false);
    ui->listWidget_2->setAutoFillBackground(false);
    ui->listWidget_3->setAutoFillBackground(false);
    ui->mainTabs->setAutoFillBackground(false);

    ui->listWidget->viewport()->setAutoFillBackground(false);
    ui->listWidget_2->viewport()->setAutoFillBackground(false);
    ui->listWidget_3->viewport()->setAutoFillBackground(false);

    applyTheme();

    refreshAll();



    connect(ui->addButton,&QPushButton::clicked,this,&ArtistWindow::onAddClicked);

    connect(ui->editButton,&QPushButton::clicked,this ,&ArtistWindow::onEditClicked);
    connect(ui->deleteButton,&QPushButton::clicked,this,&ArtistWindow::onDeleteClicked);
    connect(ui->logoutButton,&QPushButton::clicked,this,&ArtistWindow::onLogoutClicked);
    connect(ui->darkModeButton,&QPushButton::clicked,this,&ArtistWindow::onDarkModeClicked);
    connect(ui->mainTabs, &QTabWidget::currentChanged,this,&ArtistWindow::onTabChanged);

    connect(ui->listWidget,&QListWidget::itemClicked,this,[this](QListWidgetItem* item){
        int albumId = item->data(Qt::UserRole).toInt();
        loadSongs(albumId);
        ui->mainTabs->setCurrentIndex(1);
    });


    connect(ui->searchButton, &QPushButton::clicked, this, &ArtistWindow::onSearchClicked);
    connect(ui->searchEdit, &QLineEdit::returnPressed, this, &ArtistWindow::onSearchClicked);

    connect(ui->filterCombo, &QComboBox::currentIndexChanged, this, &ArtistWindow::onFilterTypechanged);
    connect(ui->filterValueCombo , &QComboBox::currentIndexChanged, this , &ArtistWindow::onFilterValuechanged);
    connect(ui->editProfileButton, &QPushButton::clicked, this ,&ArtistWindow::onEditProfileClicked);
    connect(ui->deleteProfileButton, &QPushButton::clicked, this ,&ArtistWindow::onDeleteProfileClicked);

    ui->filterCombo->addItem("None");
    ui->filterCombo->addItem("Genre");
    ui->filterCombo->addItem("Year");
}

ArtistWindow::~ArtistWindow()
{
    delete ui;
}

void ArtistWindow::loadAlbums(){
    std::vector<Album> albums = artistCtrl.getArtistAlbums(currentArtsitId);
    albums = SortHelper::sortAlbumsByName(albums);
    ui->listWidget->clear();
    for(const auto& album : albums){
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(album.getName()));
        item->setData(Qt::UserRole,album.getId());

        QImage cover = album.getCover();
        if(!cover.isNull()){
            QPixmap pixmap = QPixmap::fromImage(cover);
            QIcon icon(pixmap.scaled(40,40,Qt::KeepAspectRatio,Qt::SmoothTransformation));
            item->setIcon(icon);
        }

        ui->listWidget->addItem(item);
    }
}

void ArtistWindow::loadSongs(int albumId){
    std::vector<Song> songs = artistCtrl.getAlbumSongs(albumId);
    songs = SortHelper::sortSongByName(songs);
    ui->listWidget_2->clear();
    for(const auto& song : songs){
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(song.getTitle()));
        item->setData(Qt::UserRole, song.getId());
        ui->listWidget_2->addItem(item);
    }
}

void ArtistWindow::loadSingles(){
    std::vector<Song> songs = artistCtrl.getSingleSongs(currentArtsitId);
    ui->listWidget_3->clear();
    for(const auto& song : songs){
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(song.getTitle()));
        item->setData(Qt::UserRole, song.getId());
        ui->listWidget_3->addItem(item);
    }
}

void ArtistWindow::refreshAll(){
    loadAlbums();
    loadSingles();
}

void ArtistWindow::onDarkModeClicked(){
    isDarkMode = !isDarkMode;
    applyTheme();
}

void ArtistWindow::onLogoutClicked(){
    this->close();
    if(parentWidget()){
        parentWidget()->show();
    }
}

void ArtistWindow::applyTheme(){
    if(isDarkMode){
        this->setStyleSheet(DARK_STYLE);
        ui->darkModeButton->setText("☀️Light");
    }else{
        this->setStyleSheet(LIGHT_STYLE);
        ui->darkModeButton->setText("🌙 Dark");
    }
}

void ArtistWindow::onTabChanged(int index) {
    if (index == 0) {
        loadAlbums();
    } else if (index == 1) {
        int albumId = getSelectedItemId(ui->listWidget);
        if (albumId != -1) {
            loadSongs(albumId);
        } else {
            ui->listWidget_2->clear();
        }
    } else if (index == 2) {
        loadSingles();
    }
}

int ArtistWindow::getSelectedItemId(QListWidget* list) {
    QListWidgetItem* item = list->currentItem();
    if (item) {
        return item->data(Qt::UserRole).toInt();
    }
    return -1;
}

int ArtistWindow::getCurrentTab() {
    return ui->mainTabs->currentIndex();
}

void ArtistWindow::onAddClicked() {
    int currentTab = getCurrentTab();

    if(currentTab == 0){
        AddAlbumDialog dialog(this);
        if(dialog.exec() == QDialog::Accepted){
            QString name = dialog.getAlbumName();
            QImage cover = dialog.getCoverImage();

            if(!name.isEmpty()){
                try{
                    artistCtrl.createAlbum(currentArtsitId, name.toStdString(),cover);
                    refreshAll();
                    QMessageBox::information(this ,"Success", "Album created successfully!");
                }catch(const std::exception& e){
                    QMessageBox::warning(this,"Error",e.what());
                }
            }
        }
    }else if(currentTab == 1){
        int albumId = getSelectedItemId(ui->listWidget);
        if(albumId == -1){
            QMessageBox::warning(this, "Error", "Please select an album first.");
            return;
        }

        AddSongDialog dialog(this,albumId);
        if(dialog.exec() == QDialog::Accepted){
            try{
                QString title = dialog.getTitle();
                QString genre = dialog.getGenre();
                int year = dialog.getYear();
                QString filePath = dialog.getFilePath();

                artistCtrl.createSong(
                    currentArtsitId,
                    title.toStdString(),
                    genre.toStdString(),
                    year,
                    filePath.toStdString(),
                    albumId
                    );
                refreshAll();
                QMessageBox::information(this,"Success","Song added successfully!");

            }catch(const std::exception& e){
                QMessageBox::warning(this ,"Error",e.what() );
            }
        }
    }else if(currentTab == 2){
        AddSongDialog dialog(this,0);
        if(dialog.exec()==QDialog::Accepted){
            try{
                QString title = dialog.getTitle();
                QString genre = dialog.getGenre();
                int year = dialog.getYear();
                QString filePath = dialog.getFilePath();

                artistCtrl.createSong(
                    currentArtsitId,
                    title.toStdString(),
                    genre.toStdString(),
                    year,
                    filePath.toStdString(),
                    0
                    );
                refreshAll();
                QMessageBox::information(this , "Success", "Single added successfuly!");
            }catch(const std::exception& e){
                 QMessageBox::warning(this, "Error", e.what());
            }
        }
        }
}

void ArtistWindow::onEditClicked() {
    int currentTab = getCurrentTab();

    if(currentTab ==0){
        int albumId= getSelectedItemId(ui->listWidget);
        if(albumId == -1){
            QMessageBox::warning(this, "Error", "Please select an album first.");
            return;
        }

        auto albumOpt = artistCtrl.getAlbumById(albumId);
        if(!albumOpt.has_value()){
            QMessageBox::warning(this, "Error", "Album not found.");
            return;
        }

        Album album = albumOpt.value();
        EditAlbumDialog dialog(this);
        dialog.setAlbumName(QString::fromStdString(album.getName()));
        dialog.setCoverImage(album.getCover());

        if(dialog.exec() == QDialog::Accepted){
            QString newName = dialog.getAlbumName();
            QImage newCover = dialog.getCoverImage();
            try{
                artistCtrl.editAlbum(albumId,currentArtsitId, newName.toStdString(),{},newCover);
                loadAlbums();
                refreshAll();
                QMessageBox::information(this, "Success", "Album updated successfully!");
            }catch(const std::exception& e){
                QMessageBox::warning(this, "Error", e.what());
            }
        }
    }else if(currentTab == 1){
        int songId = getSelectedItemId(ui->listWidget_2);
        if(songId == -1){
            QMessageBox::warning(this, "Error", "Please select a song first.");
            return;
        }

        auto songOpt = artistCtrl.getSongById(songId);
        if(!songOpt.has_value()){
            QMessageBox::warning(this, "Error", "Song not found.");
            return;
        }

        Song song = songOpt.value();
        EditSongDialog dialog(this);
        dialog.setTitle(QString::fromStdString(song.getTitle()));
        dialog.setGenre(QString::fromStdString(song.getGenre()));
        dialog.setYear(song.getReleaseYear());
        dialog.setFilePath(QString::fromStdString(song.getFilePath()));

        if(dialog.exec() == QDialog::Accepted){
            try {
                artistCtrl.editSong(
                    currentArtsitId,
                    dialog.getTitle().toStdString(),
                    dialog.getGenre().toStdString(),
                    dialog.getYear(),
                    dialog.getFilePath().toStdString(),
                    songId,
                    song.getAlbumId()
                    );
                refreshAll();
                QMessageBox::information(this, "Success", "Song updated successfully!");
            } catch (const std::exception& e) {
                QMessageBox::warning(this, "Error", e.what());
            }
        }

    }else if(currentTab ==2){
        int songId = getSelectedItemId(ui->listWidget_3);
        if (songId == -1) {
            QMessageBox::warning(this, "Error", "Please select a single first.");
            return;
        }

        auto songOpt = artistCtrl.getSongById(songId);
        if (!songOpt.has_value()) {
            QMessageBox::warning(this, "Error", "Single not found.");
            return;
        }

        Song song = songOpt.value();
        EditSongDialog dialog(this);
        dialog.setTitle(QString::fromStdString(song.getTitle()));
        dialog.setGenre(QString::fromStdString(song.getGenre()));
        dialog.setYear(song.getReleaseYear());
        dialog.setFilePath(QString::fromStdString(song.getFilePath()));

        if (dialog.exec() == QDialog::Accepted) {
            try {
                artistCtrl.editSong(
                    currentArtsitId,
                    dialog.getTitle().toStdString(),
                    dialog.getGenre().toStdString(),
                    dialog.getYear(),
                    dialog.getFilePath().toStdString(),
                    songId,
                    0
                    );
                refreshAll();
                QMessageBox::information(this, "Success", "Single updated successfully!");
            } catch (const std::exception& e) {
                QMessageBox::warning(this, "Error", e.what());
            }
    }
    }
}

void ArtistWindow::onDeleteClicked() {
    int currentTab = getCurrentTab();

    if(currentTab ==0){
        int albumId = getSelectedItemId(ui->listWidget);
        if(albumId==-1){
            QMessageBox::warning(this, "Error", "Please select an album first.");
            return;
        }

        QMessageBox::StandardButton reply;
        reply =QMessageBox::question(this , "Confirm Delte","Are you sure you want to delete this album?",QMessageBox::Yes|QMessageBox::No);
        if(reply== QMessageBox::Yes){
            try{
                artistCtrl.deleteAlbum(albumId,currentArtsitId);
                refreshAll();
                QMessageBox::information(this,"Success", "Album deleted successfullt!");
            }catch(const std::exception& e){
                QMessageBox::warning(this, "Error", e.what());
            }
        }
    }else if(currentTab==1){
        int songId = getSelectedItemId(ui->listWidget_2);
        if(songId == -1){
            QMessageBox::warning(this, "Error", "Please select a song first.");
            return;
        }

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this,"Confirm Delte","Are you sure you want to delete this song?",QMessageBox::Yes|QMessageBox::No);
        if(reply == QMessageBox::Yes){
            try{
                artistCtrl.deleteSong(songId,currentArtsitId);
                refreshAll();
                QMessageBox::information(this,"Success", "Song deleted successfullt!");
            }catch(const std::exception& e){
                QMessageBox::warning(this, "Error", e.what());
            }
        }
    }else if(currentTab ==2){
        int songId = getSelectedItemId(ui->listWidget_3);
        if(songId ==-1){
            QMessageBox::warning(this,"Eror","Please enter a song first.");
            return;
        }

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Confirm Delete" , "Are you sure you want to delete this song?",QMessageBox::Yes | QMessageBox::No);
        if(reply == QMessageBox::Yes){
            try{
                artistCtrl.deleteSong(songId,currentArtsitId);
                refreshAll();
                QMessageBox::information(this,"Success", "Song deleted successfullt!");
            }catch(const std::exception& e){
                 QMessageBox::warning(this, "Error", e.what());
            }
        }
    }
}


void ArtistWindow::onSearchClicked() {
    QString query = ui->searchEdit->text().trimmed();
    int currentTab = getCurrentTab();

    if (query.isEmpty()) {
        refreshAll();
        return;
    }

    if (currentTab == 0) {

        std::vector<Album> albums = artistCtrl.getArtistAlbums(currentArtsitId);
        std::vector<Album> result;
        for (const auto& album : albums) {
            if (QString::fromStdString(album.getName()).contains(query, Qt::CaseInsensitive)) {
                result.push_back(album);
            }
        }

        ui->listWidget->clear();
        for (const auto& album : result) {
            QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(album.getName()));
            item->setData(Qt::UserRole, album.getId());
            ui->listWidget->addItem(item);
        }

    } else if (currentTab == 1) {

        int albumId = getSelectedItemId(ui->listWidget);
        if (albumId == -1) {
            QMessageBox::warning(this, "Error", "Please select an album first.");
            return;
        }
        std::vector<Song> songs = artistCtrl.getAlbumSongs(albumId);
        songs = SortHelper::searchByTitle(songs, query.toStdString());

        ui->listWidget_2->clear();
        for (const auto& song : songs) {
            QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(song.getTitle()));
            item->setData(Qt::UserRole, song.getId());
            ui->listWidget_2->addItem(item);
        }

    } else if (currentTab == 2) {

        std::vector<Song> songs = artistCtrl.getSingleSongs(currentArtsitId);
        songs = SortHelper::searchByTitle(songs, query.toStdString());

        ui->listWidget_3->clear();
        for (const auto& song : songs) {
            QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(song.getTitle()));
            item->setData(Qt::UserRole, song.getId());
            ui->listWidget_3->addItem(item);
        }
    }
}

void ArtistWindow::onFilterTypechanged(){
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

void ArtistWindow::onFilterValuechanged(){
    applyCurrentFilter();
}

void ArtistWindow::applyCurrentFilter(){
    int currentTab = getCurrentTab();
    QString filterType = ui->filterCombo->currentText();
    QString filterValue = ui->filterValueCombo->currentText();

    std::vector<Song> songs;
    if (currentTab == 1) {
        int albumId = getSelectedItemId(ui->listWidget);
        if (albumId == -1) return;
        songs = artistCtrl.getAlbumSongs(albumId);
    } else if (currentTab == 2) {
        songs = artistCtrl.getSingleSongs(currentArtsitId);
    } else {
        return;
    }

    if(filterType == "Genre" && !filterValue.isEmpty()){
        songs = SortHelper::filterByGenre(songs, filterValue.toStdString());
    }else if(filterType == "Year" && !filterValue.isEmpty()){
        songs = SortHelper::filterByYear(songs, filterValue.toInt());
    }

     QListWidget* targetList = (currentTab == 1) ? ui->listWidget_2 : ui->listWidget_3;
    targetList->clear();
     for (const auto& song : songs) {
         QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(song.getTitle()));
         item->setData(Qt::UserRole, song.getId());
         targetList->addItem(item);
     }
}

void ArtistWindow::onDeleteProfileClicked(){
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this , "Confirm Delete" , "Are you sure you want to delete this account?", QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes){
        try{
            appCtrl.deleteAccount(currentArtsitId,true);
            QMessageBox::information(this , "Succes" , "Account deleted successfully!");

            this->close();
            if(parentWidget()){
                parentWidget()->show();
            }
        }catch(const std::exception& e){
            QMessageBox::warning(this , "Error" , e.what());
        }
    }
}

void ArtistWindow::onEditProfileClicked(){
    auto accountOpt = appCtrl.getAccount(currentArtsitId,true);
    if(!accountOpt.has_value()){
        QMessageBox::warning(this, "Error", "Account not found.");
        return;
    }

    Account account = accountOpt.value();

    EditProfileDialog dialog(this);
    dialog.setFullName(QString::fromStdString(account.getFullName()));
    dialog.setUsername(QString::fromStdString(account.getUserName()));
    dialog.setPassword(QString::fromStdString(account.getPassword()));
    dialog.setProfileImage(account.getProfilePicture());

    if(dialog.exec() == QDialog::Accepted){
        try{
            appCtrl.editAccount(
                currentArtsitId,
                true,
                dialog.getFullName().toStdString(),
                dialog.getUsername().toStdString(),
                dialog.getPassword().toStdString(),
                dialog.getProfileImage()
                );
            auto updatedAccount = appCtrl.getAccount(currentArtsitId, true);
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
#include "loginwindow.h"
#include "registerwindow.h"
#include "ui_loginwindow.h"
#include<QMessageBox>
#include<QDebug>
LoginWindow::LoginWindow(AppController& AppController,ArtistController& artistController,ListenerController& listenerController,PlaylistRepository& playlistRepo , SongRepository& songRepo,AlbumRepository& albumRepo,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginWindow)
    ,appCtrl(AppController)
    ,artistCtrl(artistController)
    ,listenerCtrl(listenerController)
    ,playlistRepo(playlistRepo)
    ,songRepo(songRepo)
    ,albumRepo(albumRepo)
{
    ui->setupUi(this);
    connect(ui->loginButton, &QPushButton::clicked,this , &LoginWindow::onLoginClicked );
    connect(ui->registerButton, &QPushButton::clicked, this , &LoginWindow::onRegisterClicked);
    connect(ui->passwordEdit, &QLineEdit::returnPressed, this , &LoginWindow::onLoginClicked);
    connect(ui->togglePasswordButton, &QPushButton::clicked, this , &LoginWindow::onTogglePasswordClicked);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::onLoginClicked(){
    std::string username = ui->usernameEdit->text().toStdString();
    std::string password = ui->passwordEdit->text().toStdString();
    if(username == "" ){
        ui->errorLabel->setText("Please enter a username.");
        return;
    }
    if(password == ""){
        ui->errorLabel->setText("Please enter a password.");
        return;
    }

    try{
        Account account = appCtrl.login(username , password);

        ui->errorLabel->setText("");

        if(account.isArtist()){
            ArtistWindow* artistWin = new ArtistWindow(account.getId(), artistCtrl,appCtrl, nullptr);
            artistWin->setAttribute(Qt::WA_DeleteOnClose);
            artistWin->show();
            this->hide();
        }else{
              QMessageBox::information(this, "Info", "Listener window coming soon!");
        }

    }catch(const std::exception& e){
        ui->errorLabel->setText(e.what());
    }
}

void LoginWindow::onRegisterClicked()
{
    RegisterWindow registerWin(appCtrl,this);
    registerWin.setModal(true);
    registerWin.exec();

}

void LoginWindow::onTogglePasswordClicked(){
    if(ui->passwordEdit->echoMode() == QLineEdit::Password){
        ui->passwordEdit->setEchoMode(QLineEdit::Normal);
        ui->togglePasswordButton->setText("Hide");
    } else {
        ui->passwordEdit->setEchoMode(QLineEdit::Password);
        ui->togglePasswordButton->setText("Show");
    }
}
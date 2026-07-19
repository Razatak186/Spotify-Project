#include "addsongdialog.h"
#include "ui_addsongdialog.h"
#include<QMessageBox>
#include<QFileDialog>

AddSongDialog::AddSongDialog(QWidget *parent, int albumId)
    : QDialog(parent)
    , ui(new Ui::AddSongDialog)
    ,m_albumId(albumId)
{
    ui->setupUi(this);

    connect(ui->okButton,&QPushButton::clicked,this,&AddSongDialog::onOkclicked);
    connect(ui->cancelButton,&QPushButton::clicked,this,&AddSongDialog::onCancleClicked);
    connect(ui->browseButton,&QPushButton::clicked,this,&AddSongDialog::onBrowseClicked);
    ui->yearSpin->setValue(2026);
}

AddSongDialog::~AddSongDialog()
{
    delete ui;
}

QString AddSongDialog::getTitle()const{
    return ui->titleEdit->text().trimmed();
}

QString AddSongDialog::getGenre()const{
    return ui->genreEdit->text().trimmed();
}

int AddSongDialog::getYear()const{
    return ui->yearSpin->value();
}

QString AddSongDialog::getFilePath()const{
    return ui->fileEdit->text().trimmed();
}

int AddSongDialog::getAlbumId()const{
    return m_albumId;
}

void AddSongDialog::setalbumId(int id){
    m_albumId = id;
}

void AddSongDialog::onBrowseClicked(){
    QString filePath = QFileDialog::getOpenFileName(
        this,
        "Select Music File",
        "",
        "Audio Files (*.mp3 *.wav *.flac *.m4a);;All Files(*)"
        );
    if(!filePath.isEmpty()){
        ui->fileEdit->setText(filePath);
    }
}

void AddSongDialog::onOkclicked(){
    if(getTitle().isEmpty()){
        QMessageBox::warning(this, "Error", "Please enter a title.");
        ui->titleEdit->setFocus();
        return;
    }

    if(getGenre().isEmpty()){
        QMessageBox::warning(this, "Error", "Please enter a genre.");
        ui->genreEdit->setFocus();
        return;
    }

    if(getFilePath().isEmpty()){
        QMessageBox::warning(this, "Error", "Please select a music file.");
        ui->fileEdit->setFocus();
        return;
    }
    accept();

}

void AddSongDialog::onCancleClicked(){
    reject();
}
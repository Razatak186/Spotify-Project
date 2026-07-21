#include "editprofiledialog.h"
#include "ui_editprofiledialog.h"
#include<QMessageBox>
#include<QFileDialog>

EditProfileDialog::EditProfileDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditProfileDialog)
{
    ui->setupUi(this);

    connect(ui->saveButton, &QPushButton::clicked, this , &EditProfileDialog::onSaveClicked);
    connect(ui->cancelButton, &QPushButton::clicked , this , &EditProfileDialog::onCancelCLicked);
    connect(ui->choosePhotoButton,&QPushButton::clicked,this,&EditProfileDialog::onChoosePhotoClicked);
}

EditProfileDialog::~EditProfileDialog()
{
    delete ui;
}

void EditProfileDialog::setFullName( QString fullname){
    ui->fullNameEdit->setText(fullname);
}

void EditProfileDialog::setUsername(QString username){
    ui->usernameEdit->setText(username);
}

void EditProfileDialog::setPassword(QString password){
    ui->passwordEdit->setText(password);
}

QString EditProfileDialog::getFullName()const{
    return ui->fullNameEdit->text().trimmed();
}

QString EditProfileDialog::getUsername() const
{
    return ui->usernameEdit->text().trimmed();
}

QString EditProfileDialog::getPassword() const
{
    return ui->passwordEdit->text().trimmed();
}

void EditProfileDialog::onSaveClicked(){
    if(getFullName().isEmpty()){
        QMessageBox::warning(this, "Error", "Please enter a full name.");
        ui->fullNameEdit->setFocus();
        return;
    }

    if (getUsername().isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter a username.");
        ui->usernameEdit->setFocus();
        return;
    }

    if (getPassword().isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter a password.");
        ui->passwordEdit->setFocus();
        return;
    }

    accept();
}

void EditProfileDialog::onCancelCLicked(){
    reject();
}

void EditProfileDialog::setProfileImage(const QImage& image){
    profileImage = image;
    if(!image.isNull()){
        QPixmap pixmap = QPixmap::fromImage(image);
        ui->photoLabel->setPixmap(pixmap.scaled(80,80,Qt::KeepAspectRatio,Qt::SmoothTransformation));
        ui->photoLabel->setScaledContents(true);
    }else{
        ui->photoLabel->setText("👤");
    }
}

QImage EditProfileDialog::getProfileImage()const{
    return profileImage;
}

void EditProfileDialog::onChoosePhotoClicked() {
    QString filePath = QFileDialog::getOpenFileName(
        this,
        "Select Profile Picture",
        "",
        "Images (*.png *.jpg *.jpeg *.bmp *.gif)"
        );
    if (!filePath.isEmpty()) {
        profileImage.load(filePath);
        QPixmap pixmap = QPixmap::fromImage(profileImage);
        ui->photoLabel->setPixmap(pixmap.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->photoLabel->setScaledContents(true);
    }
}
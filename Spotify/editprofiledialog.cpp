#include "editprofiledialog.h"
#include "ui_editprofiledialog.h"
#include<QMessageBox>

EditProfileDialog::EditProfileDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditProfileDialog)
{
    ui->setupUi(this);

    connect(ui->saveButton, &QPushButton::clicked, this , &EditProfileDialog::onSaveClicked);
    connect(ui->cancelButton, &QPushButton::clicked , this , &EditProfileDialog::onCancelCLicked);
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
#include "registerwindow.h"
#include "ui_registerwindow.h"
#include<QMessageBox>
RegisterWindow::RegisterWindow(AppController& appController,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterWindow)
    ,appCtrl(appController)
{
    ui->setupUi(this);
    connect(ui->togglePasswordButton, &QToolButton::clicked, this, [this]() {
        if (ui->passwordEdit->echoMode() == QLineEdit::Password) {
            ui->passwordEdit->setEchoMode(QLineEdit::Normal);
            ui->togglePasswordButton->setText("Hide");
        } else {
            ui->passwordEdit->setEchoMode(QLineEdit::Password);
            ui->togglePasswordButton->setText("Show");
        }
    });
    connect(ui->registerButton, &QPushButton::clicked, this , &RegisterWindow::onRegisterClicked);
    connect(ui->cancelButton, &QPushButton::clicked, this , &RegisterWindow::onCancelClicked);
}

RegisterWindow::~RegisterWindow()
{
    delete ui;
}

void RegisterWindow::onRegisterClicked(){
    std::string fullname = ui->fullnameEdit->text().toStdString();
    std::string username = ui->usernameEdit->text().toStdString();
    std::string password = ui->passwordEdit->text().toStdString();
    std::string bio = ui->bio->toPlainText().toStdString();

    int role;
    if(ui->artistRadio->isChecked()){
        role=1;
    }else{
        role =0;
    }

    if (fullname.empty() || username.empty() || password.empty()) {
        ui->errorLabel->setText("Please fill in all fields.");
        return;
    }

    try{
        appCtrl.registeration(fullname , username,password,role);

        ui->errorLabel->setText("");
        QMessageBox::information(this, "Success", "Account created successfully!");
        this->hide();
        if (parentWidget()) {
            parentWidget()->show();
        }
    }catch(const std::exception& e){
        ui->errorLabel->setText(e.what());
    }
}

void RegisterWindow::onCancelClicked(){
    this->close();
    if (parentWidget()) {
        parentWidget()->show();
    }
}
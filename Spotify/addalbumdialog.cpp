#include "addalbumdialog.h"
#include "ui_addalbumdialog.h"
#include<QMessageBox>
AddAlbumDialog::AddAlbumDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddAlbumDialog)
{
    ui->setupUi(this);

    connect(ui->okButton,&QPushButton::clicked,this,&AddAlbumDialog::onOKClicked);
    connect(ui->cancelButton,&QPushButton::clicked,this,&AddAlbumDialog::onCancelclicked);
}

AddAlbumDialog::~AddAlbumDialog()
{
    delete ui;
}

QString AddAlbumDialog::getAlbumName()const{
    return ui->nameEdit->text().trimmed();
}

void AddAlbumDialog::onOKClicked(){
    if(getAlbumName().isEmpty()){
         QMessageBox::information(this, "Error", "Please enter a album name.");
        return;
    }
    accept();
}

void AddAlbumDialog::onCancelclicked(){
    reject();
}
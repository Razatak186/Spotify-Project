#include "editalbumdialog.h"
#include "ui_editalbumdialog.h"
#include<QMessageBox>

EditAlbumDialog::EditAlbumDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditAlbumDialog)
{
    ui->setupUi(this);

    connect(ui->okButton,&QPushButton::clicked,this, &EditAlbumDialog::onOkClicked);
    connect(ui->cancelButton,&QPushButton::clicked,this,&EditAlbumDialog::onCancelClicked);
}

EditAlbumDialog::~EditAlbumDialog()
{
    delete ui;
}

void EditAlbumDialog::setAlbumName(const QString& name){
    ui->nameEdit->setText(name);
}

QString EditAlbumDialog::getAlbumName()const{
    return ui->nameEdit->text().trimmed();
}

void EditAlbumDialog::onOkClicked(){
    if(getAlbumName().isEmpty()){
        QMessageBox::warning(this, "Error", "Please enter an album name.");
        return;
    }
    accept();
}

void EditAlbumDialog::onCancelClicked()
{
    reject();
}
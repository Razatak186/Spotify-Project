#include "editplaylistdialog.h"
#include "ui_editplaylistdialog.h"
#include<QMessageBox>

EditPlaylistDialog::EditPlaylistDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditPlaylistDialog)
{
    ui->setupUi(this);

    connect(ui->okButton,&QPushButton::clicked,this,&EditPlaylistDialog::onOkClicked);
    connect(ui->cancelButton,&QPushButton::clicked,this, &EditPlaylistDialog::onCancelClicked);
}

EditPlaylistDialog::~EditPlaylistDialog()
{
    delete ui;
}

QString EditPlaylistDialog::getPlaylistName()const{
    return ui->nameEdit->text().trimmed();
}

void EditPlaylistDialog::setPlaylistName(const QString& name){
    ui->nameEdit->setText(name);
}

void EditPlaylistDialog::onOkClicked(){
    if(getPlaylistName().isEmpty()){
        QMessageBox::warning(this, "Error", "Please enter a playlist name.");
        ui->nameEdit->setFocus();
        return;
    }
    accept();
}

void EditPlaylistDialog::onCancelClicked(){
    reject();
}
#include "addplaylistdialog.h"
#include "ui_addplaylistdialog.h"
#include<QMessageBox>

AddPlaylistDialog::AddPlaylistDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddPlaylistDialog)
{
    ui->setupUi(this);

    connect(ui->okButton,&QPushButton::clicked,this, &AddPlaylistDialog::onOkClicked);
    connect(ui->cancelButton,&QPushButton::clicked,this,&AddPlaylistDialog::onCancelClicked);
}

AddPlaylistDialog::~AddPlaylistDialog()
{
    delete ui;
}

QString AddPlaylistDialog::getPlaylistName()const{
    return ui->nameEdit->text().trimmed();
}

void AddPlaylistDialog::onOkClicked(){
    if(getPlaylistName().isEmpty()){
        QMessageBox::warning(this, "Error", "Please enter a playlist name.");
        ui->nameEdit->setFocus();
        return;
    }
    accept();
}

void AddPlaylistDialog::onCancelClicked(){
    reject();
}

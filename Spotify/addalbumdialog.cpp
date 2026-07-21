#include "addalbumdialog.h"
#include "ui_addalbumdialog.h"
#include<QMessageBox>
#include<QFileDialog>

AddAlbumDialog::AddAlbumDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddAlbumDialog)
{
    ui->setupUi(this);

    connect(ui->okButton,&QPushButton::clicked,this,&AddAlbumDialog::onOKClicked);
    connect(ui->cancelButton,&QPushButton::clicked,this,&AddAlbumDialog::onCancelclicked);
    connect(ui->chooseCoverButton,&QPushButton::clicked,this,&AddAlbumDialog::onChooseCoverClicked);
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

void AddAlbumDialog::onChooseCoverClicked(){
    QString filePath = QFileDialog::getOpenFileName(
        this,
        "Select Album Cover",
        "",
        "Images(*.png *.jpg *.jpeg *.gif)"
        );
    if(!filePath.isEmpty()){
        coverImage.load(filePath);
        QPixmap pixmap = QPixmap::fromImage(coverImage);
        ui->coverLabel->setPixmap(pixmap.scaled(100,100,Qt::KeepAspectRatio,Qt::SmoothTransformation));
        ui->coverLabel->setScaledContents(true);
    }
}

QImage AddAlbumDialog::getCoverImage()const{

    return coverImage;
}
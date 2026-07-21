#include "editalbumdialog.h"
#include "ui_editalbumdialog.h"
#include<QMessageBox>
#include<QFileDialog>

EditAlbumDialog::EditAlbumDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditAlbumDialog)
{
    ui->setupUi(this);

    connect(ui->okButton,&QPushButton::clicked,this, &EditAlbumDialog::onOkClicked);
    connect(ui->cancelButton,&QPushButton::clicked,this,&EditAlbumDialog::onCancelClicked);
    connect(ui->chooseCoverButton,&QPushButton::clicked,this,&EditAlbumDialog::onChooseCoverClicked);
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

void EditAlbumDialog::setCoverImage(const QImage& cover){
    coverImage = cover;
    if (!cover.isNull()) {
        QPixmap pixmap = QPixmap::fromImage(cover);
        ui->coverLabel->setPixmap(pixmap.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->coverLabel->setScaledContents(true);
    }else{
        ui->coverLabel->setText("📷");
        ui->coverLabel->setAlignment(Qt::AlignCenter);
    }
}

QImage EditAlbumDialog::getCoverImage()const{
    return coverImage;
}

void EditAlbumDialog::onChooseCoverClicked(){
    QString filePath = QFileDialog::getOpenFileName(
        this,
        "Select Album Cover",
        "",
        "Images (*.png *.jpg *.jpeg *.bmp *.gif)"
        );
    if (!filePath.isEmpty()) {
        coverImage.load(filePath);
        QPixmap pixmap = QPixmap::fromImage(coverImage);
        ui->coverLabel->setPixmap(pixmap.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->coverLabel->setScaledContents(true);
    }
}
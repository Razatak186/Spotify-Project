#include "editsongdialog.h"
#include "ui_editsongdialog.h"
#include<QMessageBox>
#include<QFileDialog>

EditSongDialog::EditSongDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditSongDialog)
{
    ui->setupUi(this);

    connect(ui->okButton, &QPushButton::clicked, this, &EditSongDialog::onOkClicked);
    connect(ui->cancelButton, &QPushButton::clicked, this, &EditSongDialog::onCancelClicked);
    connect(ui->browseButton, &QPushButton::clicked, this, &EditSongDialog::onBrowseClicked);
    ui->yearSpin->setValue(2026);
}

EditSongDialog::~EditSongDialog()
{
    delete ui;
}

void EditSongDialog::setTitle(const QString& title)
{
    ui->titleEdit->setText(title);
}

void EditSongDialog::setGenre(const QString& genre)
{
    ui->genreEdit->setText(genre);
}

void EditSongDialog::setYear(int year)
{
    ui->yearSpin->setValue(year);
}

void EditSongDialog::setFilePath(const QString& filePath)
{
    ui->fileEdit->setText(filePath);
}

QString EditSongDialog::getTitle() const
{
    return ui->titleEdit->text().trimmed();
}

QString EditSongDialog::getGenre() const
{
    return ui->genreEdit->text().trimmed();
}

int EditSongDialog::getYear() const
{
    return ui->yearSpin->value();
}

QString EditSongDialog::getFilePath() const
{
    return ui->fileEdit->text().trimmed();
}

void EditSongDialog::onBrowseClicked()
{
    QString filePath = QFileDialog::getOpenFileName(
        this,
        "Select Music File",
        "",
        "Audio Files (*.mp3 *.wav *.flac *.m4a);;All Files (*)"
        );
    if (!filePath.isEmpty()) {
        ui->fileEdit->setText(filePath);
    }
}

void EditSongDialog::onOkClicked()
{
    if (getTitle().isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter a title.");
        ui->titleEdit->setFocus();
        return;
    }

    if (getGenre().isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter a genre.");
        ui->genreEdit->setFocus();
        return;
    }

    if (getFilePath().isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select a music file.");
        ui->fileEdit->setFocus();
        return;
    }

    accept();
}

void EditSongDialog::onCancelClicked()
{
    reject();
}

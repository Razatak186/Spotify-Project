#include "selectplaylistdialog.h"
#include "ui_selectplaylistdialog.h"
#include<QMessageBox>

SelectPlaylistDialog::SelectPlaylistDialog(const std::vector<Playlist>& playlists,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SelectPlaylistDialog)
    ,selectedPlaylistId(-1)
{
    ui->setupUi(this);

    for(const auto& playlist : playlists){
        if(playlist.getName() == "Favorite Songs") continue;

        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(playlist.getName()));
        item->setData(Qt::UserRole,playlist.getId());
        ui->playlistList->addItem(item);
    }

    connect(ui->addButton,&QPushButton::clicked,this,&SelectPlaylistDialog::onAddClicked);
    connect(ui->cancelButton, &QPushButton::clicked, this, &SelectPlaylistDialog::onCancelClicked);
    connect(ui->playlistList, &QListWidget::itemDoubleClicked, this, &SelectPlaylistDialog::onItemDoubleClicked);
}

SelectPlaylistDialog::~SelectPlaylistDialog()
{
    delete ui;
}

int SelectPlaylistDialog::getSelectedPlaylistId() const
{
    return selectedPlaylistId;
}

void SelectPlaylistDialog::onAddClicked()
{
    QListWidgetItem* item = ui->playlistList->currentItem();
    if (!item) {
        QMessageBox::warning(this, "Error", "Please select a playlist.");
        return;
    }
    selectedPlaylistId = item->data(Qt::UserRole).toInt();
    accept();
}

void SelectPlaylistDialog::onCancelClicked()
{
    reject();
}

void SelectPlaylistDialog::onItemDoubleClicked(QListWidgetItem* item)
{
    if (item) {
        selectedPlaylistId = item->data(Qt::UserRole).toInt();
        accept();
    }
}
#ifndef SELECTPLAYLISTDIALOG_H
#define SELECTPLAYLISTDIALOG_H

#include "qlistwidget.h"
#include <QDialog>
#include<vector>
#include<playlist.h>


namespace Ui {
class SelectPlaylistDialog;
}

class SelectPlaylistDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelectPlaylistDialog(const std::vector<Playlist>& playlists,QWidget *parent = nullptr);
    ~SelectPlaylistDialog();

    int getSelectedPlaylistId()const;
private slots:
    void onAddClicked();
    void onCancelClicked();
    void onItemDoubleClicked(QListWidgetItem* item);
private:
    Ui::SelectPlaylistDialog *ui;
    int selectedPlaylistId;
};

#endif // SELECTPLAYLISTDIALOG_H

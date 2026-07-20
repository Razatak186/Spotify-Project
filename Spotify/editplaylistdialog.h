#ifndef EDITPLAYLISTDIALOG_H
#define EDITPLAYLISTDIALOG_H

#include <QDialog>

namespace Ui {
class EditPlaylistDialog;
}

class EditPlaylistDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditPlaylistDialog(QWidget *parent = nullptr);
    ~EditPlaylistDialog();

    QString getPlaylistName()const;
    void setPlaylistName(const QString& name);

private slots:
    void onOkClicked();
    void onCancelClicked();
private:
    Ui::EditPlaylistDialog *ui;
};

#endif // EDITPLAYLISTDIALOG_H

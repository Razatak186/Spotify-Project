#ifndef EDITALBUMDIALOG_H
#define EDITALBUMDIALOG_H

#include <QDialog>

namespace Ui {
class EditAlbumDialog;
}

class EditAlbumDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditAlbumDialog(QWidget *parent = nullptr);
    ~EditAlbumDialog();

    void setAlbumName(const QString& name);
    QString getAlbumName()const;
private slots:
    void onOkClicked();
    void onCancelClicked();
private:
    Ui::EditAlbumDialog *ui;
};

#endif // EDITALBUMDIALOG_H

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

    void setCoverImage(const QImage& cover);
    QImage getCoverImage()const;
private slots:
    void onOkClicked();
    void onCancelClicked();
    void onChooseCoverClicked();
private:
    Ui::EditAlbumDialog *ui;
    QImage coverImage;
};

#endif // EDITALBUMDIALOG_H

#ifndef ADDALBUMDIALOG_H
#define ADDALBUMDIALOG_H

#include <QDialog>

namespace Ui {
class AddAlbumDialog;
}

class AddAlbumDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddAlbumDialog(QWidget *parent = nullptr);
    ~AddAlbumDialog();

    QString getAlbumName()const;
    QImage getCoverImage()const;
private slots:
    void onOKClicked();
    void onCancelclicked();
    void onChooseCoverClicked();
private:
    Ui::AddAlbumDialog *ui;
    QImage coverImage;
};

#endif // ADDALBUMDIALOG_H

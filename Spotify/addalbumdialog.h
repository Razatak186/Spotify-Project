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
private slots:
    void onOKClicked();
    void onCancelclicked();
private:
    Ui::AddAlbumDialog *ui;
};

#endif // ADDALBUMDIALOG_H

#ifndef ADDSONGDIALOG_H
#define ADDSONGDIALOG_H

#include <QDialog>
#include<QFileDialog>

namespace Ui {
class AddSongDialog;
}

class AddSongDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddSongDialog(QWidget *parent = nullptr,int albumId=0);
    ~AddSongDialog();

    QString getTitle()const;
    QString getGenre()const;
    int getYear()const;
    QString getFilePath()const;
    int getAlbumId()const;

    void setalbumId(int id);
private slots:
    void onOkclicked();
    void onCancleClicked();
    void onBrowseClicked();
private:
    Ui::AddSongDialog *ui;
    int m_albumId;
};

#endif // ADDSONGDIALOG_H

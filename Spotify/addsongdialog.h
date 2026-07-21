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
    void setSongImage(const QImage& image);
    QImage getSongImage()const;
private slots:
    void onOkclicked();
    void onCancleClicked();
    void onBrowseClicked();
    void onChooseImageClicked();
private:
    Ui::AddSongDialog *ui;
    int m_albumId;
    QImage songImage;
};

#endif // ADDSONGDIALOG_H

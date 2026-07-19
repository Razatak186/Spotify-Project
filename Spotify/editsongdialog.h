#ifndef EDITSONGDIALOG_H
#define EDITSONGDIALOG_H

#include <QDialog>

namespace Ui {
class EditSongDialog;
}

class EditSongDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditSongDialog(QWidget *parent = nullptr);
    ~EditSongDialog();

    void setTitle(const QString& title);
    void setGenre(const QString& genre);
    void setYear(int year);
    void setFilePath(const QString& filePath);

    QString getTitle() const;
    QString getGenre() const;
    int getYear() const;
    QString getFilePath() const;

private slots:
    void onOkClicked();
    void onCancelClicked();
    void onBrowseClicked();
private:
    Ui::EditSongDialog *ui;
};

#endif // EDITSONGDIALOG_H

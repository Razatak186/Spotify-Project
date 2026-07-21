#ifndef EDITPROFILEDIALOG_H
#define EDITPROFILEDIALOG_H

#include <QDialog>

namespace Ui {
class EditProfileDialog;
}

class EditProfileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditProfileDialog(QWidget *parent = nullptr);
    ~EditProfileDialog();

    void setFullName(QString);
    void setUsername(QString);
    void setPassword(QString);

    QString getFullName()const;
    QString getUsername()const;
    QString getPassword()const;

    void setProfileImage(const QImage& image);
    QImage getProfileImage()const;

private slots:
    void onSaveClicked();
    void onCancelCLicked();
    void onChoosePhotoClicked();
private:
    Ui::EditProfileDialog *ui;
    QImage profileImage;

};

#endif // EDITPROFILEDIALOG_H

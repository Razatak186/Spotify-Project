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

private slots:
    void onSaveClicked();
    void onCancelCLicked();

private:
    Ui::EditProfileDialog *ui;


};

#endif // EDITPROFILEDIALOG_H

#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QDialog>
#include<appcontroller.h>
namespace Ui {
class RegisterWindow;
}

class RegisterWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterWindow(AppController& appController,QWidget *parent = nullptr);
    ~RegisterWindow();

private slots:
    void onRegisterClicked();
    void onCancelClicked();
private:
    Ui::RegisterWindow *ui;
    AppController& appCtrl;
};

#endif // REGISTERWINDOW_H

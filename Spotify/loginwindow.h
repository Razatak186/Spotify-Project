#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H
#include<appcontroller.h>
#include <QWidget>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(AppController& appController,QWidget *parent = nullptr);
    ~LoginWindow();
private slots:
    void onLoginClicked();
    void onRegisterClicked();
    void onTogglePasswordClicked();
private:
    Ui::LoginWindow *ui;
    AppController& appCtrl;
};

#endif // LOGINWINDOW_H

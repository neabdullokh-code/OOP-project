#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include "databasemanager.h"
#include "authcontroller.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class LoginWindow;
}
QT_END_NAMESPACE

class RegistrationWindow;
class AdminWindow;
class TeacherWindow;
class StudentWindow;

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(DatabaseManager *databaseManager, QWidget *parent = 0);
    ~LoginWindow();

private: slots:
    void onLoginClicked();
    void onOpenRegistrationClicked();
    void onLogoutToLogin();

private:
    Ui::LoginWindow *ui;
    DatabaseManager *m_databaseManager;
    AuthController m_authController;
    RegistrationWindow *m_registrationWindow;
    AdminWindow *m_adminWindow;
    TeacherWindow *m_teacherWindow;
    StudentWindow *m_studentWindow;
};

#endif

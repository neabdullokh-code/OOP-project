#ifndef REGISTRATIONWINDOW_H
#define REGISTRATIONWINDOW_H

#include <QMainWindow>
#include "core/authcontroller.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class RegistrationWindow;
}
QT_END_NAMESPACE

class RegistrationWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegistrationWindow(DatabaseManager *databaseManager, QWidget *parent = 0);
    ~RegistrationWindow();

signals:
    void backToLoginRequested();

private slots:
    void onRegisterStudentClicked();
    void onRegisterTeacherClicked();
    void onBackClicked();

private:
    void doRegister(const QString &role);

    Ui::RegistrationWindow *ui;
    AuthController m_authController;
};

#endif

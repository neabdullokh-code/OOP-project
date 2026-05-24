#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "registrationwindow.h"
#include "adminwindow.h"
#include "teacherwindow.h"
#include "studentwindow.h"

LoginWindow::LoginWindow(DatabaseManager *databaseManager, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::LoginWindow),
      m_databaseManager(databaseManager),
      m_authController(databaseManager),
      m_registrationWindow(0),
      m_adminWindow(0),
      m_teacherWindow(0),
      m_studentWindow(0)
{
    ui->setupUi(this);

    connect(ui->loginButton, SIGNAL(clicked()), this, SLOT(onLoginClicked()));
    connect(ui->openRegistrationButton, SIGNAL(clicked()), this, SLOT(onOpenRegistrationClicked()));

    ui->hintLabel->setText("Default admin: admin / admin123");
    ui->statusLabel->setText("");
}

LoginWindow::~LoginWindow()
{
    delete m_registrationWindow;
    delete m_adminWindow;
    delete m_teacherWindow;
    delete m_studentWindow;
    delete ui;
}

void LoginWindow::onLoginClicked()
{
    QString login = ui->loginLineEdit->text().trimmed();
    QString password = ui->passwordLineEdit->text();

    User *user = m_authController.login(login, password);
    if (user == 0)
    {
        ui->statusLabel->setText("Invalid username or password.");
        return;
    }

    ui->statusLabel->setText("");
    hide();

    if (user->getRole() == RoleAdmin)
    {
        if (m_adminWindow != 0)
        {
            delete m_adminWindow;
        }
        m_adminWindow = new AdminWindow(m_databaseManager);
        connect(m_adminWindow, SIGNAL(logoutRequested()), this, SLOT(onLogoutToLogin()));
        m_adminWindow->show();
        return;
    }

    if (user->getRole() == RoleTeacher)
    {
        if (m_teacherWindow != 0)
        {
            delete m_teacherWindow;
        }
        m_teacherWindow = new TeacherWindow(m_databaseManager, user->getId());
        connect(m_teacherWindow, SIGNAL(logoutRequested()), this, SLOT(onLogoutToLogin()));
        m_teacherWindow->show();
        return;
    }

    if (m_studentWindow != 0)
    {
        delete m_studentWindow;
    }
    m_studentWindow = new StudentWindow(m_databaseManager, user->getId());
    connect(m_studentWindow, SIGNAL(logoutRequested()), this, SLOT(onLogoutToLogin()));
    m_studentWindow->show();
}

void LoginWindow::onOpenRegistrationClicked()
{
    if (m_registrationWindow != 0)
    {
        delete m_registrationWindow;
    }
    m_registrationWindow = new RegistrationWindow(m_databaseManager);
    connect(m_registrationWindow, SIGNAL(backToLoginRequested()), this, SLOT(onLogoutToLogin()));
    hide();
    m_registrationWindow->show();
}

void LoginWindow::onLogoutToLogin()
{
    if (m_registrationWindow != 0)
    {
        m_registrationWindow->hide();
    }
    if (m_adminWindow != 0)
    {
        m_adminWindow->hide();
    }
    if (m_teacherWindow != 0)
    {
        m_teacherWindow->hide();
    }
    if (m_studentWindow != 0)
    {
        m_studentWindow->hide();
    }

    ui->passwordLineEdit->clear();
    ui->statusLabel->setText("");
    show();
}

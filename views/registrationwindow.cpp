#include "registrationwindow.h"
#include "ui_registrationwindow.h"
#include <QMessageBox>

RegistrationWindow::RegistrationWindow(DatabaseManager *databaseManager, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::RegistrationWindow),
      m_authController(databaseManager)
{
    ui->setupUi(this);
    connect(ui->registerStudentButton, SIGNAL(clicked()), this, SLOT(onRegisterStudentClicked()));
    connect(ui->registerTeacherButton, SIGNAL(clicked()), this, SLOT(onRegisterTeacherClicked()));
    connect(ui->backButton, SIGNAL(clicked()), this, SLOT(onBackClicked()));
}

RegistrationWindow::~RegistrationWindow()
{
    delete ui;
}

void RegistrationWindow::onRegisterStudentClicked()
{
    doRegister("student");
}

void RegistrationWindow::onRegisterTeacherClicked()
{
    doRegister("teacher");
}

void RegistrationWindow::doRegister(const QString &role)
{
    QString fullName = ui->fullNameLineEdit->text().trimmed();
    QString login = ui->loginLineEdit->text().trimmed();
    QString password = ui->passwordLineEdit->text();
    QString repeatPassword = ui->repeatPasswordLineEdit->text();

    if (fullName.isEmpty() || login.isEmpty() || password.isEmpty())
    {
        QMessageBox::warning(this, "Error", "Please fill in all fields.");
        return;
    }
    if (password != repeatPassword)
    {
        QMessageBox::warning(this, "Error", "Passwords do not match.");
        return;
    }

    if (!m_authController.registerUser(fullName, login, password, role))
    {
        QMessageBox::warning(this, "Error", "Failed to register user.");
        return;
    }

    QMessageBox::information(this, "Success", "Registration successful. You can now log in.");
    close();
    emit backToLoginRequested();
}

void RegistrationWindow::onBackClicked()
{
    close();
    emit backToLoginRequested();
}

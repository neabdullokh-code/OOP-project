#include "registrationwindow.h"
#include "ui_registrationwindow.h"

RegistrationWindow::RegistrationWindow(FileManager *fileManager, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::RegistrationWindow),
      m_fileManager(fileManager)
{
    ui->setupUi(this);
    connect(ui->registerStudentButton, SIGNAL(clicked()), this, SLOT(onRegisterStudentClicked()));
    connect(ui->registerTeacherButton, SIGNAL(clicked()), this, SLOT(onRegisterTeacherClicked()));
    connect(ui->backButton, SIGNAL(clicked()), this, SLOT(onBackClicked()));
    ui->statusLabel->setText("");
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
        ui->statusLabel->setText("Please fill in all fields.");
        return;
    }
    if (password != repeatPassword)
    {
        ui->statusLabel->setText("Passwords do not match.");
        return;
    }

    if (!m_fileManager->registerUser(fullName, login, password, role))
    {
        ui->statusLabel->setText("Failed to register user.");
        return;
    }

    ui->statusLabel->setText("Registration successful. You can now log in.");
    close();
    emit backToLoginRequested();
}

void RegistrationWindow::onBackClicked()
{
    close();
    emit backToLoginRequested();
}

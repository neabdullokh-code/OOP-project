#include "registrationwindow.h"
#include "ui_registrationwindow.h"
#include <QPushButton>

RegistrationWindow::RegistrationWindow(FileManager *fileManager, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::RegistrationWindow),
      m_fileManager(fileManager)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowCloseButtonHint);
    connect(ui->registerStudentButton, &QPushButton::clicked,
            this, &RegistrationWindow::onRegisterStudentClicked);
    connect(ui->registerTeacherButton, &QPushButton::clicked,
            this, &RegistrationWindow::onRegisterTeacherClicked);
    connect(ui->backButton, &QPushButton::clicked,
            this, &RegistrationWindow::onBackClicked);
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

void RegistrationWindow::doRegister(QString role)
{
    QString fullName = ui->fullNameLineEdit->text().trimmed();
    QString login = ui->loginLineEdit->text().trimmed();
    QString password = ui->passwordLineEdit->text();
    QString repeatPassword = ui->repeatPasswordLineEdit->text();

    if (fullName.isEmpty() || login.isEmpty() || password.isEmpty())
    {
        ui->statusLabel->setText("Fill in all fields.");
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

    ui->statusLabel->setText("Account created. You can log in now.");
    hide();
    emit backToLoginRequested();
}

void RegistrationWindow::onBackClicked()
{
    hide();
    emit backToLoginRequested();
}

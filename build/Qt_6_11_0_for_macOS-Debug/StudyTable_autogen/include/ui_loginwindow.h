/********************************************************************************
** Form generated from reading UI file 'loginwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QLabel *infoLabel;
    QLineEdit *loginLineEdit;
    QLineEdit *passwordLineEdit;
    QPushButton *loginButton;
    QPushButton *openRegistrationButton;
    QLabel *hintLabel;
    QLabel *statusLabel;

    void setupUi(QMainWindow *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName("LoginWindow");
        LoginWindow->resize(420, 520);
        centralwidget = new QWidget(LoginWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        titleLabel = new QLabel(centralwidget);
        titleLabel->setObjectName("titleLabel");

        verticalLayout->addWidget(titleLabel);

        infoLabel = new QLabel(centralwidget);
        infoLabel->setObjectName("infoLabel");

        verticalLayout->addWidget(infoLabel);

        loginLineEdit = new QLineEdit(centralwidget);
        loginLineEdit->setObjectName("loginLineEdit");

        verticalLayout->addWidget(loginLineEdit);

        passwordLineEdit = new QLineEdit(centralwidget);
        passwordLineEdit->setObjectName("passwordLineEdit");
        passwordLineEdit->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(passwordLineEdit);

        loginButton = new QPushButton(centralwidget);
        loginButton->setObjectName("loginButton");

        verticalLayout->addWidget(loginButton);

        openRegistrationButton = new QPushButton(centralwidget);
        openRegistrationButton->setObjectName("openRegistrationButton");

        verticalLayout->addWidget(openRegistrationButton);

        hintLabel = new QLabel(centralwidget);
        hintLabel->setObjectName("hintLabel");
        hintLabel->setWordWrap(true);

        verticalLayout->addWidget(hintLabel);

        statusLabel = new QLabel(centralwidget);
        statusLabel->setObjectName("statusLabel");

        verticalLayout->addWidget(statusLabel);

        LoginWindow->setCentralWidget(centralwidget);

        retranslateUi(LoginWindow);

        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QMainWindow *LoginWindow)
    {
        LoginWindow->setWindowTitle(QCoreApplication::translate("LoginWindow", "Study.Table - Login", nullptr));
        titleLabel->setText(QCoreApplication::translate("LoginWindow", "Study.Table", nullptr));
        infoLabel->setText(QCoreApplication::translate("LoginWindow", "Enter your username and password to log in.", nullptr));
        loginLineEdit->setPlaceholderText(QCoreApplication::translate("LoginWindow", "Username", nullptr));
        passwordLineEdit->setPlaceholderText(QCoreApplication::translate("LoginWindow", "Password", nullptr));
        loginButton->setText(QCoreApplication::translate("LoginWindow", "Log In", nullptr));
        openRegistrationButton->setText(QCoreApplication::translate("LoginWindow", "Create New Account", nullptr));
        hintLabel->setText(QCoreApplication::translate("LoginWindow", "Test accounts:\n"
"admin / admin123\n"
"karimov / pass123 (teacher)\n"
"yusupova / pass123 (teacher)\n"
"tursunova / pass123 (student)\n"
"ismoilov / pass123 (student)\n"
"abdullayev / pass123 (student)", nullptr));
        statusLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H

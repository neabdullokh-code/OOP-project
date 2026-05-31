/********************************************************************************
** Form generated from reading UI file 'registrationwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTRATIONWINDOW_H
#define UI_REGISTRATIONWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegistrationWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QLabel *infoLabel;
    QLineEdit *fullNameLineEdit;
    QLineEdit *loginLineEdit;
    QLineEdit *passwordLineEdit;
    QLineEdit *repeatPasswordLineEdit;
    QLabel *roleHintLabel;
    QPushButton *registerStudentButton;
    QPushButton *registerTeacherButton;
    QPushButton *backButton;
    QLabel *statusLabel;

    void setupUi(QMainWindow *RegistrationWindow)
    {
        if (RegistrationWindow->objectName().isEmpty())
            RegistrationWindow->setObjectName("RegistrationWindow");
        RegistrationWindow->resize(520, 480);
        centralwidget = new QWidget(RegistrationWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        titleLabel = new QLabel(centralwidget);
        titleLabel->setObjectName("titleLabel");

        verticalLayout->addWidget(titleLabel);

        infoLabel = new QLabel(centralwidget);
        infoLabel->setObjectName("infoLabel");
        infoLabel->setWordWrap(true);

        verticalLayout->addWidget(infoLabel);

        fullNameLineEdit = new QLineEdit(centralwidget);
        fullNameLineEdit->setObjectName("fullNameLineEdit");

        verticalLayout->addWidget(fullNameLineEdit);

        loginLineEdit = new QLineEdit(centralwidget);
        loginLineEdit->setObjectName("loginLineEdit");

        verticalLayout->addWidget(loginLineEdit);

        passwordLineEdit = new QLineEdit(centralwidget);
        passwordLineEdit->setObjectName("passwordLineEdit");
        passwordLineEdit->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(passwordLineEdit);

        repeatPasswordLineEdit = new QLineEdit(centralwidget);
        repeatPasswordLineEdit->setObjectName("repeatPasswordLineEdit");
        repeatPasswordLineEdit->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(repeatPasswordLineEdit);

        roleHintLabel = new QLabel(centralwidget);
        roleHintLabel->setObjectName("roleHintLabel");

        verticalLayout->addWidget(roleHintLabel);

        registerStudentButton = new QPushButton(centralwidget);
        registerStudentButton->setObjectName("registerStudentButton");

        verticalLayout->addWidget(registerStudentButton);

        registerTeacherButton = new QPushButton(centralwidget);
        registerTeacherButton->setObjectName("registerTeacherButton");

        verticalLayout->addWidget(registerTeacherButton);

        backButton = new QPushButton(centralwidget);
        backButton->setObjectName("backButton");

        verticalLayout->addWidget(backButton);

        statusLabel = new QLabel(centralwidget);
        statusLabel->setObjectName("statusLabel");

        verticalLayout->addWidget(statusLabel);

        RegistrationWindow->setCentralWidget(centralwidget);

        retranslateUi(RegistrationWindow);

        QMetaObject::connectSlotsByName(RegistrationWindow);
    } // setupUi

    void retranslateUi(QMainWindow *RegistrationWindow)
    {
        RegistrationWindow->setWindowTitle(QCoreApplication::translate("RegistrationWindow", "Study.Table - Registration", nullptr));
        titleLabel->setText(QCoreApplication::translate("RegistrationWindow", "New Account", nullptr));
        infoLabel->setText(QCoreApplication::translate("RegistrationWindow", "Fill in the form and choose whether you are a student or a teacher.", nullptr));
        fullNameLineEdit->setPlaceholderText(QCoreApplication::translate("RegistrationWindow", "Full name", nullptr));
        loginLineEdit->setPlaceholderText(QCoreApplication::translate("RegistrationWindow", "Username", nullptr));
        passwordLineEdit->setPlaceholderText(QCoreApplication::translate("RegistrationWindow", "Password", nullptr));
        repeatPasswordLineEdit->setPlaceholderText(QCoreApplication::translate("RegistrationWindow", "Repeat password", nullptr));
        roleHintLabel->setText(QCoreApplication::translate("RegistrationWindow", "Register as:", nullptr));
        registerStudentButton->setText(QCoreApplication::translate("RegistrationWindow", "Student", nullptr));
        registerTeacherButton->setText(QCoreApplication::translate("RegistrationWindow", "Teacher", nullptr));
        backButton->setText(QCoreApplication::translate("RegistrationWindow", "Back to Login", nullptr));
        statusLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class RegistrationWindow: public Ui_RegistrationWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTRATIONWINDOW_H

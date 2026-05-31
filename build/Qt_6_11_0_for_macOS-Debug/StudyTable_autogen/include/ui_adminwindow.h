/********************************************************************************
** Form generated from reading UI file 'adminwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMINWINDOW_H
#define UI_ADMINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AdminWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *mainLayout;
    QLabel *titleLabel;
    QLabel *infoLabel;
    QLabel *usersSectionLabel;
    QTextEdit *usersTextEdit;
    QLabel *coursesSectionLabel;
    QTextEdit *coursesTextEdit;
    QLabel *addCourseSectionLabel;
    QLineEdit *courseTitleLineEdit;
    QLineEdit *teacherIdLineEdit;
    QPushButton *addCourseButton;
    QLabel *enrollSectionLabel;
    QLineEdit *studentIdLineEdit;
    QLineEdit *courseIdLineEdit;
    QPushButton *enrollButton;
    QPushButton *refreshButton;
    QPushButton *logoutButton;
    QLabel *statusLabel;

    void setupUi(QMainWindow *AdminWindow)
    {
        if (AdminWindow->objectName().isEmpty())
            AdminWindow->setObjectName("AdminWindow");
        AdminWindow->resize(640, 780);
        centralwidget = new QWidget(AdminWindow);
        centralwidget->setObjectName("centralwidget");
        mainLayout = new QVBoxLayout(centralwidget);
        mainLayout->setObjectName("mainLayout");
        titleLabel = new QLabel(centralwidget);
        titleLabel->setObjectName("titleLabel");

        mainLayout->addWidget(titleLabel);

        infoLabel = new QLabel(centralwidget);
        infoLabel->setObjectName("infoLabel");
        infoLabel->setWordWrap(true);

        mainLayout->addWidget(infoLabel);

        usersSectionLabel = new QLabel(centralwidget);
        usersSectionLabel->setObjectName("usersSectionLabel");

        mainLayout->addWidget(usersSectionLabel);

        usersTextEdit = new QTextEdit(centralwidget);
        usersTextEdit->setObjectName("usersTextEdit");
        usersTextEdit->setReadOnly(true);
        usersTextEdit->setMinimumSize(QSize(0, 140));

        mainLayout->addWidget(usersTextEdit);

        coursesSectionLabel = new QLabel(centralwidget);
        coursesSectionLabel->setObjectName("coursesSectionLabel");

        mainLayout->addWidget(coursesSectionLabel);

        coursesTextEdit = new QTextEdit(centralwidget);
        coursesTextEdit->setObjectName("coursesTextEdit");
        coursesTextEdit->setReadOnly(true);
        coursesTextEdit->setMinimumSize(QSize(0, 100));

        mainLayout->addWidget(coursesTextEdit);

        addCourseSectionLabel = new QLabel(centralwidget);
        addCourseSectionLabel->setObjectName("addCourseSectionLabel");

        mainLayout->addWidget(addCourseSectionLabel);

        courseTitleLineEdit = new QLineEdit(centralwidget);
        courseTitleLineEdit->setObjectName("courseTitleLineEdit");

        mainLayout->addWidget(courseTitleLineEdit);

        teacherIdLineEdit = new QLineEdit(centralwidget);
        teacherIdLineEdit->setObjectName("teacherIdLineEdit");

        mainLayout->addWidget(teacherIdLineEdit);

        addCourseButton = new QPushButton(centralwidget);
        addCourseButton->setObjectName("addCourseButton");

        mainLayout->addWidget(addCourseButton);

        enrollSectionLabel = new QLabel(centralwidget);
        enrollSectionLabel->setObjectName("enrollSectionLabel");

        mainLayout->addWidget(enrollSectionLabel);

        studentIdLineEdit = new QLineEdit(centralwidget);
        studentIdLineEdit->setObjectName("studentIdLineEdit");

        mainLayout->addWidget(studentIdLineEdit);

        courseIdLineEdit = new QLineEdit(centralwidget);
        courseIdLineEdit->setObjectName("courseIdLineEdit");

        mainLayout->addWidget(courseIdLineEdit);

        enrollButton = new QPushButton(centralwidget);
        enrollButton->setObjectName("enrollButton");

        mainLayout->addWidget(enrollButton);

        refreshButton = new QPushButton(centralwidget);
        refreshButton->setObjectName("refreshButton");

        mainLayout->addWidget(refreshButton);

        logoutButton = new QPushButton(centralwidget);
        logoutButton->setObjectName("logoutButton");

        mainLayout->addWidget(logoutButton);

        statusLabel = new QLabel(centralwidget);
        statusLabel->setObjectName("statusLabel");

        mainLayout->addWidget(statusLabel);

        AdminWindow->setCentralWidget(centralwidget);

        retranslateUi(AdminWindow);

        QMetaObject::connectSlotsByName(AdminWindow);
    } // setupUi

    void retranslateUi(QMainWindow *AdminWindow)
    {
        AdminWindow->setWindowTitle(QCoreApplication::translate("AdminWindow", "Study.Table - Admin", nullptr));
        titleLabel->setText(QCoreApplication::translate("AdminWindow", "Admin Panel", nullptr));
        infoLabel->setText(QCoreApplication::translate("AdminWindow", "Here you can view all users and courses, create a new course, or enroll a student.", nullptr));
        usersSectionLabel->setText(QCoreApplication::translate("AdminWindow", "Users:", nullptr));
        coursesSectionLabel->setText(QCoreApplication::translate("AdminWindow", "Courses:", nullptr));
        addCourseSectionLabel->setText(QCoreApplication::translate("AdminWindow", "Add new course", nullptr));
        courseTitleLineEdit->setPlaceholderText(QCoreApplication::translate("AdminWindow", "Course name", nullptr));
        teacherIdLineEdit->setPlaceholderText(QCoreApplication::translate("AdminWindow", "Teacher ID (see list above)", nullptr));
        addCourseButton->setText(QCoreApplication::translate("AdminWindow", "Add Course", nullptr));
        enrollSectionLabel->setText(QCoreApplication::translate("AdminWindow", "Enroll student to course", nullptr));
        studentIdLineEdit->setPlaceholderText(QCoreApplication::translate("AdminWindow", "Student ID (see list above)", nullptr));
        courseIdLineEdit->setPlaceholderText(QCoreApplication::translate("AdminWindow", "Course ID (see list above)", nullptr));
        enrollButton->setText(QCoreApplication::translate("AdminWindow", "Enroll Student", nullptr));
        refreshButton->setText(QCoreApplication::translate("AdminWindow", "Refresh Lists", nullptr));
        logoutButton->setText(QCoreApplication::translate("AdminWindow", "Log Out", nullptr));
        statusLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class AdminWindow: public Ui_AdminWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMINWINDOW_H

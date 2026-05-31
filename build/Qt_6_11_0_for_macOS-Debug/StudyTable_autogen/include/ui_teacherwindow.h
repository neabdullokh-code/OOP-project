/********************************************************************************
** Form generated from reading UI file 'teacherwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEACHERWINDOW_H
#define UI_TEACHERWINDOW_H

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

class Ui_TeacherWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *mainLayout;
    QLabel *titleLabel;
    QLabel *infoLabel;
    QLabel *coursesSectionLabel;
    QTextEdit *coursesTextEdit;
    QLabel *studentsSectionLabel;
    QTextEdit *studentsTextEdit;
    QLabel *gradeSectionLabel;
    QLineEdit *courseIdLineEdit;
    QLineEdit *studentIdLineEdit;
    QLineEdit *gradeLineEdit;
    QPushButton *setGradeButton;
    QPushButton *refreshButton;
    QPushButton *logoutButton;
    QLabel *statusLabel;

    void setupUi(QMainWindow *TeacherWindow)
    {
        if (TeacherWindow->objectName().isEmpty())
            TeacherWindow->setObjectName("TeacherWindow");
        TeacherWindow->resize(640, 780);
        centralwidget = new QWidget(TeacherWindow);
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

        coursesSectionLabel = new QLabel(centralwidget);
        coursesSectionLabel->setObjectName("coursesSectionLabel");

        mainLayout->addWidget(coursesSectionLabel);

        coursesTextEdit = new QTextEdit(centralwidget);
        coursesTextEdit->setObjectName("coursesTextEdit");
        coursesTextEdit->setReadOnly(true);
        coursesTextEdit->setMinimumSize(QSize(0, 90));

        mainLayout->addWidget(coursesTextEdit);

        studentsSectionLabel = new QLabel(centralwidget);
        studentsSectionLabel->setObjectName("studentsSectionLabel");

        mainLayout->addWidget(studentsSectionLabel);

        studentsTextEdit = new QTextEdit(centralwidget);
        studentsTextEdit->setObjectName("studentsTextEdit");
        studentsTextEdit->setReadOnly(true);
        studentsTextEdit->setMinimumSize(QSize(0, 120));

        mainLayout->addWidget(studentsTextEdit);

        gradeSectionLabel = new QLabel(centralwidget);
        gradeSectionLabel->setObjectName("gradeSectionLabel");

        mainLayout->addWidget(gradeSectionLabel);

        courseIdLineEdit = new QLineEdit(centralwidget);
        courseIdLineEdit->setObjectName("courseIdLineEdit");

        mainLayout->addWidget(courseIdLineEdit);

        studentIdLineEdit = new QLineEdit(centralwidget);
        studentIdLineEdit->setObjectName("studentIdLineEdit");

        mainLayout->addWidget(studentIdLineEdit);

        gradeLineEdit = new QLineEdit(centralwidget);
        gradeLineEdit->setObjectName("gradeLineEdit");

        mainLayout->addWidget(gradeLineEdit);

        setGradeButton = new QPushButton(centralwidget);
        setGradeButton->setObjectName("setGradeButton");

        mainLayout->addWidget(setGradeButton);

        refreshButton = new QPushButton(centralwidget);
        refreshButton->setObjectName("refreshButton");

        mainLayout->addWidget(refreshButton);

        logoutButton = new QPushButton(centralwidget);
        logoutButton->setObjectName("logoutButton");

        mainLayout->addWidget(logoutButton);

        statusLabel = new QLabel(centralwidget);
        statusLabel->setObjectName("statusLabel");

        mainLayout->addWidget(statusLabel);

        TeacherWindow->setCentralWidget(centralwidget);

        retranslateUi(TeacherWindow);

        QMetaObject::connectSlotsByName(TeacherWindow);
    } // setupUi

    void retranslateUi(QMainWindow *TeacherWindow)
    {
        TeacherWindow->setWindowTitle(QCoreApplication::translate("TeacherWindow", "Study.Table - Teacher", nullptr));
        titleLabel->setText(QCoreApplication::translate("TeacherWindow", "Teacher Panel", nullptr));
        infoLabel->setText(QCoreApplication::translate("TeacherWindow", "View your courses and students. Enter course ID, student ID and grade to give a mark.", nullptr));
        coursesSectionLabel->setText(QCoreApplication::translate("TeacherWindow", "My courses:", nullptr));
        studentsSectionLabel->setText(QCoreApplication::translate("TeacherWindow", "My students:", nullptr));
        gradeSectionLabel->setText(QCoreApplication::translate("TeacherWindow", "Set grade for student", nullptr));
        courseIdLineEdit->setPlaceholderText(QCoreApplication::translate("TeacherWindow", "Course ID (from list above)", nullptr));
        studentIdLineEdit->setPlaceholderText(QCoreApplication::translate("TeacherWindow", "Student ID (from list above)", nullptr));
        gradeLineEdit->setPlaceholderText(QCoreApplication::translate("TeacherWindow", "Grade from 0 to 100", nullptr));
        setGradeButton->setText(QCoreApplication::translate("TeacherWindow", "Save Grade", nullptr));
        refreshButton->setText(QCoreApplication::translate("TeacherWindow", "Refresh Lists", nullptr));
        logoutButton->setText(QCoreApplication::translate("TeacherWindow", "Log Out", nullptr));
        statusLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class TeacherWindow: public Ui_TeacherWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEACHERWINDOW_H

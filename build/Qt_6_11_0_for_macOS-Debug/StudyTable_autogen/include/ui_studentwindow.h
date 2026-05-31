/********************************************************************************
** Form generated from reading UI file 'studentwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STUDENTWINDOW_H
#define UI_STUDENTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StudentWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *mainLayout;
    QLabel *titleLabel;
    QLabel *infoLabel;
    QLabel *averageLabel;
    QLabel *coursesSectionLabel;
    QTextEdit *coursesTextEdit;
    QLabel *gradesSectionLabel;
    QTextEdit *gradesTextEdit;
    QPushButton *refreshButton;
    QPushButton *logoutButton;

    void setupUi(QMainWindow *StudentWindow)
    {
        if (StudentWindow->objectName().isEmpty())
            StudentWindow->setObjectName("StudentWindow");
        StudentWindow->resize(640, 620);
        centralwidget = new QWidget(StudentWindow);
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

        averageLabel = new QLabel(centralwidget);
        averageLabel->setObjectName("averageLabel");

        mainLayout->addWidget(averageLabel);

        coursesSectionLabel = new QLabel(centralwidget);
        coursesSectionLabel->setObjectName("coursesSectionLabel");

        mainLayout->addWidget(coursesSectionLabel);

        coursesTextEdit = new QTextEdit(centralwidget);
        coursesTextEdit->setObjectName("coursesTextEdit");
        coursesTextEdit->setReadOnly(true);
        coursesTextEdit->setMinimumSize(QSize(0, 100));

        mainLayout->addWidget(coursesTextEdit);

        gradesSectionLabel = new QLabel(centralwidget);
        gradesSectionLabel->setObjectName("gradesSectionLabel");

        mainLayout->addWidget(gradesSectionLabel);

        gradesTextEdit = new QTextEdit(centralwidget);
        gradesTextEdit->setObjectName("gradesTextEdit");
        gradesTextEdit->setReadOnly(true);
        gradesTextEdit->setMinimumSize(QSize(0, 100));

        mainLayout->addWidget(gradesTextEdit);

        refreshButton = new QPushButton(centralwidget);
        refreshButton->setObjectName("refreshButton");

        mainLayout->addWidget(refreshButton);

        logoutButton = new QPushButton(centralwidget);
        logoutButton->setObjectName("logoutButton");

        mainLayout->addWidget(logoutButton);

        StudentWindow->setCentralWidget(centralwidget);

        retranslateUi(StudentWindow);

        QMetaObject::connectSlotsByName(StudentWindow);
    } // setupUi

    void retranslateUi(QMainWindow *StudentWindow)
    {
        StudentWindow->setWindowTitle(QCoreApplication::translate("StudentWindow", "Study.Table - Student", nullptr));
        titleLabel->setText(QCoreApplication::translate("StudentWindow", "Student Panel", nullptr));
        infoLabel->setText(QCoreApplication::translate("StudentWindow", "Here you can see your courses, grades and average score.", nullptr));
        averageLabel->setText(QCoreApplication::translate("StudentWindow", "Average grade: 0.00", nullptr));
        coursesSectionLabel->setText(QCoreApplication::translate("StudentWindow", "My courses:", nullptr));
        gradesSectionLabel->setText(QCoreApplication::translate("StudentWindow", "My grades:", nullptr));
        refreshButton->setText(QCoreApplication::translate("StudentWindow", "Refresh", nullptr));
        logoutButton->setText(QCoreApplication::translate("StudentWindow", "Log Out", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StudentWindow: public Ui_StudentWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STUDENTWINDOW_H

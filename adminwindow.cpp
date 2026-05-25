#include "adminwindow.h"
#include "ui_adminwindow.h"
#include <QPushButton>

AdminWindow::AdminWindow(FileManager *fileManager, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::AdminWindow),
      m_fileManager(fileManager)
{
    ui->setupUi(this);

    connect(ui->refreshButton, &QPushButton::clicked,
            this, &AdminWindow::onRefreshClicked);
    connect(ui->addCourseButton, &QPushButton::clicked,
            this, &AdminWindow::onAddCourseClicked);
    connect(ui->enrollButton, &QPushButton::clicked,
            this, &AdminWindow::onEnrollStudentClicked);
    connect(ui->logoutButton, &QPushButton::clicked,
            this, &AdminWindow::onLogoutClicked);

    ui->statusLabel->setText("");
    refreshData();
}

AdminWindow::~AdminWindow()
{
    delete ui;
}

void AdminWindow::onRefreshClicked()
{
    refreshData();
}

void AdminWindow::onAddCourseClicked()
{
    QString title = ui->courseTitleLineEdit->text().trimmed();
    int teacherId = ui->teacherIdLineEdit->text().toInt();

    if (!m_fileManager->addCourse(title, teacherId))
    {
        ui->statusLabel->setText("Could not add course. Enter course name and a valid teacher ID.");
        return;
    }

    ui->statusLabel->setText("Course added.");
    ui->courseTitleLineEdit->clear();
    ui->teacherIdLineEdit->clear();
    refreshData();
}

void AdminWindow::onEnrollStudentClicked()
{
    int studentId = ui->studentIdLineEdit->text().toInt();
    int courseId = ui->courseIdLineEdit->text().toInt();

    if (!m_fileManager->addEnrollment(studentId, courseId))
    {
        ui->statusLabel->setText("Could not enroll student. Check student ID and course ID.");
        return;
    }

    ui->statusLabel->setText("Student enrolled.");
    ui->studentIdLineEdit->clear();
    ui->courseIdLineEdit->clear();
    refreshData();
}

void AdminWindow::onLogoutClicked()
{
    close();
    emit logoutRequested();
}

void AdminWindow::refreshData()
{
    std::vector<User *> users = m_fileManager->getUsers();
    std::vector<Course> courses = m_fileManager->getCourses();

    QString usersText;
    QString coursesText;
    int i;

    ui->usersSectionLabel->setText("Users (" + QString::number(users.size()) + "):");
    ui->coursesSectionLabel->setText("Courses (" + QString::number(courses.size()) + "):");

    if (users.size() == 0)
    {
        usersText = "No users yet.";
    }
    else
    {
        for (i = 0; i < users.size(); i++)
        {
            User *user = users[i];
            usersText += "ID " + QString::number(user->getId()) + ": " +
                         user->getFullName() + ", login: " + user->getLogin() +
                         ", role: " + user->getRoleName() + "\n";
        }
    }

    if (courses.size() == 0)
    {
        coursesText = "No courses yet.";
    }
    else
    {
        for (i = 0; i < courses.size(); i++)
        {
            coursesText += "ID " + QString::number(courses[i].getId()) + ": " +
                           courses[i].getTitle() + ", teacher ID: " +
                           QString::number(courses[i].getTeacherId()) + "\n";
        }
    }

    ui->usersTextEdit->setText(usersText);
    ui->coursesTextEdit->setText(coursesText);
}

#include "adminwindow.h"
#include "ui_adminwindow.h"
#include <QMessageBox>

AdminWindow::AdminWindow(DatabaseManager *databaseManager, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::AdminWindow),
      m_databaseManager(databaseManager),
      m_userController(databaseManager),
      m_courseController(databaseManager)
{
    ui->setupUi(this);

    connect(ui->refreshButton, SIGNAL(clicked()), this, SLOT(onRefreshClicked()));
    connect(ui->addCourseButton, SIGNAL(clicked()), this, SLOT(onAddCourseClicked()));
    connect(ui->enrollButton, SIGNAL(clicked()), this, SLOT(onEnrollStudentClicked()));
    connect(ui->logoutButton, SIGNAL(clicked()), this, SLOT(onLogoutClicked()));

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

    if (!m_courseController.createCourse(title, teacherId))
    {
        QMessageBox::warning(this, "Error", "Failed to add course. Check the fields.");
        return;
    }

    ui->courseTitleLineEdit->clear();
    ui->teacherIdLineEdit->clear();
    refreshData();
}

void AdminWindow::onEnrollStudentClicked()
{
    int studentId = ui->studentIdLineEdit->text().toInt();
    int courseId = ui->courseIdLineEdit->text().toInt();

    if (!m_courseController.enrollStudent(studentId, courseId))
    {
        QMessageBox::warning(this, "Error", "Failed to enroll the student.");
        return;
    }

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
    ui->usersListWidget->clear();
    ui->coursesListWidget->clear();

    QList<User *> users = m_userController.getAllUsers();
    QList<Course> courses = m_courseController.getAllCourses();

    int i;
    for (i = 0; i < users.size(); i++)
    {
        User *user = users[i];
        QString line = QString::number(user->getId()) + " | " +
                       user->getFullName() + " | " +
                       user->getLogin() + " | " +
                       user->getRoleName();
        ui->usersListWidget->addItem(line);
    }

    for (i = 0; i < courses.size(); i++)
    {
        const Course &course = courses[i];
        QString line = QString::number(course.getId()) + " | " +
                       course.getTitle() + " | teacherId=" +
                       QString::number(course.getTeacherId());
        ui->coursesListWidget->addItem(line);
    }

    ui->usersCountLabel->setText("Users: " + QString::number(users.size()));
    ui->coursesCountLabel->setText("Courses: " + QString::number(courses.size()));
}

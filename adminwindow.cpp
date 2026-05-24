#include "adminwindow.h"
#include "ui_adminwindow.h"

AdminWindow::AdminWindow(FileManager *fileManager, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::AdminWindow),
      m_fileManager(fileManager)
{
    ui->setupUi(this);

    connect(ui->refreshButton, SIGNAL(clicked()), this, SLOT(onRefreshClicked()));
    connect(ui->addCourseButton, SIGNAL(clicked()), this, SLOT(onAddCourseClicked()));
    connect(ui->enrollButton, SIGNAL(clicked()), this, SLOT(onEnrollStudentClicked()));
    connect(ui->logoutButton, SIGNAL(clicked()), this, SLOT(onLogoutClicked()));

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
        ui->statusLabel->setText("Failed to add course. Check the fields.");
        return;
    }

    ui->statusLabel->setText("");
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
        ui->statusLabel->setText("Failed to enroll the student.");
        return;
    }

    ui->statusLabel->setText("");
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

    for (i = 0; i < users.size(); i++)
    {
        User *user = users[i];
        if (!usersText.isEmpty())
        {
            usersText += "\n";
        }
        usersText += QString::number(user->getId()) + " | " +
                     user->getFullName() + " | " +
                     user->getLogin() + " | " +
                     user->getRoleName();
    }

    for (i = 0; i < courses.size(); i++)
    {
        if (!coursesText.isEmpty())
        {
            coursesText += "\n";
        }
        coursesText += QString::number(courses[i].getId()) + " | " +
                         courses[i].getTitle() + " | teacherId=" +
                         QString::number(courses[i].getTeacherId());
    }

    ui->usersListLabel->setText(usersText);
    ui->coursesListLabel->setText(coursesText);
    ui->usersCountLabel->setText("Users: " + QString::number(users.size()));
    ui->coursesCountLabel->setText("Courses: " + QString::number(courses.size()));
}

#include "teacherwindow.h"
#include "ui_teacherwindow.h"
#include <QPushButton>

TeacherWindow::TeacherWindow(FileManager *fileManager, int teacherId, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::TeacherWindow),
      m_fileManager(fileManager),
      m_teacherId(teacherId)
{
    ui->setupUi(this);

    connect(ui->refreshButton, &QPushButton::clicked,
            this, &TeacherWindow::onRefreshClicked);
    connect(ui->setGradeButton, &QPushButton::clicked,
            this, &TeacherWindow::onSetGradeClicked);
    connect(ui->logoutButton, &QPushButton::clicked,
            this, &TeacherWindow::onLogoutClicked);

    ui->statusLabel->setText("");
    refreshData();
}

TeacherWindow::~TeacherWindow()
{
    delete ui;
}

void TeacherWindow::onRefreshClicked()
{
    refreshData();
}

void TeacherWindow::onSetGradeClicked()
{
    int courseId = ui->courseIdLineEdit->text().toInt();
    int studentId = ui->studentIdLineEdit->text().toInt();
    int gradeValue = ui->gradeLineEdit->text().toInt();

    Course *course = m_fileManager->findCourseById(courseId);
    if (course == 0 || course->getTeacherId() != m_teacherId)
    {
        ui->statusLabel->setText("Wrong course ID. Use one of your courses from the list.");
        return;
    }

    if (!m_fileManager->setGradeForStudentInCourse(studentId, courseId, gradeValue))
    {
        ui->statusLabel->setText("Could not save grade. Check student ID and grade (0-100).");
        return;
    }

    ui->statusLabel->setText("Grade saved.");
    ui->courseIdLineEdit->clear();
    ui->studentIdLineEdit->clear();
    ui->gradeLineEdit->clear();
    refreshData();
}

void TeacherWindow::onLogoutClicked()
{
    close();
    emit logoutRequested();
}

void TeacherWindow::refreshData()
{
    std::vector<Course> courses = m_fileManager->getCoursesByTeacher(m_teacherId);
    QString coursesText;
    QString studentsText;
    int totalStudents = 0;
    int i;

    ui->coursesSectionLabel->setText("My courses (" + QString::number(courses.size()) + "):");

    if (courses.size() == 0)
    {
        coursesText = "You have no courses yet. Ask admin to create one for you.";
    }
    else
    {
        for (i = 0; i < courses.size(); i++)
        {
            coursesText += "ID " + QString::number(courses[i].getId()) + ": " +
                           courses[i].getTitle() + "\n";
        }
    }

    for (i = 0; i < courses.size(); i++)
    {
        std::vector<User *> students = m_fileManager->getStudentsForCourse(courses[i].getId());
        int j;
        for (j = 0; j < students.size(); j++)
        {
            studentsText += "Course " + courses[i].getTitle() +
                            " (ID " + QString::number(courses[i].getId()) + ") - student ID " +
                            QString::number(students[j]->getId()) + ": " +
                            students[j]->getFullName() + "\n";
            totalStudents++;
        }
    }

    if (totalStudents == 0)
    {
        studentsText = "No students in your courses yet.";
    }

    ui->studentsSectionLabel->setText("My students (" + QString::number(totalStudents) + "):");
    ui->coursesTextEdit->setText(coursesText);
    ui->studentsTextEdit->setText(studentsText);
}

#include "studentwindow.h"
#include "ui_studentwindow.h"
#include <QPushButton>

StudentWindow::StudentWindow(FileManager *fileManager, int studentId, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::StudentWindow),
      m_fileManager(fileManager),
      m_studentId(studentId)
{
    ui->setupUi(this);

    connect(ui->refreshButton, &QPushButton::clicked,
            this, &StudentWindow::onRefreshClicked);
    connect(ui->logoutButton, &QPushButton::clicked,
            this, &StudentWindow::onLogoutClicked);

    refreshData();
}

StudentWindow::~StudentWindow()
{
    delete ui;
}

void StudentWindow::onRefreshClicked()
{
    refreshData();
}

void StudentWindow::onLogoutClicked()
{
    close();
    emit logoutRequested();
}

void StudentWindow::refreshData()
{
    std::vector<Course> courses = m_fileManager->getCoursesByStudent(m_studentId);
    std::vector<Enrollment> enrollments = m_fileManager->getEnrollments();
    std::vector<Grade> grades = m_fileManager->getGrades();

    QString coursesText;
    QString gradesText;
    int i;
    int j;

    ui->coursesSectionLabel->setText("My courses (" + QString::number(courses.size()) + "):");
    ui->averageLabel->setText("Average grade: " +
                              QString::number(m_fileManager->getAverageGradeForStudent(m_studentId), 'f', 2));

    if (courses.size() == 0)
    {
        coursesText = "You are not enrolled in any courses yet.";
    }
    else
    {
        for (i = 0; i < courses.size(); i++)
        {
            coursesText += "ID " + QString::number(courses[i].getId()) + ": " +
                           courses[i].getTitle() + "\n";
        }
    }

    for (i = 0; i < enrollments.size(); i++)
    {
        if (enrollments[i].getStudentId() == m_studentId)
        {
            int enrollmentId = enrollments[i].getId();
            int courseId = enrollments[i].getCourseId();
            QString courseTitle = "Unknown course";
            Course *course = m_fileManager->findCourseById(courseId);
            if (course != 0)
            {
                courseTitle = course->getTitle();
            }

            bool hasGrade = false;
            for (j = 0; j < grades.size(); j++)
            {
                if (grades[j].getEnrollmentId() == enrollmentId)
                {
                    gradesText += courseTitle + " (ID " + QString::number(courseId) + ") - grade: " +
                                  QString::number(grades[j].getValue()) + "\n";
                    hasGrade = true;
                }
            }

            if (!hasGrade)
            {
                gradesText += courseTitle + " (ID " + QString::number(courseId) + ") - no grade yet\n";
            }
        }
    }

    if (gradesText.isEmpty())
    {
        gradesText = "No grades yet.";
    }

    ui->coursesTextEdit->setText(coursesText);
    ui->gradesTextEdit->setText(gradesText);
}

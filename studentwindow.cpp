#include "studentwindow.h"
#include "ui_studentwindow.h"

StudentWindow::StudentWindow(FileManager *fileManager, int studentId, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::StudentWindow),
      m_fileManager(fileManager),
      m_studentId(studentId)
{
    ui->setupUi(this);

    connect(ui->refreshButton, SIGNAL(clicked()), this, SLOT(onRefreshClicked()));
    connect(ui->logoutButton, SIGNAL(clicked()), this, SLOT(onLogoutClicked()));

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
    const std::vector<Enrollment> &enrollments = m_fileManager->getEnrollments();
    const std::vector<Grade> &grades = m_fileManager->getGrades();

    QString coursesText;
    QString gradesText;
    int i;

    for (i = 0; i < courses.size(); i++)
    {
        if (!coursesText.isEmpty())
        {
            coursesText += "\n";
        }
        coursesText += QString::number(courses[i].getId()) + " | " + courses[i].getTitle();
    }

    for (i = 0; i < enrollments.size(); i++)
    {
        if (enrollments[i].getStudentId() == m_studentId)
        {
            int enrollmentId = enrollments[i].getId();
            int j;
            for (j = 0; j < grades.size(); j++)
            {
                if (grades[j].getEnrollmentId() == enrollmentId)
                {
                    if (!gradesText.isEmpty())
                    {
                        gradesText += "\n";
                    }
                    gradesText += "Enrollment " + QString::number(enrollmentId) +
                                  " -> " + QString::number(grades[j].getValue());
                }
            }
        }
    }

    ui->coursesListLabel->setText(coursesText);
    ui->gradesListLabel->setText(gradesText);
    ui->coursesCountLabel->setText("My courses: " + QString::number(courses.size()));
    ui->averageLabel->setText("Average grade: " + QString::number(m_fileManager->getAverageGradeForStudent(m_studentId), 'f', 2));
}

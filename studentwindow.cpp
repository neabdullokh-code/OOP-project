#include "studentwindow.h"
#include "ui_studentwindow.h"

StudentWindow::StudentWindow(DatabaseManager *databaseManager, int studentId, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::StudentWindow),
      m_databaseManager(databaseManager),
      m_studentId(studentId),
      m_courseController(databaseManager),
      m_gradeController(databaseManager)
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
    std::vector<Course> courses = m_courseController.getCoursesByStudent(m_studentId);
    const std::vector<Enrollment> &enrollments = m_databaseManager->getEnrollments();
    const std::vector<Grade> &grades = m_databaseManager->getGrades();

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
    ui->averageLabel->setText("Average grade: " + QString::number(m_gradeController.getAverageForStudent(m_studentId), 'f', 2));
}

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
    ui->coursesListWidget->clear();
    ui->gradesListWidget->clear();

    QList<Course> courses = m_courseController.getCoursesByStudent(m_studentId);
    QList<Enrollment> enrollments = m_databaseManager->getEnrollments();
    QList<Grade> grades = m_databaseManager->getGrades();

    int i;
    for (i = 0; i < courses.size(); i++)
    {
        ui->coursesListWidget->addItem(QString::number(courses[i].getId()) + " | " + courses[i].getTitle());
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
                    QString gradeLine = "Enrollment " + QString::number(enrollmentId) +
                                        " -> " + QString::number(grades[j].getValue());
                    ui->gradesListWidget->addItem(gradeLine);
                }
            }
        }
    }

    ui->coursesCountLabel->setText("My courses: " + QString::number(courses.size()));
    ui->averageLabel->setText("Average grade: " + QString::number(m_gradeController.getAverageForStudent(m_studentId), 'f', 2));
}

#include "teacherwindow.h"
#include "ui_teacherwindow.h"

TeacherWindow::TeacherWindow(DatabaseManager *databaseManager, int teacherId, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::TeacherWindow),
      m_databaseManager(databaseManager),
      m_teacherId(teacherId)
{
    ui->setupUi(this);

    connect(ui->refreshButton, SIGNAL(clicked()), this, SLOT(onRefreshClicked()));
    connect(ui->setGradeButton, SIGNAL(clicked()), this, SLOT(onSetGradeClicked()));
    connect(ui->logoutButton, SIGNAL(clicked()), this, SLOT(onLogoutClicked()));

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

    Course *course = m_databaseManager->findCourseById(courseId);
    if (course == 0 || course->getTeacherId() != m_teacherId)
    {
        ui->statusLabel->setText("This course does not belong to the current teacher.");
        return;
    }

    if (!m_databaseManager->setGradeForStudentInCourse(studentId, courseId, gradeValue))
    {
        ui->statusLabel->setText("Failed to save the grade.");
        return;
    }

    ui->statusLabel->setText("");
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
    std::vector<Course> courses = m_databaseManager->getCoursesByTeacher(m_teacherId);
    QString coursesText;
    QString studentsText;
    int totalStudents = 0;
    int i;

    for (i = 0; i < courses.size(); i++)
    {
        const Course &course = courses[i];
        if (!coursesText.isEmpty())
        {
            coursesText += "\n";
        }
        coursesText += QString::number(course.getId()) + " | " + course.getTitle();

        std::vector<User *> students = m_databaseManager->getStudentsForCourse(course.getId());
        int j;
        for (j = 0; j < students.size(); j++)
        {
            if (!studentsText.isEmpty())
            {
                studentsText += "\n";
            }
            studentsText += "course " + QString::number(course.getId()) + " -> " +
                            QString::number(students[j]->getId()) + " " + students[j]->getFullName();
            totalStudents++;
        }
    }

    ui->coursesListLabel->setText(coursesText);
    ui->studentsListLabel->setText(studentsText);
    ui->coursesCountLabel->setText("My courses: " + QString::number(courses.size()));
    ui->studentsCountLabel->setText("Students in my courses: " + QString::number(totalStudents));
}

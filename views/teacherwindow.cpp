#include "teacherwindow.h"
#include "ui_teacherwindow.h"
#include <QMessageBox>

TeacherWindow::TeacherWindow(DatabaseManager *databaseManager, int teacherId, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::TeacherWindow),
      m_databaseManager(databaseManager),
      m_teacherId(teacherId),
      m_courseController(databaseManager),
      m_gradeController(databaseManager)
{
    ui->setupUi(this);

    connect(ui->refreshButton, SIGNAL(clicked()), this, SLOT(onRefreshClicked()));
    connect(ui->setGradeButton, SIGNAL(clicked()), this, SLOT(onSetGradeClicked()));
    connect(ui->logoutButton, SIGNAL(clicked()), this, SLOT(onLogoutClicked()));

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
    int gradeValue = ui->gradeSpinBox->value();

    Course *course = m_databaseManager->findCourseById(courseId);
    if (course == 0 || course->getTeacherId() != m_teacherId)
    {
        QMessageBox::warning(this, "Error", "This course does not belong to the current teacher.");
        return;
    }

    if (!m_gradeController.setGradeForStudentInCourse(studentId, courseId, gradeValue))
    {
        QMessageBox::warning(this, "Error", "Failed to save the grade.");
        return;
    }

    ui->courseIdLineEdit->clear();
    ui->studentIdLineEdit->clear();
    refreshData();
}

void TeacherWindow::onLogoutClicked()
{
    close();
    emit logoutRequested();
}

void TeacherWindow::refreshData()
{
    ui->coursesListWidget->clear();
    ui->studentsListWidget->clear();

    QList<Course> courses = m_courseController.getCoursesByTeacher(m_teacherId);
    int totalStudents = 0;

    int i;
    for (i = 0; i < courses.size(); i++)
    {
        const Course &course = courses[i];
        QString courseLine = QString::number(course.getId()) + " | " + course.getTitle();
        ui->coursesListWidget->addItem(courseLine);

        QList<User *> students = m_databaseManager->getStudentsForCourse(course.getId());
        int j;
        for (j = 0; j < students.size(); j++)
        {
            QString studentLine = "course " + QString::number(course.getId()) + " -> " +
                                  QString::number(students[j]->getId()) + " " + students[j]->getFullName();
            ui->studentsListWidget->addItem(studentLine);
            totalStudents++;
        }
    }

    ui->coursesCountLabel->setText("My courses: " + QString::number(courses.size()));
    ui->studentsCountLabel->setText("Students in my courses: " + QString::number(totalStudents));
}

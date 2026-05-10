#include "coursecontroller.h"

CourseController::CourseController(DatabaseManager *databaseManager)
    : m_databaseManager(databaseManager)
{
}

bool CourseController::createCourse(const QString &title, int teacherId) const
{
    if (m_databaseManager == 0)
    {
        return false;
    }
    return m_databaseManager->addCourse(title, teacherId);
}

bool CourseController::removeCourse(int courseId) const
{
    if (m_databaseManager == 0)
    {
        return false;
    }
    return m_databaseManager->removeCourse(courseId);
}

bool CourseController::enrollStudent(int studentId, int courseId) const
{
    if (m_databaseManager == 0)
    {
        return false;
    }
    return m_databaseManager->addEnrollment(studentId, courseId);
}

QList<Course> CourseController::getAllCourses() const
{
    if (m_databaseManager == 0)
    {
        return QList<Course>();
    }
    return m_databaseManager->getCourses();
}

QList<Course> CourseController::getCoursesByTeacher(int teacherId) const
{
    if (m_databaseManager == 0)
    {
        return QList<Course>();
    }
    return m_databaseManager->getCoursesByTeacher(teacherId);
}

QList<Course> CourseController::getCoursesByStudent(int studentId) const
{
    if (m_databaseManager == 0)
    {
        return QList<Course>();
    }
    return m_databaseManager->getCoursesByStudent(studentId);
}

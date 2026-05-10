#include "gradecontroller.h"

GradeController::GradeController(DatabaseManager *databaseManager)
    : m_databaseManager(databaseManager)
{
}

bool GradeController::setGradeForStudentInCourse(int studentId, int courseId, int value) const
{
    if (m_databaseManager == 0)
    {
        return false;
    }

    QList<Enrollment> enrollments = m_databaseManager->getEnrollments();
    int i;
    for (i = 0; i < enrollments.size(); i++)
    {
        if (enrollments[i].getStudentId() == studentId && enrollments[i].getCourseId() == courseId)
        {
            return m_databaseManager->upsertGrade(enrollments[i].getId(), value);
        }
    }

    if (!m_databaseManager->addEnrollment(studentId, courseId))
    {
        return false;
    }

    QList<Enrollment> updatedEnrollments = m_databaseManager->getEnrollments();
    for (i = 0; i < updatedEnrollments.size(); i++)
    {
        if (updatedEnrollments[i].getStudentId() == studentId &&
            updatedEnrollments[i].getCourseId() == courseId)
        {
            return m_databaseManager->upsertGrade(updatedEnrollments[i].getId(), value);
        }
    }
    return false;
}

int GradeController::getGradeForEnrollment(int enrollmentId) const
{
    if (m_databaseManager == 0)
    {
        return 0;
    }

    QList<Grade> grades = m_databaseManager->getGrades();
    int i;
    for (i = 0; i < grades.size(); i++)
    {
        if (grades[i].getEnrollmentId() == enrollmentId)
        {
            return grades[i].getValue();
        }
    }
    return 0;
}

double GradeController::getAverageForStudent(int studentId) const
{
    if (m_databaseManager == 0)
    {
        return 0.0;
    }
    return m_databaseManager->getAverageGradeForStudent(studentId);
}

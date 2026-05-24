#include "enrollment.h"

Enrollment::Enrollment()
    : m_id(0), m_studentId(0), m_courseId(0)
{
}

Enrollment::Enrollment(int id, int studentId, int courseId)
    : m_id(id), m_studentId(studentId), m_courseId(courseId)
{
}

int Enrollment::getId() const
{
    return m_id;
}

int Enrollment::getStudentId() const
{
    return m_studentId;
}

int Enrollment::getCourseId() const
{
    return m_courseId;
}

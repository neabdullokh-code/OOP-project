#include "course.h"

Course::Course()
    : m_id(0), m_teacherId(0)
{
}

Course::Course(int id, const QString &title, int teacherId)
    : m_id(id), m_title(title), m_teacherId(teacherId)
{
}

int Course::getId() const
{
    return m_id;
}

QString Course::getTitle() const
{
    return m_title;
}

int Course::getTeacherId() const
{
    return m_teacherId;
}

void Course::setTitle(const QString &title)
{
    m_title = title;
}

void Course::setTeacherId(int teacherId)
{
    m_teacherId = teacherId;
}

#include "grade.h"

Grade::Grade()
    : m_id(0), m_enrollmentId(0), m_value(0)
{
}

Grade::Grade(int id, int enrollmentId, int value)
    : m_id(id), m_enrollmentId(enrollmentId), m_value(value)
{
}

Grade::Grade(const Grade &other)
    : m_id(other.m_id),
      m_enrollmentId(other.m_enrollmentId),
      m_value(other.m_value)
{
}

Grade &Grade::operator=(const Grade &other)
{
    if (this != &other)
    {
        m_id = other.m_id;
        m_enrollmentId = other.m_enrollmentId;
        m_value = other.m_value;
    }
    return *this;
}

int Grade::getId() const
{
    return m_id;
}

int Grade::getEnrollmentId() const
{
    return m_enrollmentId;
}

int Grade::getValue() const
{
    return m_value;
}

void Grade::setValue(int value)
{
    m_value = value;
}

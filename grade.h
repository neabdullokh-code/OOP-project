#ifndef GRADE_H
#define GRADE_H

class Grade
{
public:
    Grade();
    Grade(int id, int enrollmentId, int value);
    Grade(const Grade &other);

    Grade &operator=(const Grade &other);

    int getId() const;
    int getEnrollmentId() const;
    int getValue() const;

    void setValue(int value);

private:
    int m_id;
    int m_enrollmentId;
    int m_value;
};

#endif

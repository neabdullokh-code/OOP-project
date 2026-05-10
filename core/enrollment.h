#ifndef ENROLLMENT_H
#define ENROLLMENT_H

class Enrollment
{
public:
    Enrollment();
    Enrollment(int id, int studentId, int courseId);

    int getId() const;
    int getStudentId() const;
    int getCourseId() const;

private:
    int m_id;
    int m_studentId;
    int m_courseId;
};

#endif

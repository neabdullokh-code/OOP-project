#ifndef GRADECONTROLLER_H
#define GRADECONTROLLER_H

#include "databasemanager.h"

class GradeController
{
public:
    GradeController(DatabaseManager *databaseManager);

    bool setGradeForStudentInCourse(int studentId, int courseId, int value) const;
    int getGradeForEnrollment(int enrollmentId) const;
    double getAverageForStudent(int studentId) const;

private:
    DatabaseManager *m_databaseManager;
};

#endif

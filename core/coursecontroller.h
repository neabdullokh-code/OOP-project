#ifndef COURSECONTROLLER_H
#define COURSECONTROLLER_H

#include "databasemanager.h"

class CourseController
{
public:
    CourseController(DatabaseManager *databaseManager);

    bool createCourse(const QString &title, int teacherId) const;
    bool removeCourse(int courseId) const;
    bool enrollStudent(int studentId, int courseId) const;

    QList<Course> getAllCourses() const;
    QList<Course> getCoursesByTeacher(int teacherId) const;
    QList<Course> getCoursesByStudent(int studentId) const;

private:
    DatabaseManager *m_databaseManager;
};

#endif

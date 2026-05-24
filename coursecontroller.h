#ifndef COURSECONTROLLER_H
#define COURSECONTROLLER_H

#include <vector>
#include "databasemanager.h"

class CourseController
{
public:
    CourseController(DatabaseManager *databaseManager);

    bool createCourse(const QString &title, int teacherId) const;
    bool removeCourse(int courseId) const;
    bool enrollStudent(int studentId, int courseId) const;

    std::vector<Course> getAllCourses() const;
    std::vector<Course> getCoursesByTeacher(int teacherId) const;
    std::vector<Course> getCoursesByStudent(int studentId) const;

private:
    DatabaseManager *m_databaseManager;
};

#endif

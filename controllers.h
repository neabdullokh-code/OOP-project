#ifndef CONTROLLERS_H
#define CONTROLLERS_H

#include <QString>
#include <vector>
#include "databasemanager.h"

class AuthController
{
public:
    AuthController(DatabaseManager *databaseManager);

    User *login(const QString &login, const QString &password) const;
    bool registerUser(const QString &fullName, const QString &login, const QString &password, const QString &roleName) const;

private:
    DatabaseManager *m_databaseManager;
};

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

class UserController
{
public:
    UserController(DatabaseManager *databaseManager);

    bool removeUser(int userId) const;
    std::vector<User *> getAllUsers() const;
    std::vector<User *> getTeachers() const;
    std::vector<User *> getStudents() const;

private:
    DatabaseManager *m_databaseManager;
};

#endif

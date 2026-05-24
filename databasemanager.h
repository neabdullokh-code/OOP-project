#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include <string>
#include <vector>
#include "models.h"

using namespace std;

class DatabaseManager
{
public:
    DatabaseManager();
    ~DatabaseManager();

    bool ensureDefaultAdmin();
    bool loadAll();
    bool saveAll();

    const vector<User *> &getUsers() const;
    const vector<Course> &getCourses() const;
    const vector<Enrollment> &getEnrollments() const;
    const vector<Grade> &getGrades() const;

    User *findUserByLogin(const QString &login) const;
    User *findUserById(int id) const;
    Course *findCourseById(int id);
    Enrollment *findEnrollmentById(int id);
    Grade *findGradeByEnrollmentId(int enrollmentId);

    bool loginExists(const QString &login) const;
    bool addUser(User *user);
    bool removeUser(int userId);

    bool addCourse(const QString &title, int teacherId);
    bool removeCourse(int courseId);

    bool addEnrollment(int studentId, int courseId);
    bool upsertGrade(int enrollmentId, int value);
    bool setGradeForStudentInCourse(int studentId, int courseId, int value);

    User *login(const QString &login, const QString &password) const;
    bool registerUser(const QString &fullName, const QString &login, const QString &password, const QString &roleName);

    vector<Course> getCoursesByTeacher(int teacherId) const;
    vector<Course> getCoursesByStudent(int studentId) const;
    vector<User *> getStudentsForCourse(int courseId) const;
    vector<User *> getTeachers() const;
    vector<User *> getStudents() const;
    double getAverageGradeForStudent(int studentId) const;

private:
    vector<User *> m_users;
    vector<Course> m_courses;
    vector<Enrollment> m_enrollments;
    vector<Grade> m_grades;

    int m_nextCourseId;
    int m_nextEnrollmentId;
    int m_nextGradeId;

    string m_usersPath;
    string m_coursesPath;
    string m_enrollmentsPath;
    string m_gradesPath;

    void clearUsers();
    User *createUserByRole(const QString &role, int id, const QString &login, const QString &password, const QString &fullName) const;
};

#endif

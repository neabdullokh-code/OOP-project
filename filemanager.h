#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QString>
#include <string>
#include <vector>
#include "models.h"

using namespace std;

class FileManager
{
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
    User *createUserByRole(QString role, int id, QString login, QString password, QString fullName);

public:
    FileManager();
    ~FileManager();

    bool ensureDefaultAdmin();
    bool loadAll();
    bool saveAll();

    vector<User *> getUsers();
    vector<Course> getCourses();
    vector<Enrollment> getEnrollments();
    vector<Grade> getGrades();

    User *findUserByLogin(QString login);
    User *findUserById(int id);
    Course *findCourseById(int id);
    Grade *findGradeByEnrollmentId(int enrollmentId);

    bool loginExists(QString login);
    bool addUser(User *user);

    bool addCourse(QString title, int teacherId);

    bool addEnrollment(int studentId, int courseId);
    bool setGrade(int enrollmentId, int value);
    bool setGradeForStudentInCourse(int studentId, int courseId, int value);

    User *login(QString login, QString password);
    bool registerUser(QString fullName, QString login, QString password, QString roleName);

    vector<Course> getCoursesByTeacher(int teacherId);
    vector<Course> getCoursesByStudent(int studentId);
    vector<User *> getStudentsForCourse(int courseId);
    double getAverageGradeForStudent(int studentId);
};

#endif

#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QList>
#include <QString>
#include "user.h"
#include "course.h"
#include "enrollment.h"
#include "grade.h"

class DatabaseManager
{
public:
    DatabaseManager();
    ~DatabaseManager();

    bool ensureDefaultAdmin();
    bool loadAll();
    bool saveAll();

    const QList<User *> &getUsers() const;
    const QList<Course> &getCourses() const;
    const QList<Enrollment> &getEnrollments() const;
    const QList<Grade> &getGrades() const;

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

    QList<Course> getCoursesByTeacher(int teacherId) const;
    QList<Course> getCoursesByStudent(int studentId) const;
    QList<User *> getStudentsForCourse(int courseId) const;
    double getAverageGradeForStudent(int studentId) const;

private:
    QList<User *> m_users;
    QList<Course> m_courses;
    QList<Enrollment> m_enrollments;
    QList<Grade> m_grades;

    int m_nextCourseId;
    int m_nextEnrollmentId;
    int m_nextGradeId;

    QString m_usersPath;
    QString m_coursesPath;
    QString m_enrollmentsPath;
    QString m_gradesPath;

    void clearUsers();
    User *createUserByRole(const QString &role, int id, const QString &login, const QString &password, const QString &fullName) const;
};

#endif

#ifndef MODELS_H
#define MODELS_H

#include <QString>

enum UserRole
{
    RoleAdmin,
    RoleTeacher,
    RoleStudent
};

class User
{
private:
    static int s_nextId;

protected:
    int m_id;
    QString m_login;
    QString m_password;
    QString m_fullName;

public:
    User();
    User(int id, QString login, QString password, QString fullName);
    User(const User &other);
    virtual ~User();

    User &operator=(const User &other);
    bool operator==(User &other);

    int getId();
    QString getLogin();
    QString getPassword();
    QString getFullName();

    void setLogin(QString login);
    void setPassword(QString password);
    void setFullName(QString fullName);

    virtual UserRole getRole() = 0;
    virtual QString getRoleName() = 0;
    virtual User *clone() = 0;

    static int generateNextId();
    static void setNextId(int nextId);
};

class Admin : public User
{
public:
    Admin();
    Admin(int id, QString login, QString password, QString fullName);
    virtual ~Admin();

    virtual UserRole getRole();
    virtual QString getRoleName();
    virtual User *clone();
};

class Teacher : public User
{
public:
    Teacher();
    Teacher(int id, QString login, QString password, QString fullName);
    virtual ~Teacher();

    virtual UserRole getRole();
    virtual QString getRoleName();
    virtual User *clone();
};

class Student : public User
{
public:
    Student();
    Student(int id, QString login, QString password, QString fullName);
    virtual ~Student();

    virtual UserRole getRole();
    virtual QString getRoleName();
    virtual User *clone();
};

class Course
{
private:
    int m_id;
    QString m_title;
    int m_teacherId;

public:
    Course();
    Course(int id, QString title, int teacherId);

    int getId();
    QString getTitle();
    int getTeacherId();

    void setTitle(QString title);
    void setTeacherId(int teacherId);
};

class Enrollment
{
private:
    int m_id;
    int m_studentId;
    int m_courseId;

public:
    Enrollment();
    Enrollment(int id, int studentId, int courseId);

    int getId();
    int getStudentId();
    int getCourseId();
};

class Grade
{
private:
    int m_id;
    int m_enrollmentId;
    int m_value;

public:
    Grade();
    Grade(int id, int enrollmentId, int value);
    Grade(const Grade &other);

    Grade &operator=(const Grade &other);

    int getId();
    int getEnrollmentId();
    int getValue();

    void setValue(int value);
};

#endif

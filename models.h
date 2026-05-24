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
public:
    User();
    User(int id, const QString &login, const QString &password, const QString &fullName);
    User(const User &other);
    virtual ~User();

    User &operator=(const User &other);
    bool operator==(const User &other) const;

    int getId() const;
    QString getLogin() const;
    QString getPassword() const;
    QString getFullName() const;

    void setLogin(const QString &login);
    void setPassword(const QString &password);
    void setFullName(const QString &fullName);

    virtual UserRole getRole() const = 0;
    virtual QString getRoleName() const = 0;
    virtual User *clone() const = 0;

    static int generateNextId();
    static void setNextId(int nextId);

protected:
    int m_id;
    QString m_login;
    QString m_password;
    QString m_fullName;

private:
    static int s_nextId;
};

class Admin : public User
{
public:
    Admin();
    Admin(int id, const QString &login, const QString &password, const QString &fullName);
    virtual ~Admin();

    virtual UserRole getRole() const;
    virtual QString getRoleName() const;
    virtual User *clone() const;
};

class Teacher : public User
{
public:
    Teacher();
    Teacher(int id, const QString &login, const QString &password, const QString &fullName);
    virtual ~Teacher();

    virtual UserRole getRole() const;
    virtual QString getRoleName() const;
    virtual User *clone() const;
};

class Student : public User
{
public:
    Student();
    Student(int id, const QString &login, const QString &password, const QString &fullName);
    virtual ~Student();

    virtual UserRole getRole() const;
    virtual QString getRoleName() const;
    virtual User *clone() const;
};

class Course
{
public:
    Course();
    Course(int id, const QString &title, int teacherId);

    int getId() const;
    QString getTitle() const;
    int getTeacherId() const;

    void setTitle(const QString &title);
    void setTeacherId(int teacherId);

private:
    int m_id;
    QString m_title;
    int m_teacherId;
};

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

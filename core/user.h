#ifndef USER_H
#define USER_H

#include <QString>
#include <ostream>

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

    friend std::ostream &operator<<(std::ostream &os, const User &user);

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

#endif

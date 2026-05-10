#include "user.h"

int User::s_nextId = 1;

User::User()
    : m_id(0)
{
}

User::User(int id, const QString &login, const QString &password, const QString &fullName)
    : m_id(id), m_login(login), m_password(password), m_fullName(fullName)
{
}

User::User(const User &other)
    : m_id(other.m_id),
      m_login(other.m_login),
      m_password(other.m_password),
      m_fullName(other.m_fullName)
{
}

User::~User()
{
}

User &User::operator=(const User &other)
{
    if (this != &other)
    {
        m_id = other.m_id;
        m_login = other.m_login;
        m_password = other.m_password;
        m_fullName = other.m_fullName;
    }
    return *this;
}

bool User::operator==(const User &other) const
{
    return m_id == other.m_id && m_login == other.m_login;
}

int User::getId() const
{
    return m_id;
}

QString User::getLogin() const
{
    return m_login;
}

QString User::getPassword() const
{
    return m_password;
}

QString User::getFullName() const
{
    return m_fullName;
}

void User::setLogin(const QString &login)
{
    m_login = login;
}

void User::setPassword(const QString &password)
{
    m_password = password;
}

void User::setFullName(const QString &fullName)
{
    m_fullName = fullName;
}

int User::generateNextId()
{
    int value = s_nextId;
    s_nextId++;
    return value;
}

void User::setNextId(int nextId)
{
    if (nextId > s_nextId)
    {
        s_nextId = nextId;
    }
}

std::ostream &operator<<(std::ostream &os, const User &user)
{
    os << user.getId() << " | "
       << user.getFullName().toStdString() << " | "
       << user.getLogin().toStdString() << " | "
       << user.getRoleName().toStdString();
    return os;
}

Admin::Admin()
    : User()
{
}

Admin::Admin(int id, const QString &login, const QString &password, const QString &fullName)
    : User(id, login, password, fullName)
{
}

Admin::~Admin()
{
}

UserRole Admin::getRole() const
{
    return RoleAdmin;
}

QString Admin::getRoleName() const
{
    return "admin";
}

User *Admin::clone() const
{
    return new Admin(*this);
}

Teacher::Teacher()
    : User()
{
}

Teacher::Teacher(int id, const QString &login, const QString &password, const QString &fullName)
    : User(id, login, password, fullName)
{
}

Teacher::~Teacher()
{
}

UserRole Teacher::getRole() const
{
    return RoleTeacher;
}

QString Teacher::getRoleName() const
{
    return "teacher";
}

User *Teacher::clone() const
{
    return new Teacher(*this);
}

Student::Student()
    : User()
{
}

Student::Student(int id, const QString &login, const QString &password, const QString &fullName)
    : User(id, login, password, fullName)
{
}

Student::~Student()
{
}

UserRole Student::getRole() const
{
    return RoleStudent;
}

QString Student::getRoleName() const
{
    return "student";
}

User *Student::clone() const
{
    return new Student(*this);
}

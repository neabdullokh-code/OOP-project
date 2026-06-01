#include "models.h"

int User::s_nextId = 1;

User::User()
    : m_id(0)
{
}

User::User(int id, QString login, QString password, QString fullName)
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

bool User::operator==(User &other)
{
    return m_id == other.m_id && m_login == other.m_login;
}

int User::getId()
{
    return m_id;
}

QString User::getLogin()
{
    return m_login;
}

QString User::getPassword()
{
    return m_password;
}

QString User::getFullName()
{
    return m_fullName;
}

void User::setLogin(QString login)
{
    m_login = login;
}

void User::setPassword(QString password)
{
    m_password = password;
}

void User::setFullName(QString fullName)
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

Admin::Admin()
    : User()
{
}

Admin::Admin(int id, QString login, QString password, QString fullName)
    : User(id, login, password, fullName)
{
}

Admin::~Admin()
{
}

UserRole Admin::getRole()
{
    return RoleAdmin;
}

QString Admin::getRoleName()
{
    return "admin";
}

User *Admin::clone()
{
    return new Admin(*this);
}

Teacher::Teacher()
    : User()
{
}

Teacher::Teacher(int id, QString login, QString password, QString fullName)
    : User(id, login, password, fullName)
{
}

Teacher::~Teacher()
{
}

UserRole Teacher::getRole()
{
    return RoleTeacher;
}

QString Teacher::getRoleName()
{
    return "teacher";
}

User *Teacher::clone()
{
    return new Teacher(*this);
}

Student::Student()
    : User()
{
}

Student::Student(int id, QString login, QString password, QString fullName)
    : User(id, login, password, fullName)
{
}

Student::~Student()
{
}

UserRole Student::getRole()
{
    return RoleStudent;
}

QString Student::getRoleName()
{
    return "student";
}

User *Student::clone()
{
    return new Student(*this);
}

Course::Course()
    : m_id(0), m_teacherId(0)
{
}

Course::Course(int id, QString title, int teacherId)
    : m_id(id), m_title(title), m_teacherId(teacherId)
{
}

int Course::getId()
{
    return m_id;
}

QString Course::getTitle()
{
    return m_title;
}

int Course::getTeacherId()
{
    return m_teacherId;
}

void Course::setTitle(QString title)
{
    m_title = title;
}

void Course::setTeacherId(int teacherId)
{
    m_teacherId = teacherId;
}

Enrollment::Enrollment()
    : m_id(0), m_studentId(0), m_courseId(0)
{
}

Enrollment::Enrollment(int id, int studentId, int courseId)
    : m_id(id), m_studentId(studentId), m_courseId(courseId)
{
}

int Enrollment::getId()
{
    return m_id;
}

int Enrollment::getStudentId()
{
    return m_studentId;
}

int Enrollment::getCourseId()
{
    return m_courseId;
}

Grade::Grade()
    : m_id(0), m_enrollmentId(0), m_value(0)
{
}

Grade::Grade(int id, int enrollmentId, int value)
    : m_id(id), m_enrollmentId(enrollmentId), m_value(value)
{
}

Grade::Grade(const Grade &other)
    : m_id(other.m_id),
      m_enrollmentId(other.m_enrollmentId),
      m_value(other.m_value)
{
}

Grade &Grade::operator=(const Grade &other)
{
    if (this != &other)
    {
        m_id = other.m_id;
        m_enrollmentId = other.m_enrollmentId;
        m_value = other.m_value;
    }
    return *this;
}

int Grade::getId()
{
    return m_id;
}

int Grade::getEnrollmentId()
{
    return m_enrollmentId;
}

int Grade::getValue()
{
    return m_value;
}

void Grade::setValue(int value)
{
    m_value = value;
}

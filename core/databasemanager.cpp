#include "databasemanager.h"
#include <QDir>
#include <QStringList>
#include <fstream>

DatabaseManager::DatabaseManager()
    : m_nextCourseId(1), m_nextEnrollmentId(1), m_nextGradeId(1)
{
    QString dataDir = QDir::currentPath() + "/data";
    QDir().mkpath(dataDir);

    m_usersPath = dataDir + "/users.txt";
    m_coursesPath = dataDir + "/courses.txt";
    m_enrollmentsPath = dataDir + "/enrollments.txt";
    m_gradesPath = dataDir + "/grades.txt";
}

DatabaseManager::~DatabaseManager()
{
    clearUsers();
}

void DatabaseManager::clearUsers()
{
    int i;
    for (i = 0; i < m_users.size(); i++)
    {
        delete m_users[i];
    }
    m_users.clear();
}

bool DatabaseManager::ensureDefaultAdmin()
{
    std::ifstream checkFile(m_usersPath.toStdString().c_str());
    if (checkFile.good())
    {
        std::string line;
        while (std::getline(checkFile, line))
        {
            if (!line.empty())
            {
                return true;
            }
        }
    }

    std::ofstream usersFile(m_usersPath.toStdString().c_str(), std::ios::out | std::ios::trunc);
    if (!usersFile.is_open())
    {
        return false;
    }

    usersFile << "1;admin;admin123;Administrator;admin\n";
    usersFile.close();
    return true;
}

User *DatabaseManager::createUserByRole(const QString &role, int id, const QString &login, const QString &password, const QString &fullName) const
{
    if (role == "admin")
    {
        return new Admin(id, login, password, fullName);
    }
    if (role == "teacher")
    {
        return new Teacher(id, login, password, fullName);
    }
    return new Student(id, login, password, fullName);
}

bool DatabaseManager::loadAll()
{
    clearUsers();
    m_courses.clear();
    m_enrollments.clear();
    m_grades.clear();

    m_nextCourseId = 1;
    m_nextEnrollmentId = 1;
    m_nextGradeId = 1;
    User::setNextId(1);

    std::ifstream usersFile(m_usersPath.toStdString().c_str());
    if (usersFile.is_open())
    {
        std::string line;
        while (std::getline(usersFile, line))
        {
            if (line.empty())
            {
                continue;
            }
            QString qLine = QString::fromStdString(line);
            QStringList parts = qLine.split(";");
            if (parts.size() != 5)
            {
                continue;
            }

            int id = parts[0].toInt();
            QString login = parts[1];
            QString password = parts[2];
            QString fullName = parts[3];
            QString role = parts[4];

            User *newUser = createUserByRole(role, id, login, password, fullName);
            m_users.append(newUser);
            User::setNextId(id + 1);
        }
        usersFile.close();
    }

    std::ifstream coursesFile(m_coursesPath.toStdString().c_str());
    if (coursesFile.is_open())
    {
        std::string line;
        while (std::getline(coursesFile, line))
        {
            if (line.empty())
            {
                continue;
            }
            QString qLine = QString::fromStdString(line);
            QStringList parts = qLine.split(";");
            if (parts.size() != 3)
            {
                continue;
            }

            int id = parts[0].toInt();
            QString title = parts[1];
            int teacherId = parts[2].toInt();

            m_courses.append(Course(id, title, teacherId));
            if (id >= m_nextCourseId)
            {
                m_nextCourseId = id + 1;
            }
        }
        coursesFile.close();
    }

    std::ifstream enrollmentsFile(m_enrollmentsPath.toStdString().c_str());
    if (enrollmentsFile.is_open())
    {
        std::string line;
        while (std::getline(enrollmentsFile, line))
        {
            if (line.empty())
            {
                continue;
            }
            QString qLine = QString::fromStdString(line);
            QStringList parts = qLine.split(";");
            if (parts.size() != 3)
            {
                continue;
            }

            int id = parts[0].toInt();
            int studentId = parts[1].toInt();
            int courseId = parts[2].toInt();

            m_enrollments.append(Enrollment(id, studentId, courseId));
            if (id >= m_nextEnrollmentId)
            {
                m_nextEnrollmentId = id + 1;
            }
        }
        enrollmentsFile.close();
    }

    std::ifstream gradesFile(m_gradesPath.toStdString().c_str());
    if (gradesFile.is_open())
    {
        std::string line;
        while (std::getline(gradesFile, line))
        {
            if (line.empty())
            {
                continue;
            }
            QString qLine = QString::fromStdString(line);
            QStringList parts = qLine.split(";");
            if (parts.size() != 3)
            {
                continue;
            }

            int id = parts[0].toInt();
            int enrollmentId = parts[1].toInt();
            int value = parts[2].toInt();

            m_grades.append(Grade(id, enrollmentId, value));
            if (id >= m_nextGradeId)
            {
                m_nextGradeId = id + 1;
            }
        }
        gradesFile.close();
    }

    return true;
}

bool DatabaseManager::saveAll()
{
    std::ofstream usersFile(m_usersPath.toStdString().c_str(), std::ios::out | std::ios::trunc);
    if (!usersFile.is_open())
    {
        return false;
    }
    int i;
    for (i = 0; i < m_users.size(); i++)
    {
        User *user = m_users[i];
        usersFile << user->getId() << ";"
                  << user->getLogin().toStdString() << ";"
                  << user->getPassword().toStdString() << ";"
                  << user->getFullName().toStdString() << ";"
                  << user->getRoleName().toStdString() << "\n";
    }
    usersFile.close();

    std::ofstream coursesFile(m_coursesPath.toStdString().c_str(), std::ios::out | std::ios::trunc);
    if (!coursesFile.is_open())
    {
        return false;
    }
    for (i = 0; i < m_courses.size(); i++)
    {
        const Course &course = m_courses[i];
        coursesFile << course.getId() << ";"
                    << course.getTitle().toStdString() << ";"
                    << course.getTeacherId() << "\n";
    }
    coursesFile.close();

    std::ofstream enrollmentsFile(m_enrollmentsPath.toStdString().c_str(), std::ios::out | std::ios::trunc);
    if (!enrollmentsFile.is_open())
    {
        return false;
    }
    for (i = 0; i < m_enrollments.size(); i++)
    {
        const Enrollment &enrollment = m_enrollments[i];
        enrollmentsFile << enrollment.getId() << ";"
                        << enrollment.getStudentId() << ";"
                        << enrollment.getCourseId() << "\n";
    }
    enrollmentsFile.close();

    std::ofstream gradesFile(m_gradesPath.toStdString().c_str(), std::ios::out | std::ios::trunc);
    if (!gradesFile.is_open())
    {
        return false;
    }
    for (i = 0; i < m_grades.size(); i++)
    {
        const Grade &grade = m_grades[i];
        gradesFile << grade.getId() << ";"
                   << grade.getEnrollmentId() << ";"
                   << grade.getValue() << "\n";
    }
    gradesFile.close();

    return true;
}

const QList<User *> &DatabaseManager::getUsers() const
{
    return m_users;
}

const QList<Course> &DatabaseManager::getCourses() const
{
    return m_courses;
}

const QList<Enrollment> &DatabaseManager::getEnrollments() const
{
    return m_enrollments;
}

const QList<Grade> &DatabaseManager::getGrades() const
{
    return m_grades;
}

User *DatabaseManager::findUserByLogin(const QString &login) const
{
    int i;
    for (i = 0; i < m_users.size(); i++)
    {
        if (m_users[i]->getLogin() == login)
        {
            return m_users[i];
        }
    }
    return 0;
}

User *DatabaseManager::findUserById(int id) const
{
    int i;
    for (i = 0; i < m_users.size(); i++)
    {
        if (m_users[i]->getId() == id)
        {
            return m_users[i];
        }
    }
    return 0;
}

Course *DatabaseManager::findCourseById(int id)
{
    int i;
    for (i = 0; i < m_courses.size(); i++)
    {
        if (m_courses[i].getId() == id)
        {
            return &m_courses[i];
        }
    }
    return 0;
}

Enrollment *DatabaseManager::findEnrollmentById(int id)
{
    int i;
    for (i = 0; i < m_enrollments.size(); i++)
    {
        if (m_enrollments[i].getId() == id)
        {
            return &m_enrollments[i];
        }
    }
    return 0;
}

Grade *DatabaseManager::findGradeByEnrollmentId(int enrollmentId)
{
    int i;
    for (i = 0; i < m_grades.size(); i++)
    {
        if (m_grades[i].getEnrollmentId() == enrollmentId)
        {
            return &m_grades[i];
        }
    }
    return 0;
}

bool DatabaseManager::loginExists(const QString &login) const
{
    return findUserByLogin(login) != 0;
}

bool DatabaseManager::addUser(User *user)
{
    if (user == 0)
    {
        return false;
    }
    if (loginExists(user->getLogin()))
    {
        return false;
    }

    m_users.append(user);
    return saveAll();
}

bool DatabaseManager::removeUser(int userId)
{
    int i;
    for (i = 0; i < m_users.size(); i++)
    {
        if (m_users[i]->getId() == userId)
        {
            delete m_users[i];
            m_users.removeAt(i);
            return saveAll();
        }
    }
    return false;
}

bool DatabaseManager::addCourse(const QString &title, int teacherId)
{
    if (title.trimmed().isEmpty())
    {
        return false;
    }
    if (findUserById(teacherId) == 0)
    {
        return false;
    }

    m_courses.append(Course(m_nextCourseId, title.trimmed(), teacherId));
    m_nextCourseId++;
    return saveAll();
}

bool DatabaseManager::removeCourse(int courseId)
{
    int i;
    for (i = 0; i < m_courses.size(); i++)
    {
        if (m_courses[i].getId() == courseId)
        {
            m_courses.removeAt(i);
            return saveAll();
        }
    }
    return false;
}

bool DatabaseManager::addEnrollment(int studentId, int courseId)
{
    int i;
    for (i = 0; i < m_enrollments.size(); i++)
    {
        if (m_enrollments[i].getStudentId() == studentId &&
            m_enrollments[i].getCourseId() == courseId)
        {
            return false;
        }
    }

    m_enrollments.append(Enrollment(m_nextEnrollmentId, studentId, courseId));
    m_nextEnrollmentId++;
    return saveAll();
}

bool DatabaseManager::upsertGrade(int enrollmentId, int value)
{
    if (value < 0 || value > 100)
    {
        return false;
    }

    Grade *existingGrade = findGradeByEnrollmentId(enrollmentId);
    if (existingGrade != 0)
    {
        existingGrade->setValue(value);
    }
    else
    {
        m_grades.append(Grade(m_nextGradeId, enrollmentId, value));
        m_nextGradeId++;
    }

    return saveAll();
}

QList<Course> DatabaseManager::getCoursesByTeacher(int teacherId) const
{
    QList<Course> result;
    int i;
    for (i = 0; i < m_courses.size(); i++)
    {
        if (m_courses[i].getTeacherId() == teacherId)
        {
            result.append(m_courses[i]);
        }
    }
    return result;
}

QList<Course> DatabaseManager::getCoursesByStudent(int studentId) const
{
    QList<Course> result;
    int i;
    for (i = 0; i < m_enrollments.size(); i++)
    {
        if (m_enrollments[i].getStudentId() == studentId)
        {
            int courseId = m_enrollments[i].getCourseId();
            int j;
            for (j = 0; j < m_courses.size(); j++)
            {
                if (m_courses[j].getId() == courseId)
                {
                    result.append(m_courses[j]);
                    break;
                }
            }
        }
    }
    return result;
}

QList<User *> DatabaseManager::getStudentsForCourse(int courseId) const
{
    QList<User *> result;
    int i;
    for (i = 0; i < m_enrollments.size(); i++)
    {
        if (m_enrollments[i].getCourseId() == courseId)
        {
            int studentId = m_enrollments[i].getStudentId();
            User *user = findUserById(studentId);
            if (user != 0 && user->getRole() == RoleStudent)
            {
                result.append(user);
            }
        }
    }
    return result;
}

double DatabaseManager::getAverageGradeForStudent(int studentId) const
{
    int sum = 0;
    int count = 0;

    int i;
    for (i = 0; i < m_enrollments.size(); i++)
    {
        if (m_enrollments[i].getStudentId() == studentId)
        {
            int enrollmentId = m_enrollments[i].getId();
            int j;
            for (j = 0; j < m_grades.size(); j++)
            {
                if (m_grades[j].getEnrollmentId() == enrollmentId)
                {
                    sum += m_grades[j].getValue();
                    count++;
                }
            }
        }
    }

    if (count == 0)
    {
        return 0.0;
    }
    return static_cast<double>(sum) / count;
}

#include "filemanager.h"
#include <fstream>

using namespace std;

static int splitSemicolon(string line, string parts[], int maxParts)
{
    int count = 0;
    size_t start = 0;
    size_t i;

    for (i = 0; i <= line.size(); i++)
    {
        if (i == line.size() || line[i] == ';')
        {
            if (count < maxParts)
            {
                parts[count] = line.substr(start, i - start);
                count++;
            }
            start = i + 1;
        }
    }
    return count;
}

static int stringToInt(string text)
{
    int result = 0;
    int i;

    for (i = 0; i < text.size(); i++)
    {
        if (text[i] >= '0' && text[i] <= '9')
        {
            result = result * 10 + (text[i] - '0');
        }
    }
    return result;
}

FileManager::FileManager()
    : m_nextCourseId(1), m_nextEnrollmentId(1), m_nextGradeId(1)
{
    m_usersPath = "users.txt";
    m_coursesPath = "courses.txt";
    m_enrollmentsPath = "enrollments.txt";
    m_gradesPath = "grades.txt";
}

FileManager::~FileManager()
{
    clearUsers();
}

void FileManager::clearUsers()
{
    int i;
    for (i = 0; i < m_users.size(); i++)
    {
        delete m_users[i];
    }
    m_users.clear();
}

bool FileManager::ensureDefaultAdmin()
{
    ifstream checkFile(m_usersPath.c_str());
    if (checkFile.good())
    {
        string line;
        while (getline(checkFile, line))
        {
            if (!line.empty())
            {
                return true;
            }
        }
    }

    ofstream usersFile(m_usersPath.c_str(), ios::out | ios::trunc);
    if (!usersFile.is_open())
    {
        return false;
    }

    usersFile << "1;admin;admin123;Administrator;admin\n";
    usersFile.close();
    return true;
}

User *FileManager::createUserByRole(QString role, int id, QString login, QString password, QString fullName)
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

bool FileManager::loadAll()
{
    clearUsers();
    m_courses.clear();
    m_enrollments.clear();
    m_grades.clear();

    m_nextCourseId = 1;
    m_nextEnrollmentId = 1;
    m_nextGradeId = 1;
    User::setNextId(1);

    ifstream usersFile(m_usersPath.c_str());
    if (usersFile.is_open())
    {
        string line;
        while (getline(usersFile, line))
        {
            if (line.empty())
            {
                continue;
            }

            string parts[5];
            if (splitSemicolon(line, parts, 5) != 5)
            {
                continue;
            }

            int id = stringToInt(parts[0]);
            QString login = QString::fromStdString(parts[1]);
            QString password = QString::fromStdString(parts[2]);
            QString fullName = QString::fromStdString(parts[3]);
            QString role = QString::fromStdString(parts[4]);

            User *newUser = createUserByRole(role, id, login, password, fullName);
            m_users.push_back(newUser);
            User::setNextId(id + 1);
        }
        usersFile.close();
    }

    ifstream coursesFile(m_coursesPath.c_str());
    if (coursesFile.is_open())
    {
        string line;
        while (getline(coursesFile, line))
        {
            if (line.empty())
            {
                continue;
            }

            string parts[3];
            if (splitSemicolon(line, parts, 3) != 3)
            {
                continue;
            }

            int id = stringToInt(parts[0]);
            QString title = QString::fromStdString(parts[1]);
            int teacherId = stringToInt(parts[2]);

            m_courses.push_back(Course(id, title, teacherId));
            if (id >= m_nextCourseId)
            {
                m_nextCourseId = id + 1;
            }
        }
        coursesFile.close();
    }

    ifstream enrollmentsFile(m_enrollmentsPath.c_str());
    if (enrollmentsFile.is_open())
    {
        string line;
        while (getline(enrollmentsFile, line))
        {
            if (line.empty())
            {
                continue;
            }

            string parts[3];
            if (splitSemicolon(line, parts, 3) != 3)
            {
                continue;
            }

            int id = stringToInt(parts[0]);
            int studentId = stringToInt(parts[1]);
            int courseId = stringToInt(parts[2]);

            m_enrollments.push_back(Enrollment(id, studentId, courseId));
            if (id >= m_nextEnrollmentId)
            {
                m_nextEnrollmentId = id + 1;
            }
        }
        enrollmentsFile.close();
    }

    ifstream gradesFile(m_gradesPath.c_str());
    if (gradesFile.is_open())
    {
        string line;
        while (getline(gradesFile, line))
        {
            if (line.empty())
            {
                continue;
            }

            string parts[3];
            if (splitSemicolon(line, parts, 3) != 3)
            {
                continue;
            }

            int id = stringToInt(parts[0]);
            int enrollmentId = stringToInt(parts[1]);
            int value = stringToInt(parts[2]);

            m_grades.push_back(Grade(id, enrollmentId, value));
            if (id >= m_nextGradeId)
            {
                m_nextGradeId = id + 1;
            }
        }
        gradesFile.close();
    }

    return true;
}

bool FileManager::saveAll()
{
    ofstream usersFile(m_usersPath.c_str(), ios::out | ios::trunc);
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

    ofstream coursesFile(m_coursesPath.c_str(), ios::out | ios::trunc);
    if (!coursesFile.is_open())
    {
        return false;
    }
    for (i = 0; i < m_courses.size(); i++)
    {
        coursesFile << m_courses[i].getId() << ";"
                    << m_courses[i].getTitle().toStdString() << ";"
                    << m_courses[i].getTeacherId() << "\n";
    }
    coursesFile.close();

    ofstream enrollmentsFile(m_enrollmentsPath.c_str(), ios::out | ios::trunc);
    if (!enrollmentsFile.is_open())
    {
        return false;
    }
    for (i = 0; i < m_enrollments.size(); i++)
    {
        enrollmentsFile << m_enrollments[i].getId() << ";"
                        << m_enrollments[i].getStudentId() << ";"
                        << m_enrollments[i].getCourseId() << "\n";
    }
    enrollmentsFile.close();

    ofstream gradesFile(m_gradesPath.c_str(), ios::out | ios::trunc);
    if (!gradesFile.is_open())
    {
        return false;
    }
    for (i = 0; i < m_grades.size(); i++)
    {
        gradesFile << m_grades[i].getId() << ";"
                   << m_grades[i].getEnrollmentId() << ";"
                   << m_grades[i].getValue() << "\n";
    }
    gradesFile.close();

    return true;
}

vector<User *> FileManager::getUsers()
{
    return m_users;
}

vector<Course> FileManager::getCourses()
{
    return m_courses;
}

vector<Enrollment> FileManager::getEnrollments()
{
    return m_enrollments;
}

vector<Grade> FileManager::getGrades()
{
    return m_grades;
}

User *FileManager::findUserByLogin(QString login)
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

User *FileManager::findUserById(int id)
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

Course *FileManager::findCourseById(int id)
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

Enrollment *FileManager::findEnrollmentById(int id)
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

Grade *FileManager::findGradeByEnrollmentId(int enrollmentId)
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

bool FileManager::loginExists(QString login)
{
    return findUserByLogin(login) != 0;
}

bool FileManager::addUser(User *user)
{
    if (user == 0)
    {
        return false;
    }
    if (loginExists(user->getLogin()))
    {
        return false;
    }

    m_users.push_back(user);
    return saveAll();
}

bool FileManager::removeUser(int userId)
{
    int i;
    for (i = 0; i < m_users.size(); i++)
    {
        if (m_users[i]->getId() == userId)
        {
            delete m_users[i];
            m_users.erase(m_users.begin() + i);
            return saveAll();
        }
    }
    return false;
}

bool FileManager::addCourse(QString title, int teacherId)
{
    if (title.trimmed().isEmpty())
    {
        return false;
    }
    if (findUserById(teacherId) == 0)
    {
        return false;
    }

    m_courses.push_back(Course(m_nextCourseId, title.trimmed(), teacherId));
    m_nextCourseId++;
    return saveAll();
}

bool FileManager::removeCourse(int courseId)
{
    int i;
    for (i = 0; i < m_courses.size(); i++)
    {
        if (m_courses[i].getId() == courseId)
        {
            m_courses.erase(m_courses.begin() + i);
            return saveAll();
        }
    }
    return false;
}

bool FileManager::addEnrollment(int studentId, int courseId)
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

    m_enrollments.push_back(Enrollment(m_nextEnrollmentId, studentId, courseId));
    m_nextEnrollmentId++;
    return saveAll();
}

bool FileManager::setGrade(int enrollmentId, int value)
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
        m_grades.push_back(Grade(m_nextGradeId, enrollmentId, value));
        m_nextGradeId++;
    }

    return saveAll();
}

vector<Course> FileManager::getCoursesByTeacher(int teacherId)
{
    vector<Course> result;
    int i;
    for (i = 0; i < m_courses.size(); i++)
    {
        if (m_courses[i].getTeacherId() == teacherId)
        {
            result.push_back(m_courses[i]);
        }
    }
    return result;
}

vector<Course> FileManager::getCoursesByStudent(int studentId)
{
    vector<Course> result;
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
                    result.push_back(m_courses[j]);
                    break;
                }
            }
        }
    }
    return result;
}

vector<User *> FileManager::getStudentsForCourse(int courseId)
{
    vector<User *> result;
    int i;
    for (i = 0; i < m_enrollments.size(); i++)
    {
        if (m_enrollments[i].getCourseId() == courseId)
        {
            int studentId = m_enrollments[i].getStudentId();
            User *user = findUserById(studentId);
            if (user != 0 && user->getRole() == RoleStudent)
            {
                result.push_back(user);
            }
        }
    }
    return result;
}

double FileManager::getAverageGradeForStudent(int studentId)
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
    return (double)sum / count;
}

User *FileManager::login(QString login, QString password)
{
    User *user = findUserByLogin(login.trimmed());
    if (user == 0)
    {
        return 0;
    }
    if (user->getPassword() != password)
    {
        return 0;
    }
    return user;
}

bool FileManager::registerUser(QString fullName, QString login, QString password, QString roleName)
{
    if (fullName.trimmed().isEmpty() || login.trimmed().isEmpty() || password.isEmpty())
    {
        return false;
    }
    if (loginExists(login.trimmed()))
    {
        return false;
    }

    User *newUser = 0;
    int newId = User::generateNextId();

    if (roleName == "teacher")
    {
        newUser = new Teacher(newId, login.trimmed(), password, fullName.trimmed());
    }
    else
    {
        newUser = new Student(newId, login.trimmed(), password, fullName.trimmed());
    }

    return addUser(newUser);
}

bool FileManager::setGradeForStudentInCourse(int studentId, int courseId, int value)
{
    int i;
    for (i = 0; i < m_enrollments.size(); i++)
    {
        if (m_enrollments[i].getStudentId() == studentId && m_enrollments[i].getCourseId() == courseId)
        {
            return setGrade(m_enrollments[i].getId(), value);
        }
    }

    if (!addEnrollment(studentId, courseId))
    {
        return false;
    }

    for (i = 0; i < m_enrollments.size(); i++)
    {
        if (m_enrollments[i].getStudentId() == studentId &&
            m_enrollments[i].getCourseId() == courseId)
        {
            return setGrade(m_enrollments[i].getId(), value);
        }
    }
    return false;
}

vector<User *> FileManager::getTeachers()
{
    vector<User *> result;
    int i;
    for (i = 0; i < m_users.size(); i++)
    {
        if (m_users[i]->getRole() == RoleTeacher)
        {
            result.push_back(m_users[i]);
        }
    }
    return result;
}

vector<User *> FileManager::getStudents()
{
    vector<User *> result;
    int i;
    for (i = 0; i < m_users.size(); i++)
    {
        if (m_users[i]->getRole() == RoleStudent)
        {
            result.push_back(m_users[i]);
        }
    }
    return result;
}

#include "controllers.h"

AuthController::AuthController(DatabaseManager *databaseManager)
    : m_databaseManager(databaseManager)
{
}

User *AuthController::login(const QString &login, const QString &password) const
{
    if (m_databaseManager == 0)
    {
        return 0;
    }

    User *user = m_databaseManager->findUserByLogin(login.trimmed());
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

bool AuthController::registerUser(const QString &fullName, const QString &login, const QString &password, const QString &roleName) const
{
    if (m_databaseManager == 0)
    {
        return false;
    }
    if (fullName.trimmed().isEmpty() || login.trimmed().isEmpty() || password.isEmpty())
    {
        return false;
    }
    if (m_databaseManager->loginExists(login.trimmed()))
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

    return m_databaseManager->addUser(newUser);
}

CourseController::CourseController(DatabaseManager *databaseManager)
    : m_databaseManager(databaseManager)
{
}

bool CourseController::createCourse(const QString &title, int teacherId) const
{
    if (m_databaseManager == 0)
    {
        return false;
    }
    return m_databaseManager->addCourse(title, teacherId);
}

bool CourseController::removeCourse(int courseId) const
{
    if (m_databaseManager == 0)
    {
        return false;
    }
    return m_databaseManager->removeCourse(courseId);
}

bool CourseController::enrollStudent(int studentId, int courseId) const
{
    if (m_databaseManager == 0)
    {
        return false;
    }
    return m_databaseManager->addEnrollment(studentId, courseId);
}

std::vector<Course> CourseController::getAllCourses() const
{
    if (m_databaseManager == 0)
    {
        return std::vector<Course>();
    }
    return m_databaseManager->getCourses();
}

std::vector<Course> CourseController::getCoursesByTeacher(int teacherId) const
{
    if (m_databaseManager == 0)
    {
        return std::vector<Course>();
    }
    return m_databaseManager->getCoursesByTeacher(teacherId);
}

std::vector<Course> CourseController::getCoursesByStudent(int studentId) const
{
    if (m_databaseManager == 0)
    {
        return std::vector<Course>();
    }
    return m_databaseManager->getCoursesByStudent(studentId);
}

GradeController::GradeController(DatabaseManager *databaseManager)
    : m_databaseManager(databaseManager)
{
}

bool GradeController::setGradeForStudentInCourse(int studentId, int courseId, int value) const
{
    if (m_databaseManager == 0)
    {
        return false;
    }

    const std::vector<Enrollment> &enrollments = m_databaseManager->getEnrollments();
    int i;
    for (i = 0; i < enrollments.size(); i++)
    {
        if (enrollments[i].getStudentId() == studentId && enrollments[i].getCourseId() == courseId)
        {
            return m_databaseManager->upsertGrade(enrollments[i].getId(), value);
        }
    }

    if (!m_databaseManager->addEnrollment(studentId, courseId))
    {
        return false;
    }

    const std::vector<Enrollment> &updatedEnrollments = m_databaseManager->getEnrollments();
    for (i = 0; i < updatedEnrollments.size(); i++)
    {
        if (updatedEnrollments[i].getStudentId() == studentId &&
            updatedEnrollments[i].getCourseId() == courseId)
        {
            return m_databaseManager->upsertGrade(updatedEnrollments[i].getId(), value);
        }
    }
    return false;
}

int GradeController::getGradeForEnrollment(int enrollmentId) const
{
    if (m_databaseManager == 0)
    {
        return 0;
    }

    const std::vector<Grade> &grades = m_databaseManager->getGrades();
    int i;
    for (i = 0; i < grades.size(); i++)
    {
        if (grades[i].getEnrollmentId() == enrollmentId)
        {
            return grades[i].getValue();
        }
    }
    return 0;
}

double GradeController::getAverageForStudent(int studentId) const
{
    if (m_databaseManager == 0)
    {
        return 0.0;
    }
    return m_databaseManager->getAverageGradeForStudent(studentId);
}

UserController::UserController(DatabaseManager *databaseManager)
    : m_databaseManager(databaseManager)
{
}

bool UserController::removeUser(int userId) const
{
    if (m_databaseManager == 0)
    {
        return false;
    }
    return m_databaseManager->removeUser(userId);
}

std::vector<User *> UserController::getAllUsers() const
{
    if (m_databaseManager == 0)
    {
        return std::vector<User *>();
    }
    return m_databaseManager->getUsers();
}

std::vector<User *> UserController::getTeachers() const
{
    std::vector<User *> result;
    if (m_databaseManager == 0)
    {
        return result;
    }

    const std::vector<User *> &users = m_databaseManager->getUsers();
    int i;
    for (i = 0; i < users.size(); i++)
    {
        if (users[i]->getRole() == RoleTeacher)
        {
            result.push_back(users[i]);
        }
    }
    return result;
}

std::vector<User *> UserController::getStudents() const
{
    std::vector<User *> result;
    if (m_databaseManager == 0)
    {
        return result;
    }

    const std::vector<User *> &users = m_databaseManager->getUsers();
    int i;
    for (i = 0; i < users.size(); i++)
    {
        if (users[i]->getRole() == RoleStudent)
        {
            result.push_back(users[i]);
        }
    }
    return result;
}

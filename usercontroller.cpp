#include "usercontroller.h"

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

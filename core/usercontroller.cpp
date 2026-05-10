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

QList<User *> UserController::getAllUsers() const
{
    if (m_databaseManager == 0)
    {
        return QList<User *>();
    }
    return m_databaseManager->getUsers();
}

QList<User *> UserController::getTeachers() const
{
    QList<User *> result;
    if (m_databaseManager == 0)
    {
        return result;
    }

    QList<User *> users = m_databaseManager->getUsers();
    int i;
    for (i = 0; i < users.size(); i++)
    {
        if (users[i]->getRole() == RoleTeacher)
        {
            result.append(users[i]);
        }
    }
    return result;
}

QList<User *> UserController::getStudents() const
{
    QList<User *> result;
    if (m_databaseManager == 0)
    {
        return result;
    }

    QList<User *> users = m_databaseManager->getUsers();
    int i;
    for (i = 0; i < users.size(); i++)
    {
        if (users[i]->getRole() == RoleStudent)
        {
            result.append(users[i]);
        }
    }
    return result;
}

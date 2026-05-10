#include "authcontroller.h"

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

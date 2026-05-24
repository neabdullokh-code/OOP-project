#ifndef AUTHCONTROLLER_H
#define AUTHCONTROLLER_H

#include <QString>
#include "databasemanager.h"

class AuthController
{
public:
    AuthController(DatabaseManager *databaseManager);

    User *login(const QString &login, const QString &password) const;
    bool registerUser(const QString &fullName, const QString &login, const QString &password, const QString &roleName) const;

private:
    DatabaseManager *m_databaseManager;
};

#endif

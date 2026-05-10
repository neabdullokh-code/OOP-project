#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include "databasemanager.h"

class UserController
{
public:
    UserController(DatabaseManager *databaseManager);

    bool removeUser(int userId) const;
    QList<User *> getAllUsers() const;
    QList<User *> getTeachers() const;
    QList<User *> getStudents() const;

private:
    DatabaseManager *m_databaseManager;
};

#endif

#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include <vector>
#include "databasemanager.h"

class UserController
{
public:
    UserController(DatabaseManager *databaseManager);

    bool removeUser(int userId) const;
    std::vector<User *> getAllUsers() const;
    std::vector<User *> getTeachers() const;
    std::vector<User *> getStudents() const;

private:
    DatabaseManager *m_databaseManager;
};

#endif

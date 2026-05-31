#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include "../models/user.h"
#include <QList>
#include <QString>

class UserController {
public:
  UserController();

  // CRUD операции
  QList<User> getAllUsers();
  QList<User> getUsersByRole(const QString &role);
  User getUserById(int id);
  bool addUser(const QString &name, const QString &login,
               const QString &password, const QString &role);
  bool updateUser(int id, const QString &name, const QString &login,
                  const QString &password, const QString &role);
  bool deleteUser(int id);

  // Статистика
  int getTotalUsers();
  int getStudentCount();
  int getTeacherCount();
};

#endif // USERCONTROLLER_H

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
  void addUser(const QString &name, const QString &login,
               const QString &password, const QString &role);
  void updateUser(int id, const QString &name, const QString &login,
                  const QString &password, const QString &role);
  void deleteUser(int id);

  // Статистика
  int getTotalUsers();
  int getStudentCount();
  int getTeacherCount();
};

#endif // USERCONTROLLER_H

#include "usercontroller.h"
#include "../database/databasemanager.h"

UserController::UserController() {}

QList<User> UserController::getAllUsers() {
  return DatabaseManager::instance()->getAllUsers();
}

QList<User> UserController::getUsersByRole(const QString &role) {
  QList<User> result;
  QList<User> all = getAllUsers();
  for (const User &user : all) {
    if (user.getRole() == role) {
      result.append(user);
    }
  }
  return result;
}

User UserController::getUserById(int id) {
  return DatabaseManager::instance()->getUserById(id);
}

bool UserController::addUser(const QString &name, const QString &login,
                             const QString &password, const QString &role) {
  if (DatabaseManager::instance()->getUserByLogin(login).getId() != 0)
    return false;
  int newId = DatabaseManager::instance()->getNextUserId();
  User user(newId, name, login, password, role);
  DatabaseManager::instance()->addUser(user);
  return true;
}

bool UserController::updateUser(int id, const QString &name,
                                const QString &login, const QString &password,
                                const QString &role) {
  User withSameLogin = DatabaseManager::instance()->getUserByLogin(login);
  if (withSameLogin.getId() != 0 && withSameLogin.getId() != id)
    return false;
  User user(id, name, login, password, role);
  DatabaseManager::instance()->updateUser(user);
  return true;
}

bool UserController::deleteUser(int id) {
  User u = getUserById(id);
  if (u.getRole() == "teacher" &&
      !DatabaseManager::instance()->getCoursesByTeacherId(id).isEmpty())
    return false;
  DatabaseManager::instance()->deleteGradesByStudentId(id);
  DatabaseManager::instance()->deleteEnrollmentsByStudentId(id);
  DatabaseManager::instance()->deleteUser(id);
  return true;
}

int UserController::getTotalUsers() { return getAllUsers().size(); }

int UserController::getStudentCount() {
  return getUsersByRole("student").size();
}

int UserController::getTeacherCount() {
  return getUsersByRole("teacher").size();
}

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

void UserController::addUser(const QString &name, const QString &login,
                             const QString &password, const QString &role) {
  int newId = DatabaseManager::instance()->getNextUserId();
  User user(newId, name, login, password, role);
  DatabaseManager::instance()->addUser(user);
}

void UserController::updateUser(int id, const QString &name,
                                const QString &login, const QString &password,
                                const QString &role) {
  User user(id, name, login, password, role);
  DatabaseManager::instance()->updateUser(user);
}

void UserController::deleteUser(int id) {
  // Удаляем также связанные оценки и записи на курсы
  DatabaseManager::instance()->deleteGradesByStudentId(id);
  DatabaseManager::instance()->deleteEnrollmentsByStudentId(id);
  DatabaseManager::instance()->deleteUser(id);
}

int UserController::getTotalUsers() { return getAllUsers().size(); }

int UserController::getStudentCount() {
  return getUsersByRole("student").size();
}

int UserController::getTeacherCount() {
  return getUsersByRole("teacher").size();
}

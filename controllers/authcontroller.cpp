#include "authcontroller.h"
#include "../database/databasemanager.h"

AuthController::AuthController() : m_isAuthenticated(false) {}

bool AuthController::authenticate(const QString &login,
                                  const QString &password) {
  // Получаем пользователя по логину из базы
  User user = DatabaseManager::instance()->getUserByLogin(login);

  // Проверяем что пользователь найден (id != 0) и пароль совпадает
  if (user.getId() != 0 && user.getPassword() == password) {
    m_currentUser = user;
    m_isAuthenticated = true;
    return true;
  }

  m_isAuthenticated = false;
  return false;
}

User AuthController::getCurrentUser() const { return m_currentUser; }

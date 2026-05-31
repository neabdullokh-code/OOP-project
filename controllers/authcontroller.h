#ifndef AUTHCONTROLLER_H
#define AUTHCONTROLLER_H

#include "../models/user.h"
#include <QString>

class AuthController {
public:
  AuthController();

  // Проверить логин и пароль. Возвращает true если успешно
  bool authenticate(const QString &login, const QString &password);

  // Получить текущего пользователя (после успешной авторизации)
  User getCurrentUser() const;

private:
  User m_currentUser;
  bool m_isAuthenticated;
};

#endif // AUTHCONTROLLER_H

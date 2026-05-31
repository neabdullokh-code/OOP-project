#include "user.h"

// ==================== User (базовый класс) ====================

User::User() : m_id(0) {}

User::User(int id, const QString &name, const QString &login,
           const QString &password, const QString &role)
    : m_id(id), m_name(name), m_login(login), m_password(password),
      m_role(role) {}

int User::getId() const { return m_id; }
QString User::getName() const { return m_name; }
QString User::getLogin() const { return m_login; }
QString User::getPassword() const { return m_password; }
QString User::getRole() const { return m_role; }

void User::setId(int id) { m_id = id; }
void User::setName(const QString &name) { m_name = name; }
void User::setLogin(const QString &login) { m_login = login; }
void User::setPassword(const QString &password) { m_password = password; }
void User::setRole(const QString &role) { m_role = role; }

QString User::getDashboardTitle() const { return "User dashboard"; }

User User::fromJson(const QJsonObject &json) {
  User user;
  user.m_id = json["id"].toInt();
  user.m_name = json["name"].toString();
  user.m_login = json["login"].toString();
  user.m_password = json["password"].toString();
  user.m_role = json["role"].toString();
  return user;
}

QJsonObject User::toJson() const {
  QJsonObject json;
  json["id"] = m_id;
  json["name"] = m_name;
  json["login"] = m_login;
  json["password"] = m_password;
  json["role"] = m_role;
  return json;
}

// ==================== Admin ====================

Admin::Admin() { setRole("admin"); }

Admin::Admin(int id, const QString &name, const QString &login,
             const QString &password)
    : User(id, name, login, password, "admin") {}

QString Admin::getDashboardTitle() const { return "Administrator dashboard"; }

// ==================== Teacher ====================

Teacher::Teacher() { setRole("teacher"); }

Teacher::Teacher(int id, const QString &name, const QString &login,
                 const QString &password)
    : User(id, name, login, password, "teacher") {}

QString Teacher::getDashboardTitle() const { return "Teacher dashboard"; }

// ==================== Student ====================

Student::Student() { setRole("student"); }

Student::Student(int id, const QString &name, const QString &login,
                 const QString &password)
    : User(id, name, login, password, "student") {}

QString Student::getDashboardTitle() const { return "Student dashboard"; }

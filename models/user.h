#ifndef USER_H
#define USER_H

#include <QString>
#include <QJsonObject>

// Базовый класс пользователя (демонстрирует Инкапсуляцию и Абстракцию)
class User {
public:
    User();
    User(int id, const QString& name, const QString& login,
         const QString& password, const QString& role);
    virtual ~User() = default;

    // --- Геттеры ---
    int getId() const;
    QString getName() const;
    QString getLogin() const;
    QString getPassword() const;
    QString getRole() const;

    // --- Сеттеры ---
    void setId(int id);
    void setName(const QString& name);
    void setLogin(const QString& login);
    void setPassword(const QString& password);
    void setRole(const QString& role);

    // --- Полиморфизм: виртуальные методы ---
    virtual QString getDashboardTitle() const;

    // --- Сериализация JSON ---
    static User fromJson(const QJsonObject& json);
    QJsonObject toJson() const;

private:
    int m_id;
    QString m_name;
    QString m_login;
    QString m_password;
    QString m_role; // "admin", "teacher", "student"
};

// --- Наследование: дочерние классы ---

class Admin : public User {
public:
    Admin();
    Admin(int id, const QString& name, const QString& login, const QString& password);
    QString getDashboardTitle() const override;
};

class Teacher : public User {
public:
    Teacher();
    Teacher(int id, const QString& name, const QString& login, const QString& password);
    QString getDashboardTitle() const override;
};

class Student : public User {
public:
    Student();
    Student(int id, const QString& name, const QString& login, const QString& password);
    QString getDashboardTitle() const override;
};

#endif // USER_H

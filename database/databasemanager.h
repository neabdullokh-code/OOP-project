#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QList>
#include <QString>

#include "../models/course.h"
#include "../models/enrollment.h"
#include "../models/grade.h"
#include "../models/user.h"

// Singleton — единственный экземпляр для работы с файлами
class DatabaseManager {
public:
  // Получить единственный экземпляр (паттерн Singleton)
  static DatabaseManager *instance();

  // --- Пользователи ---
  QList<User> getAllUsers();
  User getUserById(int id);
  User getUserByLogin(const QString &login);
  void addUser(const User &user);
  void updateUser(const User &user);
  void deleteUser(int id);
  int getNextUserId();

  // --- Курсы ---
  QList<Course> getAllCourses();
  Course getCourseById(int id);
  QList<Course> getCoursesByTeacherId(int teacherId);
  void addCourse(const Course &course);
  void updateCourse(const Course &course);
  void deleteCourse(int id);
  int getNextCourseId();

  // --- Оценки ---
  QList<Grade> getAllGrades();
  QList<Grade> getGradesByStudentId(int studentId);
  QList<Grade> getGradesByCourseId(int courseId);
  Grade getGrade(int studentId, int courseId);
  void addGrade(const Grade &grade);
  void updateGrade(const Grade &grade);
  void deleteGradesByStudentId(int studentId);
  void deleteGradesByCourseId(int courseId);
  int getNextGradeId();

  // --- Записи на курсы ---
  QList<Enrollment> getAllEnrollments();
  QList<Enrollment> getEnrollmentsByStudentId(int studentId);
  QList<Enrollment> getEnrollmentsByCourseId(int courseId);
  bool enrollmentExists(int studentId, int courseId);
  void addEnrollment(const Enrollment &enrollment);
  void deleteEnrollment(int id);
  void deleteEnrollmentsByStudentId(int studentId);
  void deleteEnrollmentsByCourseId(int courseId);
  int getNextEnrollmentId();

private:
  // Конструктор закрыт — нельзя создать извне (Singleton)
  DatabaseManager();
  static DatabaseManager *m_instance;

  // Путь к папке с данными
  QString m_dataPath;

  // Вспомогательные методы для чтения/записи JSON
  QJsonArray readJsonFile(const QString &filename);
  void writeJsonFile(const QString &filename, const QJsonArray &array);
};

#endif // DATABASEMANAGER_H

#include "databasemanager.h"
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFile>

// Инициализация статического указателя (Singleton)
DatabaseManager *DatabaseManager::m_instance = nullptr;

DatabaseManager::DatabaseManager() {
  // Определяем путь к папке data/ рядом с исполняемым файлом
  m_dataPath = QCoreApplication::applicationDirPath() + "/data/";

  // Создаём папку если не существует
  QDir dir(m_dataPath);
  if (!dir.exists()) {
    dir.mkpath(".");
  }

  // Если файлов данных нет — копируем начальные из ресурсов или создаём пустые
  QStringList files = {"users.json", "courses.json", "grades.json",
                       "enrollments.json"};
  for (const QString &file : files) {
    if (!QFile::exists(m_dataPath + file)) {
      // Пробуем скопировать из исходной папки data/
      QString sourcePath = QCoreApplication::applicationDirPath();
      // Ищем data/ папку в нескольких местах
      QStringList searchPaths = {
          sourcePath + "/../../../data/", // macOS .app bundle
          sourcePath + "/../../data/",    // обычная сборка
          sourcePath + "/../data/", sourcePath + "/data/"};

      bool copied = false;
      for (const QString &sp : searchPaths) {
        if (QFile::exists(sp + file)) {
          QFile::copy(sp + file, m_dataPath + file);
          // Устанавливаем права на запись (copy делает read-only)
          QFile(m_dataPath + file)
              .setPermissions(QFile::ReadOwner | QFile::WriteOwner |
                              QFile::ReadGroup | QFile::ReadOther);
          copied = true;
          break;
        }
      }

      if (!copied) {
        // Создаём пустой JSON-массив
        writeJsonFile(file, QJsonArray());
      }
    }
  }
}

DatabaseManager *DatabaseManager::instance() {
  if (!m_instance) {
    m_instance = new DatabaseManager();
  }
  return m_instance;
}

// ==================== Вспомогательные методы ====================

QJsonArray DatabaseManager::readJsonFile(const QString &filename) {
  QFile file(m_dataPath + filename);
  if (!file.open(QIODevice::ReadOnly)) {
    qWarning() << "Не удалось открыть файл:" << filename;
    return QJsonArray();
  }

  QByteArray data = file.readAll();
  file.close();

  QJsonDocument doc = QJsonDocument::fromJson(data);
  if (doc.isNull() || !doc.isArray()) {
    qWarning() << "Ошибка парсинга JSON:" << filename;
    return QJsonArray();
  }

  return doc.array();
}

void DatabaseManager::writeJsonFile(const QString &filename,
                                    const QJsonArray &array) {
  QFile file(m_dataPath + filename);
  if (!file.open(QIODevice::WriteOnly)) {
    qWarning() << "Не удалось записать файл:" << filename;
    return;
  }

  QJsonDocument doc(array);
  file.write(doc.toJson(QJsonDocument::Indented));
  file.close();
}

// ==================== Пользователи ====================

QList<User> DatabaseManager::getAllUsers() {
  QList<User> users;
  QJsonArray array = readJsonFile("users.json");
  for (const QJsonValue &val : array) {
    users.append(User::fromJson(val.toObject()));
  }
  return users;
}

User DatabaseManager::getUserById(int id) {
  QList<User> users = getAllUsers();
  for (const User &user : users) {
    if (user.getId() == id)
      return user;
  }
  return User();
}

User DatabaseManager::getUserByLogin(const QString &login) {
  QList<User> users = getAllUsers();
  for (const User &user : users) {
    if (user.getLogin() == login)
      return user;
  }
  return User();
}

void DatabaseManager::addUser(const User &user) {
  QJsonArray array = readJsonFile("users.json");
  array.append(user.toJson());
  writeJsonFile("users.json", array);
}

void DatabaseManager::updateUser(const User &user) {
  QJsonArray array = readJsonFile("users.json");
  for (int i = 0; i < array.size(); ++i) {
    if (array[i].toObject()["id"].toInt() == user.getId()) {
      array[i] = user.toJson();
      break;
    }
  }
  writeJsonFile("users.json", array);
}

void DatabaseManager::deleteUser(int id) {
  QJsonArray array = readJsonFile("users.json");
  for (int i = 0; i < array.size(); ++i) {
    if (array[i].toObject()["id"].toInt() == id) {
      array.removeAt(i);
      break;
    }
  }
  writeJsonFile("users.json", array);
}

int DatabaseManager::getNextUserId() {
  QList<User> users = getAllUsers();
  int maxId = 0;
  for (const User &u : users) {
    if (u.getId() > maxId)
      maxId = u.getId();
  }
  return maxId + 1;
}

// ==================== Курсы ====================

QList<Course> DatabaseManager::getAllCourses() {
  QList<Course> courses;
  QJsonArray array = readJsonFile("courses.json");
  for (const QJsonValue &val : array) {
    courses.append(Course::fromJson(val.toObject()));
  }
  return courses;
}

Course DatabaseManager::getCourseById(int id) {
  QList<Course> courses = getAllCourses();
  for (const Course &course : courses) {
    if (course.getId() == id)
      return course;
  }
  return Course();
}

QList<Course> DatabaseManager::getCoursesByTeacherId(int teacherId) {
  QList<Course> result;
  QList<Course> courses = getAllCourses();
  for (const Course &course : courses) {
    if (course.getTeacherId() == teacherId)
      result.append(course);
  }
  return result;
}

void DatabaseManager::addCourse(const Course &course) {
  QJsonArray array = readJsonFile("courses.json");
  array.append(course.toJson());
  writeJsonFile("courses.json", array);
}

void DatabaseManager::updateCourse(const Course &course) {
  QJsonArray array = readJsonFile("courses.json");
  for (int i = 0; i < array.size(); ++i) {
    if (array[i].toObject()["id"].toInt() == course.getId()) {
      array[i] = course.toJson();
      break;
    }
  }
  writeJsonFile("courses.json", array);
}

void DatabaseManager::deleteCourse(int id) {
  QJsonArray array = readJsonFile("courses.json");
  for (int i = 0; i < array.size(); ++i) {
    if (array[i].toObject()["id"].toInt() == id) {
      array.removeAt(i);
      break;
    }
  }
  writeJsonFile("courses.json", array);
}

int DatabaseManager::getNextCourseId() {
  QList<Course> courses = getAllCourses();
  int maxId = 0;
  for (const Course &c : courses) {
    if (c.getId() > maxId)
      maxId = c.getId();
  }
  return maxId + 1;
}

// ==================== Оценки ====================

QList<Grade> DatabaseManager::getAllGrades() {
  QList<Grade> grades;
  QJsonArray array = readJsonFile("grades.json");
  for (const QJsonValue &val : array) {
    grades.append(Grade::fromJson(val.toObject()));
  }
  return grades;
}

QList<Grade> DatabaseManager::getGradesByStudentId(int studentId) {
  QList<Grade> result;
  QList<Grade> grades = getAllGrades();
  for (const Grade &grade : grades) {
    if (grade.getStudentId() == studentId)
      result.append(grade);
  }
  return result;
}

QList<Grade> DatabaseManager::getGradesByCourseId(int courseId) {
  QList<Grade> result;
  QList<Grade> grades = getAllGrades();
  for (const Grade &grade : grades) {
    if (grade.getCourseId() == courseId)
      result.append(grade);
  }
  return result;
}

Grade DatabaseManager::getGrade(int studentId, int courseId) {
  QList<Grade> grades = getAllGrades();
  for (const Grade &grade : grades) {
    if (grade.getStudentId() == studentId && grade.getCourseId() == courseId)
      return grade;
  }
  return Grade();
}

void DatabaseManager::addGrade(const Grade &grade) {
  QJsonArray array = readJsonFile("grades.json");
  array.append(grade.toJson());
  writeJsonFile("grades.json", array);
}

void DatabaseManager::updateGrade(const Grade &grade) {
  QJsonArray array = readJsonFile("grades.json");
  for (int i = 0; i < array.size(); ++i) {
    if (array[i].toObject()["id"].toInt() == grade.getId()) {
      array[i] = grade.toJson();
      break;
    }
  }
  writeJsonFile("grades.json", array);
}

void DatabaseManager::deleteGradesByStudentId(int studentId) {
  QJsonArray array = readJsonFile("grades.json");
  for (int i = array.size() - 1; i >= 0; --i) {
    if (array[i].toObject()["studentId"].toInt() == studentId) {
      array.removeAt(i);
    }
  }
  writeJsonFile("grades.json", array);
}

void DatabaseManager::deleteGradesByCourseId(int courseId) {
  QJsonArray array = readJsonFile("grades.json");
  for (int i = array.size() - 1; i >= 0; --i) {
    if (array[i].toObject()["courseId"].toInt() == courseId) {
      array.removeAt(i);
    }
  }
  writeJsonFile("grades.json", array);
}

int DatabaseManager::getNextGradeId() {
  QList<Grade> grades = getAllGrades();
  int maxId = 0;
  for (const Grade &g : grades) {
    if (g.getId() > maxId)
      maxId = g.getId();
  }
  return maxId + 1;
}

// ==================== Записи на курсы ====================

QList<Enrollment> DatabaseManager::getAllEnrollments() {
  QList<Enrollment> enrollments;
  QJsonArray array = readJsonFile("enrollments.json");
  for (const QJsonValue &val : array) {
    enrollments.append(Enrollment::fromJson(val.toObject()));
  }
  return enrollments;
}

QList<Enrollment> DatabaseManager::getEnrollmentsByStudentId(int studentId) {
  QList<Enrollment> result;
  QList<Enrollment> enrollments = getAllEnrollments();
  for (const Enrollment &e : enrollments) {
    if (e.getStudentId() == studentId)
      result.append(e);
  }
  return result;
}

QList<Enrollment> DatabaseManager::getEnrollmentsByCourseId(int courseId) {
  QList<Enrollment> result;
  QList<Enrollment> enrollments = getAllEnrollments();
  for (const Enrollment &e : enrollments) {
    if (e.getCourseId() == courseId)
      result.append(e);
  }
  return result;
}

void DatabaseManager::addEnrollment(const Enrollment &enrollment) {
  QJsonArray array = readJsonFile("enrollments.json");
  array.append(enrollment.toJson());
  writeJsonFile("enrollments.json", array);
}

void DatabaseManager::deleteEnrollment(int id) {
  QJsonArray array = readJsonFile("enrollments.json");
  for (int i = 0; i < array.size(); ++i) {
    if (array[i].toObject()["id"].toInt() == id) {
      array.removeAt(i);
      break;
    }
  }
  writeJsonFile("enrollments.json", array);
}

void DatabaseManager::deleteEnrollmentsByStudentId(int studentId) {
  QJsonArray array = readJsonFile("enrollments.json");
  for (int i = array.size() - 1; i >= 0; --i) {
    if (array[i].toObject()["studentId"].toInt() == studentId) {
      array.removeAt(i);
    }
  }
  writeJsonFile("enrollments.json", array);
}

void DatabaseManager::deleteEnrollmentsByCourseId(int courseId) {
  QJsonArray array = readJsonFile("enrollments.json");
  for (int i = array.size() - 1; i >= 0; --i) {
    if (array[i].toObject()["courseId"].toInt() == courseId) {
      array.removeAt(i);
    }
  }
  writeJsonFile("enrollments.json", array);
}

int DatabaseManager::getNextEnrollmentId() {
  QList<Enrollment> enrollments = getAllEnrollments();
  int maxId = 0;
  for (const Enrollment &e : enrollments) {
    if (e.getId() > maxId)
      maxId = e.getId();
  }
  return maxId + 1;
}

#include "gradecontroller.h"
#include "../database/databasemanager.h"
#include <QDate>

GradeController::GradeController() {}

QList<Grade> GradeController::getGradesByStudentId(int studentId) {
  return DatabaseManager::instance()->getGradesByStudentId(studentId);
}

QList<Grade> GradeController::getGradesByCourseId(int courseId) {
  return DatabaseManager::instance()->getGradesByCourseId(courseId);
}

Grade GradeController::getGrade(int studentId, int courseId) {
  return DatabaseManager::instance()->getGrade(studentId, courseId);
}

void GradeController::setGrade(int studentId, int courseId, int value,
                               const QString &date) {
  // Проверяем — есть ли уже оценка
  Grade existing = DatabaseManager::instance()->getGrade(studentId, courseId);
  QString gradeDate =
      date.isEmpty() ? QDate::currentDate().toString("yyyy-MM-dd") : date;

  if (existing.getId() != 0) {
    // Обновляем существующую оценку
    existing.setValue(value);
    existing.setDate(gradeDate);
    DatabaseManager::instance()->updateGrade(existing);
  } else {
    // Создаём новую оценку
    int newId = DatabaseManager::instance()->getNextGradeId();
    Grade grade(newId, studentId, courseId, value, gradeDate);
    DatabaseManager::instance()->addGrade(grade);
  }
}

double GradeController::getAverageGradeForStudent(int studentId) {
  QList<Grade> grades = getGradesByStudentId(studentId);
  if (grades.isEmpty())
    return 0.0;

  double sum = 0;
  for (const Grade &g : grades) {
    sum += g.getValue();
  }
  return sum / grades.size();
}

double GradeController::getAverageGradeForCourse(int courseId) {
  QList<Grade> grades = getGradesByCourseId(courseId);
  if (grades.isEmpty())
    return 0.0;

  double sum = 0;
  for (const Grade &g : grades) {
    sum += g.getValue();
  }
  return sum / grades.size();
}

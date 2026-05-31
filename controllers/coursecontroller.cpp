#include "coursecontroller.h"
#include "../database/databasemanager.h"
#include <QDate>

CourseController::CourseController() {}

QList<Course> CourseController::getAllCourses() {
  return DatabaseManager::instance()->getAllCourses();
}

QList<Course> CourseController::getCoursesByTeacherId(int teacherId) {
  return DatabaseManager::instance()->getCoursesByTeacherId(teacherId);
}

Course CourseController::getCourseById(int id) {
  return DatabaseManager::instance()->getCourseById(id);
}

bool CourseController::addCourse(const QString &name,
                                 const QString &description, int teacherId) {
  if (teacherId <= 0)
    return false;
  int newId = DatabaseManager::instance()->getNextCourseId();
  Course course(newId, name, description, teacherId);
  DatabaseManager::instance()->addCourse(course);
  return true;
}

bool CourseController::updateCourse(int id, const QString &name,
                                    const QString &description, int teacherId) {
  if (teacherId <= 0)
    return false;
  Course course(id, name, description, teacherId);
  DatabaseManager::instance()->updateCourse(course);
  return true;
}

void CourseController::deleteCourse(int id) {
  // Удаляем связанные оценки и записи
  DatabaseManager::instance()->deleteGradesByCourseId(id);
  DatabaseManager::instance()->deleteEnrollmentsByCourseId(id);
  DatabaseManager::instance()->deleteCourse(id);
}

bool CourseController::enrollStudent(int studentId, int courseId,
                                     const QString &date) {
  if (DatabaseManager::instance()->enrollmentExists(studentId, courseId))
    return false;
  int newId = DatabaseManager::instance()->getNextEnrollmentId();
  QString enrollDate =
      date.isEmpty() ? QDate::currentDate().toString("yyyy-MM-dd") : date;
  Enrollment enrollment(newId, studentId, courseId, enrollDate);
  DatabaseManager::instance()->addEnrollment(enrollment);
  return true;
}

void CourseController::unenrollStudent(int enrollmentId) {
  DatabaseManager::instance()->deleteEnrollment(enrollmentId);
}

QList<Enrollment> CourseController::getEnrollmentsByCourseId(int courseId) {
  return DatabaseManager::instance()->getEnrollmentsByCourseId(courseId);
}

QList<Enrollment> CourseController::getEnrollmentsByStudentId(int studentId) {
  return DatabaseManager::instance()->getEnrollmentsByStudentId(studentId);
}

int CourseController::getStudentCountForCourse(int courseId) {
  return getEnrollmentsByCourseId(courseId).size();
}

int CourseController::getTotalCourses() { return getAllCourses().size(); }

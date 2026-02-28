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

void CourseController::addCourse(const QString &name,
                                 const QString &description, int teacherId) {
  int newId = DatabaseManager::instance()->getNextCourseId();
  Course course(newId, name, description, teacherId);
  DatabaseManager::instance()->addCourse(course);
}

void CourseController::updateCourse(int id, const QString &name,
                                    const QString &description, int teacherId) {
  Course course(id, name, description, teacherId);
  DatabaseManager::instance()->updateCourse(course);
}

void CourseController::deleteCourse(int id) {
  // Удаляем связанные оценки и записи
  DatabaseManager::instance()->deleteGradesByCourseId(id);
  DatabaseManager::instance()->deleteEnrollmentsByCourseId(id);
  DatabaseManager::instance()->deleteCourse(id);
}

void CourseController::enrollStudent(int studentId, int courseId,
                                     const QString &date) {
  int newId = DatabaseManager::instance()->getNextEnrollmentId();
  QString enrollDate =
      date.isEmpty() ? QDate::currentDate().toString("yyyy-MM-dd") : date;
  Enrollment enrollment(newId, studentId, courseId, enrollDate);
  DatabaseManager::instance()->addEnrollment(enrollment);
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

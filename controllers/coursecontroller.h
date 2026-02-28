#ifndef COURSECONTROLLER_H
#define COURSECONTROLLER_H

#include "../models/course.h"
#include "../models/enrollment.h"
#include <QList>
#include <QString>

class CourseController {
public:
  CourseController();

  // CRUD
  QList<Course> getAllCourses();
  QList<Course> getCoursesByTeacherId(int teacherId);
  Course getCourseById(int id);
  void addCourse(const QString &name, const QString &description,
                 int teacherId);
  void updateCourse(int id, const QString &name, const QString &description,
                    int teacherId);
  void deleteCourse(int id);

  // Записи
  void enrollStudent(int studentId, int courseId, const QString &date);
  void unenrollStudent(int enrollmentId);
  QList<Enrollment> getEnrollmentsByCourseId(int courseId);
  QList<Enrollment> getEnrollmentsByStudentId(int studentId);
  int getStudentCountForCourse(int courseId);

  // Статистика
  int getTotalCourses();
};

#endif // COURSECONTROLLER_H

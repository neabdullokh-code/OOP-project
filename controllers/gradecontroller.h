#ifndef GRADECONTROLLER_H
#define GRADECONTROLLER_H

#include "../models/grade.h"
#include <QList>
#include <QString>

class GradeController {
public:
  GradeController();

  // CRUD
  QList<Grade> getGradesByStudentId(int studentId);
  QList<Grade> getGradesByCourseId(int courseId);
  Grade getGrade(int studentId, int courseId);
  void setGrade(int studentId, int courseId, int value, const QString &date);

  // Статистика
  double getAverageGradeForStudent(int studentId);
  double getAverageGradeForCourse(int courseId);
};

#endif // GRADECONTROLLER_H

#ifndef ENROLLMENT_H
#define ENROLLMENT_H

#include <QJsonObject>
#include <QString>

class Enrollment {
public:
  Enrollment();
  Enrollment(int id, int studentId, int courseId, const QString &enrolledDate);

  // Геттеры
  int getId() const;
  int getStudentId() const;
  int getCourseId() const;
  QString getEnrolledDate() const;

  // Сеттеры
  void setId(int id);
  void setStudentId(int studentId);
  void setCourseId(int courseId);
  void setEnrolledDate(const QString &enrolledDate);

  // JSON
  static Enrollment fromJson(const QJsonObject &json);
  QJsonObject toJson() const;

private:
  int m_id;
  int m_studentId;
  int m_courseId;
  QString m_enrolledDate;
};

#endif // ENROLLMENT_H

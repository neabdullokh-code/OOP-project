#include "enrollment.h"

Enrollment::Enrollment() : m_id(0), m_studentId(0), m_courseId(0) {}

Enrollment::Enrollment(int id, int studentId, int courseId,
                       const QString &enrolledDate)
    : m_id(id), m_studentId(studentId), m_courseId(courseId),
      m_enrolledDate(enrolledDate) {}

int Enrollment::getId() const { return m_id; }
int Enrollment::getStudentId() const { return m_studentId; }
int Enrollment::getCourseId() const { return m_courseId; }
QString Enrollment::getEnrolledDate() const { return m_enrolledDate; }

void Enrollment::setId(int id) { m_id = id; }
void Enrollment::setStudentId(int studentId) { m_studentId = studentId; }
void Enrollment::setCourseId(int courseId) { m_courseId = courseId; }
void Enrollment::setEnrolledDate(const QString &enrolledDate) {
  m_enrolledDate = enrolledDate;
}

Enrollment Enrollment::fromJson(const QJsonObject &json) {
  Enrollment enrollment;
  enrollment.m_id = json["id"].toInt();
  enrollment.m_studentId = json["studentId"].toInt();
  enrollment.m_courseId = json["courseId"].toInt();
  enrollment.m_enrolledDate = json["enrolledDate"].toString();
  return enrollment;
}

QJsonObject Enrollment::toJson() const {
  QJsonObject json;
  json["id"] = m_id;
  json["studentId"] = m_studentId;
  json["courseId"] = m_courseId;
  json["enrolledDate"] = m_enrolledDate;
  return json;
}

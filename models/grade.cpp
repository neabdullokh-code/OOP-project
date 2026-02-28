#include "grade.h"

Grade::Grade() : m_id(0), m_studentId(0), m_courseId(0), m_value(0) {}

Grade::Grade(int id, int studentId, int courseId, int value,
             const QString &date)
    : m_id(id), m_studentId(studentId), m_courseId(courseId), m_value(value),
      m_date(date) {}

int Grade::getId() const { return m_id; }
int Grade::getStudentId() const { return m_studentId; }
int Grade::getCourseId() const { return m_courseId; }
int Grade::getValue() const { return m_value; }
QString Grade::getDate() const { return m_date; }

void Grade::setId(int id) { m_id = id; }
void Grade::setStudentId(int studentId) { m_studentId = studentId; }
void Grade::setCourseId(int courseId) { m_courseId = courseId; }
void Grade::setValue(int value) { m_value = value; }
void Grade::setDate(const QString &date) { m_date = date; }

Grade Grade::fromJson(const QJsonObject &json) {
  Grade grade;
  grade.m_id = json["id"].toInt();
  grade.m_studentId = json["studentId"].toInt();
  grade.m_courseId = json["courseId"].toInt();
  grade.m_value = json["value"].toInt();
  grade.m_date = json["date"].toString();
  return grade;
}

QJsonObject Grade::toJson() const {
  QJsonObject json;
  json["id"] = m_id;
  json["studentId"] = m_studentId;
  json["courseId"] = m_courseId;
  json["value"] = m_value;
  json["date"] = m_date;
  return json;
}

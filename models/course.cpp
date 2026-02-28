#include "course.h"

Course::Course() : m_id(0), m_teacherId(0) {}

Course::Course(int id, const QString &name, const QString &description,
               int teacherId)
    : m_id(id), m_name(name), m_description(description),
      m_teacherId(teacherId) {}

int Course::getId() const { return m_id; }
QString Course::getName() const { return m_name; }
QString Course::getDescription() const { return m_description; }
int Course::getTeacherId() const { return m_teacherId; }

void Course::setId(int id) { m_id = id; }
void Course::setName(const QString &name) { m_name = name; }
void Course::setDescription(const QString &description) {
  m_description = description;
}
void Course::setTeacherId(int teacherId) { m_teacherId = teacherId; }

Course Course::fromJson(const QJsonObject &json) {
  Course course;
  course.m_id = json["id"].toInt();
  course.m_name = json["name"].toString();
  course.m_description = json["description"].toString();
  course.m_teacherId = json["teacherId"].toInt();
  return course;
}

QJsonObject Course::toJson() const {
  QJsonObject json;
  json["id"] = m_id;
  json["name"] = m_name;
  json["description"] = m_description;
  json["teacherId"] = m_teacherId;
  return json;
}

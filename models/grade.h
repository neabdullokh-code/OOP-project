#ifndef GRADE_H
#define GRADE_H

#include <QJsonObject>
#include <QString>

class Grade {
public:
  Grade();
  Grade(int id, int studentId, int courseId, int value, const QString &date);

  // Геттеры
  int getId() const;
  int getStudentId() const;
  int getCourseId() const;
  int getValue() const;
  QString getDate() const;

  // Сеттеры
  void setId(int id);
  void setStudentId(int studentId);
  void setCourseId(int courseId);
  void setValue(int value);
  void setDate(const QString &date);

  // JSON
  static Grade fromJson(const QJsonObject &json);
  QJsonObject toJson() const;

private:
  int m_id;
  int m_studentId;
  int m_courseId;
  int m_value;
  QString m_date;
};

#endif // GRADE_H

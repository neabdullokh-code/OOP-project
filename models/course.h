#ifndef COURSE_H
#define COURSE_H

#include <QJsonObject>
#include <QString>

class Course {
public:
  Course();
  Course(int id, const QString &name, const QString &description,
         int teacherId);

  // Геттеры
  int getId() const;
  QString getName() const;
  QString getDescription() const;
  int getTeacherId() const;

  // Сеттеры
  void setId(int id);
  void setName(const QString &name);
  void setDescription(const QString &description);
  void setTeacherId(int teacherId);

  // JSON
  static Course fromJson(const QJsonObject &json);
  QJsonObject toJson() const;

private:
  int m_id;
  QString m_name;
  QString m_description;
  int m_teacherId;
};

#endif // COURSE_H

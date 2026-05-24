#ifndef COURSE_H
#define COURSE_H

#include <QString>

class Course
{
public:
    Course();
    Course(int id, const QString &title, int teacherId);

    int getId() const;
    QString getTitle() const;
    int getTeacherId() const;

    void setTitle(const QString &title);
    void setTeacherId(int teacherId);

private:
    int m_id;
    QString m_title;
    int m_teacherId;
};

#endif

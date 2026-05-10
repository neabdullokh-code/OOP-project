#ifndef TEACHERWINDOW_H
#define TEACHERWINDOW_H

#include <QMainWindow>
#include "core/databasemanager.h"
#include "core/coursecontroller.h"
#include "core/gradecontroller.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class TeacherWindow;
}
QT_END_NAMESPACE

class TeacherWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TeacherWindow(DatabaseManager *databaseManager, int teacherId, QWidget *parent = 0);
    ~TeacherWindow();

signals:
    void logoutRequested();

private slots:
    void onRefreshClicked();
    void onSetGradeClicked();
    void onLogoutClicked();

private:
    void refreshData();

    Ui::TeacherWindow *ui;
    DatabaseManager *m_databaseManager;
    int m_teacherId;
    CourseController m_courseController;
    GradeController m_gradeController;
};

#endif

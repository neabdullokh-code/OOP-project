#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include "databasemanager.h"
#include "usercontroller.h"
#include "coursecontroller.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class AdminWindow;
}
QT_END_NAMESPACE

class AdminWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminWindow(DatabaseManager *databaseManager, QWidget *parent = 0);
    ~AdminWindow();

signals:
    void logoutRequested();

private slots:
    void onRefreshClicked();
    void onAddCourseClicked();
    void onEnrollStudentClicked();
    void onLogoutClicked();

private:
    void refreshData();

    Ui::AdminWindow *ui;
    DatabaseManager *m_databaseManager;
    UserController m_userController;
    CourseController m_courseController;
};

#endif

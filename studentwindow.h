#ifndef STUDENTWINDOW_H
#define STUDENTWINDOW_H

#include <QMainWindow>
#include "databasemanager.h"
#include "controllers.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class StudentWindow;
}
QT_END_NAMESPACE

class StudentWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StudentWindow(DatabaseManager *databaseManager, int studentId, QWidget *parent = 0);
    ~StudentWindow();

signals:
    void logoutRequested();

private slots:
    void onRefreshClicked();
    void onLogoutClicked();

private:
    void refreshData();

    Ui::StudentWindow *ui;
    DatabaseManager *m_databaseManager;
    int m_studentId;
    CourseController m_courseController;
    GradeController m_gradeController;
};

#endif

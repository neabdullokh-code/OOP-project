#ifndef TEACHERWINDOW_H
#define TEACHERWINDOW_H

#include <QMainWindow>
#include "filemanager.h"

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
    explicit TeacherWindow(FileManager *fileManager, int teacherId, QWidget *parent = 0);
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
    FileManager *m_fileManager;
    int m_teacherId;
};

#endif

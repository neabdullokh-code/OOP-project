#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include "filemanager.h"

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
    explicit AdminWindow(FileManager *fileManager, QWidget *parent = 0);
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
    FileManager *m_fileManager;
};

#endif

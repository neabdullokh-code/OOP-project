#ifndef STUDENTWINDOW_H
#define STUDENTWINDOW_H

#include <QMainWindow>
#include "filemanager.h"

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
    explicit StudentWindow(FileManager *fileManager, int studentId, QWidget *parent = 0);
    ~StudentWindow();

signals:
    void logoutRequested();

private slots:
    void onRefreshClicked();
    void onLogoutClicked();

private:
    void refreshData();

    Ui::StudentWindow *ui;
    FileManager *m_fileManager;
    int m_studentId;
};

#endif

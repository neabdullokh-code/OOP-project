#ifndef REGISTRATIONWINDOW_H
#define REGISTRATIONWINDOW_H

#include <QMainWindow>
#include "filemanager.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class RegistrationWindow;
}
QT_END_NAMESPACE

class RegistrationWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegistrationWindow(FileManager *fileManager, QWidget *parent = 0);
    ~RegistrationWindow();

signals:
    void backToLoginRequested();

private slots:
    void onRegisterStudentClicked();
    void onRegisterTeacherClicked();
    void onBackClicked();

private:
    void doRegister(QString role);

    Ui::RegistrationWindow *ui;
    FileManager *m_fileManager;
};

#endif

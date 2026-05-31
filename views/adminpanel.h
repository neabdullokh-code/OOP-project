#ifndef ADMINPANEL_H
#define ADMINPANEL_H

#include "../controllers/coursecontroller.h"
#include "../controllers/usercontroller.h"
#include "../models/user.h"
#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTabWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QWidget>

class AdminPanel : public QWidget {
  Q_OBJECT

public:
  explicit AdminPanel(const User &currentUser, QWidget *parent = nullptr);

private slots:
  void onAddUser();
  void onEditUser();
  void onDeleteUser();
  void onAddCourse();
  void onEditCourse();
  void onDeleteCourse();
  void onEnrollStudent();
  void onLogout();

private:
  void setupUI();
  void refreshDashboard();
  void refreshUsersTable();
  void refreshCoursesTable();
  QWidget *createDashboardTab();
  QWidget *createUsersTab();
  QWidget *createCoursesTab();
  QFrame *createStatCard(QLabel *valueLabel, const QString &label);

  User m_currentUser;
  UserController m_userController;
  CourseController m_courseController;

  QTabWidget *m_tabWidget;

  // Dashboard
  QLabel *m_totalUsersLabel;
  QLabel *m_totalCoursesLabel;
  QLabel *m_totalStudentsLabel;
  QLabel *m_totalTeachersLabel;

  // Таблицы
  QTableWidget *m_usersTable;
  QTableWidget *m_coursesTable;
};

#endif // ADMINPANEL_H

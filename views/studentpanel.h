#ifndef STUDENTPANEL_H
#define STUDENTPANEL_H

#include "../controllers/coursecontroller.h"
#include "../controllers/gradecontroller.h"
#include "../controllers/usercontroller.h"
#include "../models/user.h"
#include <QLabel>
#include <QTabWidget>
#include <QTableWidget>
#include <QWidget>

class StudentPanel : public QWidget {
  Q_OBJECT

public:
  explicit StudentPanel(const User &currentUser, QWidget *parent = nullptr);

private slots:
  void onLogout();

private:
  void setupUI();
  void refreshDashboard();
  void refreshCoursesTable();
  void refreshGradesTable();
  QWidget *createDashboardTab();
  QWidget *createCoursesTab();
  QWidget *createGradesTab();

  User m_currentUser;
  CourseController m_courseController;
  GradeController m_gradeController;
  UserController m_userController;

  QTabWidget *m_tabWidget;

  // Dashboard
  QLabel *m_coursesCountLabel;
  QLabel *m_avgGradeLabel;

  // Таблицы
  QTableWidget *m_coursesTable;
  QTableWidget *m_gradesTable;
};

#endif // STUDENTPANEL_H

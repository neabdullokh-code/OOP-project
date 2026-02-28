#ifndef TEACHERPANEL_H
#define TEACHERPANEL_H

#include "../controllers/coursecontroller.h"
#include "../controllers/gradecontroller.h"
#include "../controllers/usercontroller.h"
#include "../models/user.h"
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QTabWidget>
#include <QTableWidget>
#include <QWidget>

class TeacherPanel : public QWidget {
  Q_OBJECT

public:
  explicit TeacherPanel(const User &currentUser, QWidget *parent = nullptr);

private slots:
  void onCourseSelected(int index);
  void onSetGrade();
  void onLogout();

private:
  void setupUI();
  void refreshDashboard();
  void refreshStudentsTable();
  QWidget *createDashboardTab();
  QWidget *createGradesTab();

  User m_currentUser;
  CourseController m_courseController;
  GradeController m_gradeController;
  UserController m_userController;

  QTabWidget *m_tabWidget;

  // Dashboard
  QLabel *m_coursesCountLabel;
  QLabel *m_studentsCountLabel;
  QLabel *m_avgGradeLabel;

  // Оценки
  QComboBox *m_courseSelector;
  QTableWidget *m_studentsTable;
};

#endif // TEACHERPANEL_H

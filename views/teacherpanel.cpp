#include "teacherpanel.h"
#include "loginwindow.h"
#include <QApplication>
#include <QDate>
#include <QFrame>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QInputDialog>
#include <QMessageBox>
#include <QScreen>
#include <QVBoxLayout>

TeacherPanel::TeacherPanel(const User &currentUser, QWidget *parent)
    : QWidget(parent), m_currentUser(currentUser) {
  setupUI();
  setWindowTitle("Study.Table() — Панель преподавателя");
  resize(900, 600);

  QScreen *screen = QApplication::primaryScreen();
  if (screen) {
    QRect sg = screen->geometry();
    move((sg.width() - width()) / 2, (sg.height() - height()) / 2);
  }
}

void TeacherPanel::setupUI() {
  QVBoxLayout *mainLayout = new QVBoxLayout(this);
  mainLayout->setContentsMargins(20, 20, 20, 20);
  mainLayout->setSpacing(12);

  // Заголовок
  QHBoxLayout *headerLayout = new QHBoxLayout();
  QLabel *titleLabel = new QLabel("🟡 Панель преподавателя");
  titleLabel->setObjectName("titleLabel");
  headerLayout->addWidget(titleLabel);

  QLabel *welcomeLabel = new QLabel("Привет, " + m_currentUser.getName() + "!");
  welcomeLabel->setObjectName("subtitleLabel");
  headerLayout->addWidget(welcomeLabel);
  headerLayout->addStretch();

  QPushButton *logoutBtn = new QPushButton("Выйти");
  logoutBtn->setProperty("danger", true);
  logoutBtn->setCursor(Qt::PointingHandCursor);
  connect(logoutBtn, &QPushButton::clicked, this, &TeacherPanel::onLogout);
  headerLayout->addWidget(logoutBtn);

  mainLayout->addLayout(headerLayout);

  m_tabWidget = new QTabWidget();
  m_tabWidget->addTab(createDashboardTab(), "📊 Статистика");
  m_tabWidget->addTab(createGradesTab(), "📝 Оценки");
  mainLayout->addWidget(m_tabWidget);

  refreshDashboard();
}

QWidget *TeacherPanel::createDashboardTab() {
  QWidget *tab = new QWidget();
  QVBoxLayout *layout = new QVBoxLayout(tab);
  layout->setSpacing(20);

  QLabel *info = new QLabel("Ваша статистика");
  info->setObjectName("subtitleLabel");
  info->setAlignment(Qt::AlignCenter);
  layout->addWidget(info);

  QHBoxLayout *cardsLayout = new QHBoxLayout();
  cardsLayout->setSpacing(16);

  // Карточка: Мои курсы
  m_coursesCountLabel = new QLabel("0");
  m_coursesCountLabel->setObjectName("statValue");
  m_coursesCountLabel->setAlignment(Qt::AlignCenter);

  m_studentsCountLabel = new QLabel("0");
  m_studentsCountLabel->setObjectName("statValue");
  m_studentsCountLabel->setAlignment(Qt::AlignCenter);

  m_avgGradeLabel = new QLabel("0");
  m_avgGradeLabel->setObjectName("statValue");
  m_avgGradeLabel->setAlignment(Qt::AlignCenter);

  auto makeCard = [](QLabel *valLabel, const QString &desc) -> QFrame * {
    QFrame *card = new QFrame();
    card->setObjectName("statCard");
    card->setMinimumSize(200, 110);
    QVBoxLayout *l = new QVBoxLayout(card);
    l->setAlignment(Qt::AlignCenter);
    l->addWidget(valLabel);
    QLabel *d = new QLabel(desc);
    d->setObjectName("statLabel");
    d->setAlignment(Qt::AlignCenter);
    l->addWidget(d);
    return card;
  };

  cardsLayout->addWidget(makeCard(m_coursesCountLabel, "Ваших курсов"));
  cardsLayout->addWidget(makeCard(m_studentsCountLabel, "Ваших студентов"));
  cardsLayout->addWidget(makeCard(m_avgGradeLabel, "Средний балл"));

  layout->addLayout(cardsLayout);
  layout->addStretch();

  return tab;
}

QWidget *TeacherPanel::createGradesTab() {
  QWidget *tab = new QWidget();
  QVBoxLayout *layout = new QVBoxLayout(tab);

  // Выбор курса
  QHBoxLayout *topLayout = new QHBoxLayout();
  QLabel *courseLabel = new QLabel("Выберите курс:");
  courseLabel->setStyleSheet("font-weight: bold;");
  topLayout->addWidget(courseLabel);

  m_courseSelector = new QComboBox();
  m_courseSelector->setMinimumWidth(300);
  QList<Course> myCourses =
      m_courseController.getCoursesByTeacherId(m_currentUser.getId());
  for (const Course &c : myCourses) {
    m_courseSelector->addItem(c.getName(), c.getId());
  }
  connect(m_courseSelector, QOverload<int>::of(&QComboBox::currentIndexChanged),
          this, &TeacherPanel::onCourseSelected);
  topLayout->addWidget(m_courseSelector);
  topLayout->addStretch();

  QPushButton *gradeBtn = new QPushButton("✏️ Поставить оценку");
  gradeBtn->setProperty("primary", true);
  gradeBtn->setCursor(Qt::PointingHandCursor);
  connect(gradeBtn, &QPushButton::clicked, this, &TeacherPanel::onSetGrade);
  topLayout->addWidget(gradeBtn);

  layout->addLayout(topLayout);

  // Таблица студентов + оценки
  m_studentsTable = new QTableWidget();
  m_studentsTable->setColumnCount(3);
  m_studentsTable->setHorizontalHeaderLabels({"Студент", "Оценка", "Дата"});
  m_studentsTable->horizontalHeader()->setStretchLastSection(true);
  m_studentsTable->horizontalHeader()->setSectionResizeMode(
      0, QHeaderView::Stretch);
  m_studentsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
  m_studentsTable->setSelectionMode(QAbstractItemView::SingleSelection);
  m_studentsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
  m_studentsTable->setAlternatingRowColors(true);
  m_studentsTable->verticalHeader()->setVisible(false);
  layout->addWidget(m_studentsTable);

  // Загрузим первый курс
  if (m_courseSelector->count() > 0) {
    onCourseSelected(0);
  }

  return tab;
}

void TeacherPanel::refreshDashboard() {
  QList<Course> myCourses =
      m_courseController.getCoursesByTeacherId(m_currentUser.getId());
  m_coursesCountLabel->setText(QString::number(myCourses.size()));

  int totalStudents = 0;
  double totalGrade = 0;
  int gradeCount = 0;

  for (const Course &course : myCourses) {
    QList<Enrollment> enrollments =
        m_courseController.getEnrollmentsByCourseId(course.getId());
    totalStudents += enrollments.size();

    QList<Grade> grades = m_gradeController.getGradesByCourseId(course.getId());
    for (const Grade &g : grades) {
      totalGrade += g.getValue();
      gradeCount++;
    }
  }

  m_studentsCountLabel->setText(QString::number(totalStudents));
  if (gradeCount > 0) {
    m_avgGradeLabel->setText(QString::number(totalGrade / gradeCount, 'f', 1));
  } else {
    m_avgGradeLabel->setText("—");
  }
}

void TeacherPanel::onCourseSelected(int index) {
  if (index < 0)
    return;

  int courseId = m_courseSelector->currentData().toInt();
  QList<Enrollment> enrollments =
      m_courseController.getEnrollmentsByCourseId(courseId);

  m_studentsTable->setRowCount(enrollments.size());

  for (int i = 0; i < enrollments.size(); ++i) {
    User student = m_userController.getUserById(enrollments[i].getStudentId());
    m_studentsTable->setItem(i, 0, new QTableWidgetItem(student.getName()));

    Grade grade = m_gradeController.getGrade(student.getId(), courseId);
    if (grade.getId() != 0) {
      m_studentsTable->setItem(
          i, 1, new QTableWidgetItem(QString::number(grade.getValue())));
      m_studentsTable->setItem(i, 2, new QTableWidgetItem(grade.getDate()));
    } else {
      m_studentsTable->setItem(i, 1, new QTableWidgetItem("—"));
      m_studentsTable->setItem(i, 2, new QTableWidgetItem("—"));
    }
  }
}

void TeacherPanel::refreshStudentsTable() {
  onCourseSelected(m_courseSelector->currentIndex());
}

void TeacherPanel::onSetGrade() {
  int row = m_studentsTable->currentRow();
  if (row < 0) {
    QMessageBox::information(this, "Внимание", "Выберите студента в таблице");
    return;
  }

  int courseId = m_courseSelector->currentData().toInt();

  // Получаем студента через enrollments
  QList<Enrollment> enrollments =
      m_courseController.getEnrollmentsByCourseId(courseId);
  if (row >= enrollments.size())
    return;

  int studentId = enrollments[row].getStudentId();
  User student = m_userController.getUserById(studentId);

  bool ok;
  int grade = QInputDialog::getInt(this, "Оценка",
                                   "Оценка для " + student.getName() + ":", 50,
                                   0, 100, 1, &ok);

  if (ok) {
    m_gradeController.setGrade(studentId, courseId, grade,
                               QDate::currentDate().toString("yyyy-MM-dd"));
    refreshStudentsTable();
    refreshDashboard();
  }
}

void TeacherPanel::onLogout() {
  LoginWindow *login = new LoginWindow();
  login->show();
  this->close();
}

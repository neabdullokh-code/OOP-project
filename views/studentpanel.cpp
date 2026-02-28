#include "studentpanel.h"
#include "loginwindow.h"
#include <QApplication>
#include <QFrame>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QPushButton>
#include <QScreen>
#include <QVBoxLayout>

StudentPanel::StudentPanel(const User &currentUser, QWidget *parent)
    : QWidget(parent), m_currentUser(currentUser) {
  setupUI();
  setWindowTitle("Study.Table() — Панель студента");
  resize(850, 550);
  QScreen *screen = QApplication::primaryScreen();
  if (screen) {
    QRect sg = screen->geometry();
    move((sg.width() - width()) / 2, (sg.height() - height()) / 2);
  }
}

void StudentPanel::setupUI() {
  QVBoxLayout *mainLayout = new QVBoxLayout(this);
  mainLayout->setContentsMargins(20, 20, 20, 20);
  mainLayout->setSpacing(12);

  QHBoxLayout *headerLayout = new QHBoxLayout();
  QLabel *titleLabel = new QLabel("🟢 Панель студента");
  titleLabel->setObjectName("titleLabel");
  headerLayout->addWidget(titleLabel);
  QLabel *welcomeLabel = new QLabel("Привет, " + m_currentUser.getName() + "!");
  welcomeLabel->setObjectName("subtitleLabel");
  headerLayout->addWidget(welcomeLabel);
  headerLayout->addStretch();
  QPushButton *logoutBtn = new QPushButton("Выйти");
  logoutBtn->setProperty("danger", true);
  logoutBtn->setCursor(Qt::PointingHandCursor);
  connect(logoutBtn, &QPushButton::clicked, this, &StudentPanel::onLogout);
  headerLayout->addWidget(logoutBtn);
  mainLayout->addLayout(headerLayout);

  m_tabWidget = new QTabWidget();
  m_tabWidget->addTab(createDashboardTab(), "📊 Статистика");
  m_tabWidget->addTab(createCoursesTab(), "📚 Мои курсы");
  m_tabWidget->addTab(createGradesTab(), "📝 Оценки");
  mainLayout->addWidget(m_tabWidget);

  refreshDashboard();
  refreshCoursesTable();
  refreshGradesTable();
}

QWidget *StudentPanel::createDashboardTab() {
  QWidget *tab = new QWidget();
  QVBoxLayout *layout = new QVBoxLayout(tab);
  layout->setSpacing(20);

  QLabel *info = new QLabel("Ваша статистика");
  info->setObjectName("subtitleLabel");
  info->setAlignment(Qt::AlignCenter);
  layout->addWidget(info);

  QHBoxLayout *cardsLayout = new QHBoxLayout();
  cardsLayout->setSpacing(16);

  m_coursesCountLabel = new QLabel("0");
  m_coursesCountLabel->setObjectName("statValue");
  m_coursesCountLabel->setAlignment(Qt::AlignCenter);

  m_avgGradeLabel = new QLabel("0");
  m_avgGradeLabel->setObjectName("statValue");
  m_avgGradeLabel->setAlignment(Qt::AlignCenter);

  auto makeCard = [](QLabel *valLabel, const QString &desc) -> QFrame * {
    QFrame *card = new QFrame();
    card->setObjectName("statCard");
    card->setMinimumSize(220, 120);
    QVBoxLayout *l = new QVBoxLayout(card);
    l->setAlignment(Qt::AlignCenter);
    l->addWidget(valLabel);
    QLabel *d = new QLabel(desc);
    d->setObjectName("statLabel");
    d->setAlignment(Qt::AlignCenter);
    l->addWidget(d);
    return card;
  };

  cardsLayout->addWidget(makeCard(m_coursesCountLabel, "Записан на курсов"));
  cardsLayout->addWidget(makeCard(m_avgGradeLabel, "Средний балл"));
  layout->addLayout(cardsLayout);
  layout->addStretch();
  return tab;
}

QWidget *StudentPanel::createCoursesTab() {
  QWidget *tab = new QWidget();
  QVBoxLayout *layout = new QVBoxLayout(tab);

  m_coursesTable = new QTableWidget();
  m_coursesTable->setColumnCount(3);
  m_coursesTable->setHorizontalHeaderLabels(
      {"Название курса", "Преподаватель", "Оценка"});
  m_coursesTable->horizontalHeader()->setStretchLastSection(true);
  m_coursesTable->horizontalHeader()->setSectionResizeMode(
      0, QHeaderView::Stretch);
  m_coursesTable->setSelectionBehavior(QAbstractItemView::SelectRows);
  m_coursesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
  m_coursesTable->setAlternatingRowColors(true);
  m_coursesTable->verticalHeader()->setVisible(false);
  layout->addWidget(m_coursesTable);
  return tab;
}

QWidget *StudentPanel::createGradesTab() {
  QWidget *tab = new QWidget();
  QVBoxLayout *layout = new QVBoxLayout(tab);

  m_gradesTable = new QTableWidget();
  m_gradesTable->setColumnCount(3);
  m_gradesTable->setHorizontalHeaderLabels({"Курс", "Оценка", "Дата"});
  m_gradesTable->horizontalHeader()->setStretchLastSection(true);
  m_gradesTable->horizontalHeader()->setSectionResizeMode(0,
                                                          QHeaderView::Stretch);
  m_gradesTable->setSelectionBehavior(QAbstractItemView::SelectRows);
  m_gradesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
  m_gradesTable->setAlternatingRowColors(true);
  m_gradesTable->verticalHeader()->setVisible(false);
  layout->addWidget(m_gradesTable);

  QHBoxLayout *bottomLayout = new QHBoxLayout();
  bottomLayout->addStretch();
  QLabel *avgLabel = new QLabel("Средний балл: ");
  avgLabel->setStyleSheet("font-weight: bold; font-size: 16px;");
  bottomLayout->addWidget(avgLabel);
  QLabel *avgValue = new QLabel("—");
  avgValue->setObjectName("avgGradeBottom");
  avgValue->setStyleSheet(
      "font-weight: bold; font-size: 16px; color: #89b4fa;");
  bottomLayout->addWidget(avgValue);
  layout->addLayout(bottomLayout);
  return tab;
}

void StudentPanel::refreshDashboard() {
  QList<Enrollment> enrollments =
      m_courseController.getEnrollmentsByStudentId(m_currentUser.getId());
  m_coursesCountLabel->setText(QString::number(enrollments.size()));
  double avg =
      m_gradeController.getAverageGradeForStudent(m_currentUser.getId());
  m_avgGradeLabel->setText(avg > 0 ? QString::number(avg, 'f', 1) : "—");
}

void StudentPanel::refreshCoursesTable() {
  QList<Enrollment> enrollments =
      m_courseController.getEnrollmentsByStudentId(m_currentUser.getId());
  m_coursesTable->setRowCount(enrollments.size());
  for (int i = 0; i < enrollments.size(); ++i) {
    Course course =
        m_courseController.getCourseById(enrollments[i].getCourseId());
    m_coursesTable->setItem(i, 0, new QTableWidgetItem(course.getName()));
    User teacher = m_userController.getUserById(course.getTeacherId());
    m_coursesTable->setItem(i, 1, new QTableWidgetItem(teacher.getName()));
    Grade grade =
        m_gradeController.getGrade(m_currentUser.getId(), course.getId());
    QString gradeText =
        grade.getId() != 0 ? QString::number(grade.getValue()) : "—";
    m_coursesTable->setItem(i, 2, new QTableWidgetItem(gradeText));
  }
}

void StudentPanel::refreshGradesTable() {
  QList<Grade> grades =
      m_gradeController.getGradesByStudentId(m_currentUser.getId());
  m_gradesTable->setRowCount(grades.size());
  double total = 0;
  for (int i = 0; i < grades.size(); ++i) {
    Course course = m_courseController.getCourseById(grades[i].getCourseId());
    m_gradesTable->setItem(i, 0, new QTableWidgetItem(course.getName()));
    m_gradesTable->setItem(
        i, 1, new QTableWidgetItem(QString::number(grades[i].getValue())));
    m_gradesTable->setItem(i, 2, new QTableWidgetItem(grades[i].getDate()));
    total += grades[i].getValue();
  }
  QLabel *avgValue =
      m_gradesTable->parentWidget()->findChild<QLabel *>("avgGradeBottom");
  if (avgValue && !grades.isEmpty()) {
    avgValue->setText(QString::number(total / grades.size(), 'f', 1));
  }
}

void StudentPanel::onLogout() {
  LoginWindow *login = new LoginWindow();
  login->show();
  this->close();
}

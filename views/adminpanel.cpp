#include "adminpanel.h"
#include "loginwindow.h"
#include <QApplication>
#include <QComboBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QHeaderView>
#include <QInputDialog>
#include <QLineEdit>
#include <QMessageBox>
#include <QScreen>

AdminPanel::AdminPanel(const User &currentUser, QWidget *parent)
    : QWidget(parent), m_currentUser(currentUser) {
  setupUI();
  setWindowTitle("Study.Table() — Панель администратора");
  resize(1000, 650);

  // Центрируем
  QScreen *screen = QApplication::primaryScreen();
  if (screen) {
    QRect sg = screen->geometry();
    move((sg.width() - width()) / 2, (sg.height() - height()) / 2);
  }
}

void AdminPanel::setupUI() {
  QVBoxLayout *mainLayout = new QVBoxLayout(this);
  mainLayout->setContentsMargins(20, 20, 20, 20);
  mainLayout->setSpacing(12);

  // Заголовок + кнопка выхода
  QHBoxLayout *headerLayout = new QHBoxLayout();
  QLabel *titleLabel = new QLabel("🔴 Панель администратора");
  titleLabel->setObjectName("titleLabel");
  headerLayout->addWidget(titleLabel);

  QLabel *welcomeLabel = new QLabel("Привет, " + m_currentUser.getName() + "!");
  welcomeLabel->setObjectName("subtitleLabel");
  headerLayout->addWidget(welcomeLabel);

  headerLayout->addStretch();

  QPushButton *logoutBtn = new QPushButton("Выйти");
  logoutBtn->setProperty("danger", true);
  logoutBtn->setCursor(Qt::PointingHandCursor);
  connect(logoutBtn, &QPushButton::clicked, this, &AdminPanel::onLogout);
  headerLayout->addWidget(logoutBtn);

  mainLayout->addLayout(headerLayout);

  // Вкладки
  m_tabWidget = new QTabWidget();
  m_tabWidget->addTab(createDashboardTab(), "📊 Статистика");
  m_tabWidget->addTab(createUsersTab(), "👥 Пользователи");
  m_tabWidget->addTab(createCoursesTab(), "📚 Курсы");
  mainLayout->addWidget(m_tabWidget);

  // Загрузим данные
  refreshDashboard();
  refreshUsersTable();
  refreshCoursesTable();
}

QFrame *AdminPanel::createStatCard(const QString &value, const QString &label) {
  QFrame *card = new QFrame();
  card->setObjectName("statCard");
  card->setMinimumSize(180, 100);

  QVBoxLayout *layout = new QVBoxLayout(card);
  layout->setAlignment(Qt::AlignCenter);

  QLabel *valueLabel = new QLabel(value);
  valueLabel->setObjectName("statValue");
  valueLabel->setAlignment(Qt::AlignCenter);
  layout->addWidget(valueLabel);

  QLabel *descLabel = new QLabel(label);
  descLabel->setObjectName("statLabel");
  descLabel->setAlignment(Qt::AlignCenter);
  layout->addWidget(descLabel);

  return card;
}

QWidget *AdminPanel::createDashboardTab() {
  QWidget *tab = new QWidget();
  QVBoxLayout *layout = new QVBoxLayout(tab);
  layout->setSpacing(20);

  QLabel *info = new QLabel("Общая статистика системы");
  info->setObjectName("subtitleLabel");
  info->setAlignment(Qt::AlignCenter);
  layout->addWidget(info);

  QHBoxLayout *cardsLayout = new QHBoxLayout();
  cardsLayout->setSpacing(16);

  m_totalUsersLabel = new QLabel("0");
  m_totalUsersLabel->setObjectName("statValue");
  m_totalUsersLabel->setAlignment(Qt::AlignCenter);

  m_totalCoursesLabel = new QLabel("0");
  m_totalCoursesLabel->setObjectName("statValue");
  m_totalCoursesLabel->setAlignment(Qt::AlignCenter);

  m_totalStudentsLabel = new QLabel("0");
  m_totalStudentsLabel->setObjectName("statValue");
  m_totalStudentsLabel->setAlignment(Qt::AlignCenter);

  m_totalTeachersLabel = new QLabel("0");
  m_totalTeachersLabel->setObjectName("statValue");
  m_totalTeachersLabel->setAlignment(Qt::AlignCenter);

  // Создаём карточки
  auto makeCard = [](QLabel *valLabel, const QString &desc) -> QFrame * {
    QFrame *card = new QFrame();
    card->setObjectName("statCard");
    card->setMinimumSize(180, 100);
    QVBoxLayout *l = new QVBoxLayout(card);
    l->setAlignment(Qt::AlignCenter);
    l->addWidget(valLabel);
    QLabel *d = new QLabel(desc);
    d->setObjectName("statLabel");
    d->setAlignment(Qt::AlignCenter);
    l->addWidget(d);
    return card;
  };

  cardsLayout->addWidget(makeCard(m_totalUsersLabel, "Всего пользователей"));
  cardsLayout->addWidget(makeCard(m_totalCoursesLabel, "Всего курсов"));
  cardsLayout->addWidget(makeCard(m_totalStudentsLabel, "Студентов"));
  cardsLayout->addWidget(makeCard(m_totalTeachersLabel, "Преподавателей"));

  layout->addLayout(cardsLayout);
  layout->addStretch();

  return tab;
}

QWidget *AdminPanel::createUsersTab() {
  QWidget *tab = new QWidget();
  QVBoxLayout *layout = new QVBoxLayout(tab);

  // Кнопки
  QHBoxLayout *btnLayout = new QHBoxLayout();
  QPushButton *addBtn = new QPushButton("➕ Добавить");
  addBtn->setProperty("primary", true);
  addBtn->setCursor(Qt::PointingHandCursor);
  connect(addBtn, &QPushButton::clicked, this, &AdminPanel::onAddUser);

  QPushButton *editBtn = new QPushButton("✏️ Редактировать");
  editBtn->setCursor(Qt::PointingHandCursor);
  connect(editBtn, &QPushButton::clicked, this, &AdminPanel::onEditUser);

  QPushButton *deleteBtn = new QPushButton("🗑 Удалить");
  deleteBtn->setProperty("danger", true);
  deleteBtn->setCursor(Qt::PointingHandCursor);
  connect(deleteBtn, &QPushButton::clicked, this, &AdminPanel::onDeleteUser);

  btnLayout->addWidget(addBtn);
  btnLayout->addWidget(editBtn);
  btnLayout->addWidget(deleteBtn);
  btnLayout->addStretch();
  layout->addLayout(btnLayout);

  // Таблица пользователей
  m_usersTable = new QTableWidget();
  m_usersTable->setColumnCount(4);
  m_usersTable->setHorizontalHeaderLabels({"ID", "Имя", "Логин", "Роль"});
  m_usersTable->horizontalHeader()->setStretchLastSection(true);
  m_usersTable->horizontalHeader()->setSectionResizeMode(1,
                                                         QHeaderView::Stretch);
  m_usersTable->setSelectionBehavior(QAbstractItemView::SelectRows);
  m_usersTable->setSelectionMode(QAbstractItemView::SingleSelection);
  m_usersTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
  m_usersTable->setAlternatingRowColors(true);
  m_usersTable->verticalHeader()->setVisible(false);
  layout->addWidget(m_usersTable);

  return tab;
}

QWidget *AdminPanel::createCoursesTab() {
  QWidget *tab = new QWidget();
  QVBoxLayout *layout = new QVBoxLayout(tab);

  // Кнопки
  QHBoxLayout *btnLayout = new QHBoxLayout();
  QPushButton *addBtn = new QPushButton("➕ Создать курс");
  addBtn->setProperty("primary", true);
  addBtn->setCursor(Qt::PointingHandCursor);
  connect(addBtn, &QPushButton::clicked, this, &AdminPanel::onAddCourse);

  QPushButton *editBtn = new QPushButton("✏️ Редактировать");
  editBtn->setCursor(Qt::PointingHandCursor);
  connect(editBtn, &QPushButton::clicked, this, &AdminPanel::onEditCourse);

  QPushButton *deleteBtn = new QPushButton("🗑 Удалить");
  deleteBtn->setProperty("danger", true);
  deleteBtn->setCursor(Qt::PointingHandCursor);
  connect(deleteBtn, &QPushButton::clicked, this, &AdminPanel::onDeleteCourse);

  QPushButton *enrollBtn = new QPushButton("📝 Записать студента");
  enrollBtn->setProperty("success", true);
  enrollBtn->setCursor(Qt::PointingHandCursor);
  connect(enrollBtn, &QPushButton::clicked, this, &AdminPanel::onEnrollStudent);

  btnLayout->addWidget(addBtn);
  btnLayout->addWidget(editBtn);
  btnLayout->addWidget(deleteBtn);
  btnLayout->addWidget(enrollBtn);
  btnLayout->addStretch();
  layout->addLayout(btnLayout);

  // Таблица курсов
  m_coursesTable = new QTableWidget();
  m_coursesTable->setColumnCount(4);
  m_coursesTable->setHorizontalHeaderLabels(
      {"ID", "Название", "Преподаватель", "Студентов"});
  m_coursesTable->horizontalHeader()->setStretchLastSection(true);
  m_coursesTable->horizontalHeader()->setSectionResizeMode(
      1, QHeaderView::Stretch);
  m_coursesTable->setSelectionBehavior(QAbstractItemView::SelectRows);
  m_coursesTable->setSelectionMode(QAbstractItemView::SingleSelection);
  m_coursesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
  m_coursesTable->setAlternatingRowColors(true);
  m_coursesTable->verticalHeader()->setVisible(false);
  layout->addWidget(m_coursesTable);

  return tab;
}

void AdminPanel::refreshDashboard() {
  m_totalUsersLabel->setText(QString::number(m_userController.getTotalUsers()));
  m_totalCoursesLabel->setText(
      QString::number(m_courseController.getTotalCourses()));
  m_totalStudentsLabel->setText(
      QString::number(m_userController.getStudentCount()));
  m_totalTeachersLabel->setText(
      QString::number(m_userController.getTeacherCount()));
}

void AdminPanel::refreshUsersTable() {
  QList<User> users = m_userController.getAllUsers();
  m_usersTable->setRowCount(users.size());

  for (int i = 0; i < users.size(); ++i) {
    m_usersTable->setItem(
        i, 0, new QTableWidgetItem(QString::number(users[i].getId())));
    m_usersTable->setItem(i, 1, new QTableWidgetItem(users[i].getName()));
    m_usersTable->setItem(i, 2, new QTableWidgetItem(users[i].getLogin()));

    QString roleDisplay;
    if (users[i].getRole() == "admin")
      roleDisplay = "🔴 Администратор";
    else if (users[i].getRole() == "teacher")
      roleDisplay = "🟡 Преподаватель";
    else
      roleDisplay = "🟢 Студент";
    m_usersTable->setItem(i, 3, new QTableWidgetItem(roleDisplay));
  }
}

void AdminPanel::refreshCoursesTable() {
  QList<Course> courses = m_courseController.getAllCourses();
  m_coursesTable->setRowCount(courses.size());

  for (int i = 0; i < courses.size(); ++i) {
    m_coursesTable->setItem(
        i, 0, new QTableWidgetItem(QString::number(courses[i].getId())));
    m_coursesTable->setItem(i, 1, new QTableWidgetItem(courses[i].getName()));

    // Имя преподавателя
    User teacher = m_userController.getUserById(courses[i].getTeacherId());
    m_coursesTable->setItem(i, 2, new QTableWidgetItem(teacher.getName()));

    int count = m_courseController.getStudentCountForCourse(courses[i].getId());
    m_coursesTable->setItem(i, 3, new QTableWidgetItem(QString::number(count)));
  }
}

void AdminPanel::onAddUser() {
  QDialog dialog(this);
  dialog.setWindowTitle("Добавить пользователя");
  dialog.setMinimumWidth(350);

  QFormLayout *formLayout = new QFormLayout(&dialog);

  QLineEdit *nameInput = new QLineEdit();
  nameInput->setPlaceholderText("Фамилия Имя");
  formLayout->addRow("Имя:", nameInput);

  QLineEdit *loginInput = new QLineEdit();
  loginInput->setPlaceholderText("login");
  formLayout->addRow("Логин:", loginInput);

  QLineEdit *passInput = new QLineEdit();
  passInput->setPlaceholderText("password");
  passInput->setEchoMode(QLineEdit::Password);
  formLayout->addRow("Пароль:", passInput);

  QComboBox *roleBox = new QComboBox();
  roleBox->addItem("Студент", "student");
  roleBox->addItem("Преподаватель", "teacher");
  roleBox->addItem("Администратор", "admin");
  formLayout->addRow("Роль:", roleBox);

  QDialogButtonBox *buttons =
      new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
  formLayout->addRow(buttons);
  connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
  connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

  if (dialog.exec() == QDialog::Accepted) {
    QString name = nameInput->text().trimmed();
    QString login = loginInput->text().trimmed();
    QString pass = passInput->text();
    QString role = roleBox->currentData().toString();

    if (name.isEmpty() || login.isEmpty() || pass.isEmpty()) {
      QMessageBox::warning(this, "Ошибка", "Заполните все поля!");
      return;
    }

    m_userController.addUser(name, login, pass, role);
    refreshUsersTable();
    refreshDashboard();
  }
}

void AdminPanel::onEditUser() {
  int row = m_usersTable->currentRow();
  if (row < 0) {
    QMessageBox::information(this, "Внимание",
                             "Выберите пользователя в таблице");
    return;
  }

  int userId = m_usersTable->item(row, 0)->text().toInt();
  User user = m_userController.getUserById(userId);

  QDialog dialog(this);
  dialog.setWindowTitle("Редактировать пользователя");
  dialog.setMinimumWidth(350);

  QFormLayout *formLayout = new QFormLayout(&dialog);

  QLineEdit *nameInput = new QLineEdit(user.getName());
  formLayout->addRow("Имя:", nameInput);

  QLineEdit *loginInput = new QLineEdit(user.getLogin());
  formLayout->addRow("Логин:", loginInput);

  QLineEdit *passInput = new QLineEdit(user.getPassword());
  passInput->setEchoMode(QLineEdit::Password);
  formLayout->addRow("Пароль:", passInput);

  QComboBox *roleBox = new QComboBox();
  roleBox->addItem("Студент", "student");
  roleBox->addItem("Преподаватель", "teacher");
  roleBox->addItem("Администратор", "admin");
  int roleIndex = roleBox->findData(user.getRole());
  if (roleIndex >= 0)
    roleBox->setCurrentIndex(roleIndex);
  formLayout->addRow("Роль:", roleBox);

  QDialogButtonBox *buttons =
      new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
  formLayout->addRow(buttons);
  connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
  connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

  if (dialog.exec() == QDialog::Accepted) {
    m_userController.updateUser(userId, nameInput->text().trimmed(),
                                loginInput->text().trimmed(), passInput->text(),
                                roleBox->currentData().toString());
    refreshUsersTable();
    refreshDashboard();
  }
}

void AdminPanel::onDeleteUser() {
  int row = m_usersTable->currentRow();
  if (row < 0) {
    QMessageBox::information(this, "Внимание",
                             "Выберите пользователя в таблице");
    return;
  }

  int userId = m_usersTable->item(row, 0)->text().toInt();
  QString userName = m_usersTable->item(row, 1)->text();

  QMessageBox::StandardButton reply = QMessageBox::question(
      this, "Подтверждение",
      "Удалить пользователя \"" + userName +
          "\"?\n"
          "Все связанные оценки и записи на курсы будут удалены.",
      QMessageBox::Yes | QMessageBox::No);

  if (reply == QMessageBox::Yes) {
    m_userController.deleteUser(userId);
    refreshUsersTable();
    refreshDashboard();
  }
}

void AdminPanel::onAddCourse() {
  QDialog dialog(this);
  dialog.setWindowTitle("Создать курс");
  dialog.setMinimumWidth(400);

  QFormLayout *formLayout = new QFormLayout(&dialog);

  QLineEdit *nameInput = new QLineEdit();
  nameInput->setPlaceholderText("Название курса");
  formLayout->addRow("Название:", nameInput);

  QLineEdit *descInput = new QLineEdit();
  descInput->setPlaceholderText("Описание курса");
  formLayout->addRow("Описание:", descInput);

  QComboBox *teacherBox = new QComboBox();
  QList<User> teachers = m_userController.getUsersByRole("teacher");
  for (const User &t : teachers) {
    teacherBox->addItem(t.getName(), t.getId());
  }
  formLayout->addRow("Преподаватель:", teacherBox);

  QDialogButtonBox *buttons =
      new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
  formLayout->addRow(buttons);
  connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
  connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

  if (dialog.exec() == QDialog::Accepted) {
    QString name = nameInput->text().trimmed();
    if (name.isEmpty()) {
      QMessageBox::warning(this, "Ошибка", "Введите название курса!");
      return;
    }
    int teacherId = teacherBox->currentData().toInt();
    m_courseController.addCourse(name, descInput->text().trimmed(), teacherId);
    refreshCoursesTable();
    refreshDashboard();
  }
}

void AdminPanel::onEditCourse() {
  int row = m_coursesTable->currentRow();
  if (row < 0) {
    QMessageBox::information(this, "Внимание", "Выберите курс в таблице");
    return;
  }

  int courseId = m_coursesTable->item(row, 0)->text().toInt();
  Course course = m_courseController.getCourseById(courseId);

  QDialog dialog(this);
  dialog.setWindowTitle("Редактировать курс");
  dialog.setMinimumWidth(400);

  QFormLayout *formLayout = new QFormLayout(&dialog);

  QLineEdit *nameInput = new QLineEdit(course.getName());
  formLayout->addRow("Название:", nameInput);

  QLineEdit *descInput = new QLineEdit(course.getDescription());
  formLayout->addRow("Описание:", descInput);

  QComboBox *teacherBox = new QComboBox();
  QList<User> teachers = m_userController.getUsersByRole("teacher");
  for (const User &t : teachers) {
    teacherBox->addItem(t.getName(), t.getId());
  }
  int idx = teacherBox->findData(course.getTeacherId());
  if (idx >= 0)
    teacherBox->setCurrentIndex(idx);
  formLayout->addRow("Преподаватель:", teacherBox);

  QDialogButtonBox *buttons =
      new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
  formLayout->addRow(buttons);
  connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
  connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

  if (dialog.exec() == QDialog::Accepted) {
    m_courseController.updateCourse(courseId, nameInput->text().trimmed(),
                                    descInput->text().trimmed(),
                                    teacherBox->currentData().toInt());
    refreshCoursesTable();
  }
}

void AdminPanel::onDeleteCourse() {
  int row = m_coursesTable->currentRow();
  if (row < 0) {
    QMessageBox::information(this, "Внимание", "Выберите курс в таблице");
    return;
  }

  int courseId = m_coursesTable->item(row, 0)->text().toInt();
  QString courseName = m_coursesTable->item(row, 1)->text();

  QMessageBox::StandardButton reply =
      QMessageBox::question(this, "Подтверждение",
                            "Удалить курс \"" + courseName +
                                "\"?\n"
                                "Все связанные оценки и записи будут удалены.",
                            QMessageBox::Yes | QMessageBox::No);

  if (reply == QMessageBox::Yes) {
    m_courseController.deleteCourse(courseId);
    refreshCoursesTable();
    refreshDashboard();
  }
}

void AdminPanel::onEnrollStudent() {
  int row = m_coursesTable->currentRow();
  if (row < 0) {
    QMessageBox::information(this, "Внимание",
                             "Сначала выберите курс в таблице");
    return;
  }

  int courseId = m_coursesTable->item(row, 0)->text().toInt();

  QDialog dialog(this);
  dialog.setWindowTitle("Записать студента на курс");
  dialog.setMinimumWidth(350);

  QFormLayout *formLayout = new QFormLayout(&dialog);

  QComboBox *studentBox = new QComboBox();
  QList<User> students = m_userController.getUsersByRole("student");

  // Исключаем уже записанных
  QList<Enrollment> existing =
      m_courseController.getEnrollmentsByCourseId(courseId);
  QSet<int> enrolledIds;
  for (const Enrollment &e : existing) {
    enrolledIds.insert(e.getStudentId());
  }

  for (const User &s : students) {
    if (!enrolledIds.contains(s.getId())) {
      studentBox->addItem(s.getName(), s.getId());
    }
  }

  if (studentBox->count() == 0) {
    QMessageBox::information(this, "Информация",
                             "Все студенты уже записаны на этот курс!");
    return;
  }

  formLayout->addRow("Студент:", studentBox);

  QDialogButtonBox *buttons =
      new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
  formLayout->addRow(buttons);
  connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
  connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

  if (dialog.exec() == QDialog::Accepted) {
    int studentId = studentBox->currentData().toInt();
    m_courseController.enrollStudent(studentId, courseId, "");
    refreshCoursesTable();
  }
}

void AdminPanel::onLogout() {
  LoginWindow *login = new LoginWindow();
  login->show();
  this->close();
}

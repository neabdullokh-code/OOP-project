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
  setAttribute(Qt::WA_DeleteOnClose);
  setupUI();
  setWindowTitle("Study.Table() — Administrator");
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
  QLabel *titleLabel = new QLabel("🔴 Administrator");
  titleLabel->setObjectName("titleLabel");
  headerLayout->addWidget(titleLabel);

  QLabel *welcomeLabel = new QLabel("Hello, " + m_currentUser.getName() + "!");
  welcomeLabel->setObjectName("subtitleLabel");
  headerLayout->addWidget(welcomeLabel);

  headerLayout->addStretch();

  QPushButton *logoutBtn = new QPushButton("Logout");
  logoutBtn->setProperty("danger", true);
  logoutBtn->setCursor(Qt::PointingHandCursor);
  connect(logoutBtn, &QPushButton::clicked, this, &AdminPanel::onLogout);
  headerLayout->addWidget(logoutBtn);

  mainLayout->addLayout(headerLayout);

  // Вкладки
  m_tabWidget = new QTabWidget();
  m_tabWidget->addTab(createDashboardTab(), "📊 Statistics");
  m_tabWidget->addTab(createUsersTab(), "👥 Users");
  m_tabWidget->addTab(createCoursesTab(), "📚 Courses");
  mainLayout->addWidget(m_tabWidget);

  // Загрузим данные
  refreshDashboard();
  refreshUsersTable();
  refreshCoursesTable();
}

QFrame *AdminPanel::createStatCard(QLabel *valueLabel, const QString &label) {
  QFrame *card = new QFrame();
  card->setObjectName("statCard");
  card->setMinimumSize(180, 100);

  QVBoxLayout *layout = new QVBoxLayout(card);
  layout->setAlignment(Qt::AlignCenter);

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

  QLabel *info = new QLabel("System overview");
  info->setObjectName("subtitleLabel");
  info->setAlignment(Qt::AlignCenter);
  layout->addWidget(info);

  QHBoxLayout *cardsLayout = new QHBoxLayout();
  cardsLayout->setSpacing(16);

  m_totalUsersLabel = new QLabel("0");
  m_totalCoursesLabel = new QLabel("0");
  m_totalStudentsLabel = new QLabel("0");
  m_totalTeachersLabel = new QLabel("0");

  cardsLayout->addWidget(
      createStatCard(m_totalUsersLabel, "Total users"));
  cardsLayout->addWidget(createStatCard(m_totalCoursesLabel, "Total courses"));
  cardsLayout->addWidget(createStatCard(m_totalStudentsLabel, "Students"));
  cardsLayout->addWidget(createStatCard(m_totalTeachersLabel, "Teachers"));

  layout->addLayout(cardsLayout);
  layout->addStretch();

  return tab;
}

QWidget *AdminPanel::createUsersTab() {
  QWidget *tab = new QWidget();
  QVBoxLayout *layout = new QVBoxLayout(tab);

  // Кнопки
  QHBoxLayout *btnLayout = new QHBoxLayout();
  QPushButton *addBtn = new QPushButton("➕ Add");
  addBtn->setProperty("primary", true);
  addBtn->setCursor(Qt::PointingHandCursor);
  connect(addBtn, &QPushButton::clicked, this, &AdminPanel::onAddUser);

  QPushButton *editBtn = new QPushButton("✏️ Edit");
  editBtn->setCursor(Qt::PointingHandCursor);
  connect(editBtn, &QPushButton::clicked, this, &AdminPanel::onEditUser);

  QPushButton *deleteBtn = new QPushButton("🗑 Delete");
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
  m_usersTable->setHorizontalHeaderLabels({"ID", "Name", "Login", "Role"});
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
  QPushButton *addBtn = new QPushButton("➕ Create course");
  addBtn->setProperty("primary", true);
  addBtn->setCursor(Qt::PointingHandCursor);
  connect(addBtn, &QPushButton::clicked, this, &AdminPanel::onAddCourse);

  QPushButton *editBtn = new QPushButton("✏️ Edit");
  editBtn->setCursor(Qt::PointingHandCursor);
  connect(editBtn, &QPushButton::clicked, this, &AdminPanel::onEditCourse);

  QPushButton *deleteBtn = new QPushButton("🗑 Delete");
  deleteBtn->setProperty("danger", true);
  deleteBtn->setCursor(Qt::PointingHandCursor);
  connect(deleteBtn, &QPushButton::clicked, this, &AdminPanel::onDeleteCourse);

  QPushButton *enrollBtn = new QPushButton("📝 Enroll student");
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
      {"ID", "Title", "Teacher", "Students"});
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
      roleDisplay = "🔴 Administrator";
    else if (users[i].getRole() == "teacher")
      roleDisplay = "🟡 Teacher";
    else
      roleDisplay = "🟢 Student";
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
  dialog.setWindowTitle("Add user");
  dialog.setMinimumWidth(350);

  QFormLayout *formLayout = new QFormLayout(&dialog);

  QLineEdit *nameInput = new QLineEdit();
  nameInput->setPlaceholderText("Last, First");
  formLayout->addRow("Name:", nameInput);

  QLineEdit *loginInput = new QLineEdit();
  loginInput->setPlaceholderText("login");
  formLayout->addRow("Login:", loginInput);

  QLineEdit *passInput = new QLineEdit();
  passInput->setPlaceholderText("password");
  passInput->setEchoMode(QLineEdit::Password);
  formLayout->addRow("Password:", passInput);

  QComboBox *roleBox = new QComboBox();
  roleBox->addItem("Student", "student");
  roleBox->addItem("Teacher", "teacher");
  roleBox->addItem("Administrator", "admin");
  formLayout->addRow("Role:", roleBox);

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
      QMessageBox::warning(this, "Error", "Please fill in all fields.");
      return;
    }

    if (!m_userController.addUser(name, login, pass, role)) {
      QMessageBox::warning(this, "Error",
                           "A user with this login already exists.");
      return;
    }
    refreshUsersTable();
    refreshDashboard();
  }
}

void AdminPanel::onEditUser() {
  int row = m_usersTable->currentRow();
  if (row < 0) {
    QMessageBox::information(this, "Notice",
                             "Select a user in the table.");
    return;
  }

  int userId = m_usersTable->item(row, 0)->text().toInt();
  User user = m_userController.getUserById(userId);

  QDialog dialog(this);
  dialog.setWindowTitle("Edit user");
  dialog.setMinimumWidth(350);

  QFormLayout *formLayout = new QFormLayout(&dialog);

  QLineEdit *nameInput = new QLineEdit(user.getName());
  formLayout->addRow("Name:", nameInput);

  QLineEdit *loginInput = new QLineEdit(user.getLogin());
  formLayout->addRow("Login:", loginInput);

  QLineEdit *passInput = new QLineEdit(user.getPassword());
  passInput->setEchoMode(QLineEdit::Password);
  formLayout->addRow("Password:", passInput);

  QComboBox *roleBox = new QComboBox();
  roleBox->addItem("Student", "student");
  roleBox->addItem("Teacher", "teacher");
  roleBox->addItem("Administrator", "admin");
  int roleIndex = roleBox->findData(user.getRole());
  if (roleIndex >= 0)
    roleBox->setCurrentIndex(roleIndex);
  formLayout->addRow("Role:", roleBox);

  QDialogButtonBox *buttons =
      new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
  formLayout->addRow(buttons);
  connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
  connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

  if (dialog.exec() == QDialog::Accepted) {
    if (!m_userController.updateUser(userId, nameInput->text().trimmed(),
                                     loginInput->text().trimmed(),
                                     passInput->text(),
                                     roleBox->currentData().toString())) {
      QMessageBox::warning(this, "Error",
                           "This login is already used by another user.");
      return;
    }
    refreshUsersTable();
    refreshDashboard();
  }
}

void AdminPanel::onDeleteUser() {
  int row = m_usersTable->currentRow();
  if (row < 0) {
    QMessageBox::information(this, "Notice",
                             "Select a user in the table.");
    return;
  }

  int userId = m_usersTable->item(row, 0)->text().toInt();
  QString userName = m_usersTable->item(row, 1)->text();

  QMessageBox::StandardButton reply = QMessageBox::question(
      this, "Confirm",
      "Delete user \"" + userName +
          "\"?\n"
          "All related grades and course enrollments will be removed.",
      QMessageBox::Yes | QMessageBox::No);

  if (reply == QMessageBox::Yes) {
    if (!m_userController.deleteUser(userId)) {
      QMessageBox::warning(
          this, "Cannot delete",
          "This teacher is assigned to courses. Assign another teacher "
          "or remove those courses first.");
      return;
    }
    refreshUsersTable();
    refreshDashboard();
  }
}

void AdminPanel::onAddCourse() {
  QList<User> teachers = m_userController.getUsersByRole("teacher");
  if (teachers.isEmpty()) {
    QMessageBox::information(
        this, "No teachers",
        "Create a user with the Teacher role first.");
    return;
  }

  QDialog dialog(this);
  dialog.setWindowTitle("Create course");
  dialog.setMinimumWidth(400);

  QFormLayout *formLayout = new QFormLayout(&dialog);

  QLineEdit *nameInput = new QLineEdit();
  nameInput->setPlaceholderText("Course title");
  formLayout->addRow("Title:", nameInput);

  QLineEdit *descInput = new QLineEdit();
  descInput->setPlaceholderText("Course description");
  formLayout->addRow("Description:", descInput);

  QComboBox *teacherBox = new QComboBox();
  for (const User &t : teachers) {
    teacherBox->addItem(t.getName(), t.getId());
  }
  formLayout->addRow("Teacher:", teacherBox);

  QDialogButtonBox *buttons =
      new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
  formLayout->addRow(buttons);
  connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
  connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

  if (dialog.exec() == QDialog::Accepted) {
    QString name = nameInput->text().trimmed();
    if (name.isEmpty()) {
      QMessageBox::warning(this, "Error", "Enter a course title.");
      return;
    }
    int teacherId = teacherBox->currentData().toInt();
    if (!m_courseController.addCourse(name, descInput->text().trimmed(),
                                      teacherId)) {
      QMessageBox::warning(this, "Error",
                           "Select a valid teacher.");
      return;
    }
    refreshCoursesTable();
    refreshDashboard();
  }
}

void AdminPanel::onEditCourse() {
  int row = m_coursesTable->currentRow();
  if (row < 0) {
    QMessageBox::information(this, "Notice", "Select a course in the table.");
    return;
  }

  int courseId = m_coursesTable->item(row, 0)->text().toInt();
  Course course = m_courseController.getCourseById(courseId);

  QDialog dialog(this);
  dialog.setWindowTitle("Edit course");
  dialog.setMinimumWidth(400);

  QFormLayout *formLayout = new QFormLayout(&dialog);

  QLineEdit *nameInput = new QLineEdit(course.getName());
  formLayout->addRow("Title:", nameInput);

  QLineEdit *descInput = new QLineEdit(course.getDescription());
  formLayout->addRow("Description:", descInput);

  QComboBox *teacherBox = new QComboBox();
  QList<User> teachersForEdit = m_userController.getUsersByRole("teacher");
  if (teachersForEdit.isEmpty()) {
    QMessageBox::information(
        this, "No teachers",
        "There are no teachers in the system; cannot edit the course.");
    return;
  }
  for (const User &t : teachersForEdit) {
    teacherBox->addItem(t.getName(), t.getId());
  }
  int idx = teacherBox->findData(course.getTeacherId());
  if (idx >= 0)
    teacherBox->setCurrentIndex(idx);
  formLayout->addRow("Teacher:", teacherBox);

  QDialogButtonBox *buttons =
      new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
  formLayout->addRow(buttons);
  connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
  connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

  if (dialog.exec() == QDialog::Accepted) {
    if (!m_courseController.updateCourse(courseId, nameInput->text().trimmed(),
                                         descInput->text().trimmed(),
                                         teacherBox->currentData().toInt())) {
      QMessageBox::warning(this, "Error",
                           "Select a valid teacher.");
      return;
    }
    refreshCoursesTable();
  }
}

void AdminPanel::onDeleteCourse() {
  int row = m_coursesTable->currentRow();
  if (row < 0) {
    QMessageBox::information(this, "Notice", "Select a course in the table.");
    return;
  }

  int courseId = m_coursesTable->item(row, 0)->text().toInt();
  QString courseName = m_coursesTable->item(row, 1)->text();

  QMessageBox::StandardButton reply =
      QMessageBox::question(this, "Confirm",
                            "Delete course \"" + courseName +
                                "\"?\n"
                                "All related grades and enrollments will be removed.",
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
    QMessageBox::information(this, "Notice",
                             "Select a course in the table first.");
    return;
  }

  int courseId = m_coursesTable->item(row, 0)->text().toInt();

  QDialog dialog(this);
  dialog.setWindowTitle("Enroll student in course");
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
    QMessageBox::information(this, "Info",
                             "All students are already enrolled in this course.");
    return;
  }

  formLayout->addRow("Student:", studentBox);

  QDialogButtonBox *buttons =
      new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
  formLayout->addRow(buttons);
  connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
  connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

  if (dialog.exec() == QDialog::Accepted) {
    int studentId = studentBox->currentData().toInt();
    if (!m_courseController.enrollStudent(studentId, courseId, "")) {
      QMessageBox::warning(
          this, "Enrollment",
          "This student is already enrolled in the selected course.");
      return;
    }
    refreshCoursesTable();
  }
}

void AdminPanel::onLogout() {
  LoginWindow *login = new LoginWindow();
  login->show();
  this->close();
}

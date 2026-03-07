#include "loginwindow.h"
#include "adminpanel.h"
#include "studentpanel.h"
#include "teacherpanel.h"
#include <QApplication>
#include <QFrame>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QScreen>
#include <QSpacerItem>
#include <QVBoxLayout>

LoginWindow::LoginWindow(QWidget *parent) : QWidget(parent) {
  setupUI();
  setWindowTitle("Study.Table() — Вход");
  setFixedSize(420, 620);

  // Центрируем окно на экране
  QScreen *screen = QApplication::primaryScreen();
  if (screen) {
    QRect screenGeometry = screen->geometry();
    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;
    move(x, y);
  }

  connect(m_loginButton, &QPushButton::clicked, this,
          &LoginWindow::onLoginClicked);
}

void LoginWindow::setupUI() {
  QVBoxLayout *mainLayout = new QVBoxLayout(this);
  mainLayout->setContentsMargins(40, 40, 40, 40);
  mainLayout->setSpacing(12);

  // Заголовок
  m_titleLabel = new QLabel("📚 Study.Table()");
  m_titleLabel->setObjectName("titleLabel");
  m_titleLabel->setAlignment(Qt::AlignCenter);
  mainLayout->addWidget(m_titleLabel);

  // Подзаголовок
  QLabel *subtitleLabel = new QLabel("CRM для образовательного центра");
  subtitleLabel->setObjectName("subtitleLabel");
  subtitleLabel->setAlignment(Qt::AlignCenter);
  mainLayout->addWidget(subtitleLabel);

  mainLayout->addSpacing(30);

  // Разделитель
  QFrame *line = new QFrame();
  line->setFrameShape(QFrame::HLine);
  line->setFrameShadow(QFrame::Sunken);
  mainLayout->addWidget(line);

  mainLayout->addSpacing(20);

  // Поле логина
  QLabel *loginLabel = new QLabel("Логин");
  loginLabel->setStyleSheet("font-weight: bold; font-size: 13px;");
  mainLayout->addWidget(loginLabel);

  m_loginInput = new QLineEdit();
  m_loginInput->setPlaceholderText("Введите логин...");
  m_loginInput->setMinimumHeight(40);
  mainLayout->addWidget(m_loginInput);

  mainLayout->addSpacing(8);

  // Поле пароля
  QLabel *passwordLabel = new QLabel("Пароль");
  passwordLabel->setStyleSheet("font-weight: bold; font-size: 13px;");
  mainLayout->addWidget(passwordLabel);

  m_passwordInput = new QLineEdit();
  m_passwordInput->setPlaceholderText("Введите пароль...");
  m_passwordInput->setEchoMode(QLineEdit::Password);
  m_passwordInput->setMinimumHeight(40);
  mainLayout->addWidget(m_passwordInput);

  mainLayout->addSpacing(8);

  // Сообщение об ошибке
  m_errorLabel = new QLabel("");
  m_errorLabel->setObjectName("errorLabel");
  m_errorLabel->setAlignment(Qt::AlignCenter);
  m_errorLabel->setVisible(false);
  mainLayout->addWidget(m_errorLabel);

  mainLayout->addSpacing(12);

  // Кнопка входа
  m_loginButton = new QPushButton("Войти");
  m_loginButton->setProperty("primary", true);
  m_loginButton->setMinimumHeight(44);
  m_loginButton->setCursor(Qt::PointingHandCursor);
  m_loginButton->setStyleSheet("QPushButton { font-size: 16px; font-weight: "
                               "bold; border-radius: 10px; }");
  mainLayout->addWidget(m_loginButton);

  mainLayout->addStretch();

  // Блок с тестовыми аккаунтами
  QFrame *hintsFrame = new QFrame();
  hintsFrame->setObjectName("hintsFrame");
  hintsFrame->setStyleSheet("QFrame#hintsFrame { background-color: #181825; "
                            "border: 1px solid #313244; "
                            "border-radius: 10px; }");

  QVBoxLayout *hintsLayout = new QVBoxLayout(hintsFrame);
  hintsLayout->setContentsMargins(12, 12, 12, 12);

  QLabel *accountsLabel = new QLabel();
  accountsLabel->setTextFormat(Qt::RichText);
  accountsLabel->setText(
      "<div style='margin-bottom: 6px;'><b style='color: #a6adc8; font-size: "
      "12px;'>Тестовые аккаунты:</b></div>"
      "<table border='0' cellspacing='5' cellpadding='0'>"
      "<tr><td><b style='color: #f38ba8; font-size: 11px;'>Admin:</b></td>"
      "    <td><code style='color: #cdd6f4; font-size: 11px; font-family: "
      "monospace;'>admin / admin123</code></td></tr>"
      "<tr><td><b style='color: #f9e2af; font-size: 11px;'>Teacher:</b></td>"
      "    <td><code style='color: #cdd6f4; font-size: 11px; font-family: "
      "monospace;'>teacher1 / teach123</code></td></tr>"
      "<tr><td><b style='color: #a6e3a1; font-size: 11px;'>Student:</b></td>"
      "    <td><code style='color: #cdd6f4; font-size: 11px; font-family: "
      "monospace;'>student1 / stud123</code></td></tr>"
      "</table>");
  accountsLabel->setStyleSheet("border: none; background: transparent;");

  hintsLayout->addWidget(accountsLabel);
  mainLayout->addWidget(hintsFrame);

  // Enter нажат в поле пароля
  connect(m_passwordInput, &QLineEdit::returnPressed, m_loginButton,
          &QPushButton::click);
  connect(m_loginInput, &QLineEdit::returnPressed, m_passwordInput,
          static_cast<void (QLineEdit::*)()>(&QLineEdit::setFocus));
}

void LoginWindow::onLoginClicked() {
  QString login = m_loginInput->text().trimmed();
  QString password = m_passwordInput->text();

  if (login.isEmpty() || password.isEmpty()) {
    m_errorLabel->setText("⚠ Заполните все поля");
    m_errorLabel->setVisible(true);
    return;
  }

  if (m_authController.authenticate(login, password)) {
    User user = m_authController.getCurrentUser();

    // Полиморфная маршрутизация по роли
    if (user.getRole() == "admin") {
      AdminPanel *panel = new AdminPanel(user);
      panel->show();
    } else if (user.getRole() == "teacher") {
      TeacherPanel *panel = new TeacherPanel(user);
      panel->show();
    } else if (user.getRole() == "student") {
      StudentPanel *panel = new StudentPanel(user);
      panel->show();
    }

    this->close(); // Закрываем окно входа
  } else {
    m_errorLabel->setText("❌ Неверный логин или пароль");
    m_errorLabel->setVisible(true);
    m_passwordInput->clear();
    m_passwordInput->setFocus();
  }
}

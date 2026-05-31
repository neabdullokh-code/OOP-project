#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include "../controllers/authcontroller.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class LoginWindow : public QWidget {
  Q_OBJECT

public:
  explicit LoginWindow(QWidget *parent = nullptr);

private slots:
  void onLoginClicked();

private:
  void setupUI();

  QLineEdit *m_loginInput;
  QLineEdit *m_passwordInput;
  QPushButton *m_loginButton;
  QLabel *m_errorLabel;
  QLabel *m_titleLabel;

  AuthController m_authController;
};

#endif // LOGINWINDOW_H

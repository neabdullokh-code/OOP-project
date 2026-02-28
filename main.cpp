#include "views/loginwindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  app.setApplicationName("Study.Table()");

  // Загрузка стилей из ресурсов
  QFile styleFile(":/resources/styles/main.qss");
  if (styleFile.open(QFile::ReadOnly | QFile::Text)) {
    QString style = styleFile.readAll();
    app.setStyleSheet(style);
    styleFile.close();
  }

  // Показываем окно входа
  LoginWindow loginWindow;
  loginWindow.show();

  return app.exec();
}

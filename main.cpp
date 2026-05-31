#include <QApplication>
#include "loginwindow.h"
#include "filemanager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    FileManager fileManager;
    fileManager.ensureDefaultAdmin();
    fileManager.loadAll();

    LoginWindow loginWindow(&fileManager);
    loginWindow.show();

    return app.exec();
}

#include <QApplication>
#include "views/loginwindow.h"
#include "core/databasemanager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    DatabaseManager databaseManager;
    databaseManager.ensureDefaultAdmin();
    databaseManager.loadAll();

    LoginWindow loginWindow(&databaseManager);
    loginWindow.show();

    return app.exec();
}

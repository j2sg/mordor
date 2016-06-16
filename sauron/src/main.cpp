#include <QApplication>
#include "global.h"
#include "mainwindow.h"

void setupApplication(QApplication *app);

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    setupApplication(&app);

    MainWindow mainWindow;

    mainWindow.show();

    return app.exec();

}

void setupApplication(QApplication *app)
{
    if(!app)
        return;

    app -> setOrganizationName(ORGANIZATION_NAME);
    app -> setOrganizationDomain(ORGANIZATION_DOMAIN);
    app -> setApplicationName(APPLICATION_NAME);
    app -> setApplicationVersion(APPLICATION_VERSION);
}

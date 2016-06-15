#include "mainwindow.h"
#include "centralwidget.h"
#include "global.h"
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QLabel>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    createWidgets();
    createConnections();
    setWindowTitle(tr("S4ur0n"));
    //setWindowIcon(QIcon(""));

    _connected = false;
}

void MainWindow::connectToCC()
{

}

void MainWindow::disconnectFromCC()
{

}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About %1").arg(APPLICATION_NAME),
                             tr("<h2>%1 %2</h2>"
                                "<h3>GUI para botmaster de la botnet Mordor</h3>"
                                "<p>(C) %3 %4 <a href= \"mailto:%5\" >%5</a></p>"
                                "<p><a href= \"%6\" >%6</a></p>"
                                "<p>Licensed under <a href=\"http://www.gnu.org/licenses/gpl.html\" >GNU General Public License version 3</a></p>")
                             .arg(APPLICATION_NAME_LONG)
                             .arg(APPLICATION_VERSION)
                             .arg(APPLICATION_YEARS)
                             .arg(AUTHOR_NAME)
                             .arg(AUTHOR_EMAIL)
                             .arg(APPLICATION_WEB));
}

void MainWindow::createWidgets()
{
    createCentralWidget();
    createActions();
    createMenus();
    createToolBar();
    createStatusBar();
}

void MainWindow::createCentralWidget()
{
    _centralWidget = new CentralWidget;

    setCentralWidget(_centralWidget);
}

void MainWindow::createActions()
{
    _connectToCCAction = new QAction(tr("&Conectar a CC..."), this);
    //_connectToCCAction->setIcon(QIcon(""));
    _connectToCCAction -> setStatusTip(tr("Establecer conexion con el CC de la Botnet"));

    _disconnectFromCCAction = new QAction(tr("&Desconectar del CC"), this);
    //_disconnectFromCCAction->setIcon(QIcon(""));
    _disconnectFromCCAction -> setStatusTip(tr("Cerrar conexion con el CC"));

    _exitAction = new QAction(tr("&Salir"), this);
    //_exitAction->setIcon(QIcon(""));
    _exitAction -> setStatusTip(tr("Salir de la aplicacion"));

    _aboutAction = new QAction(tr("Acerca de"), this);
    //_aboutAction->setIcon(QIcon(""));
    _aboutAction -> setStatusTip(tr("Muestra informacion acerca de la aplicacion"));
}

void MainWindow::createMenus()
{
    _applicationMenu = menuBar() -> addMenu(tr("A&plicacion"));
    _applicationMenu -> addAction(_connectToCCAction);
    _applicationMenu -> addAction(_disconnectFromCCAction);
    _applicationMenu -> addAction(_exitAction);

    _attackMenu = menuBar() -> addMenu(tr("&Ataque"));

    _helpMenu = menuBar() -> addMenu(tr("A&yuda"));
    _helpMenu -> addAction(_aboutAction);
}

void MainWindow::createToolBar()
{
    _applicationToolBar = addToolBar(tr("Aplicacion"));
    _applicationToolBar -> addAction(_connectToCCAction);
    _applicationToolBar -> addAction(_disconnectFromCCAction);

    _attackToolBar = addToolBar(tr("Ataque"));
}

void MainWindow::createStatusBar()
{
    _ccLabel = new QLabel;

    statusBar() -> addWidget(_ccLabel);
}

void MainWindow::createConnections()
{
    connect(_connectToCCAction, SIGNAL(triggered()), this, SLOT(connectToCC()));
    connect(_disconnectFromCCAction, SIGNAL(triggered()), this, SLOT(disconnectFromCC()));
    connect(_exitAction, SIGNAL(triggered()), this, SLOT(close()));
    connect(_aboutAction, SIGNAL(triggered()), this, SLOT(about()));
}

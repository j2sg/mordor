#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "attack.h"

class CentralWidget;
class QAction;
class QMenu;
class QToolBar;
class QLabel;
class XmppClient;
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
private:
    void createWidgets();
    void createCentralWidget();
    void createActions();
    void createMenus();
    void createToolBar();
    void createStatusBar();
    void createConnections();
    void setConnected(bool connected);
    void setAttackInProgress(bool inProgress, const QString& target = "");
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
    QLabel *_ccLabel;

    XmppClient *_xmppClient;
    bool _connected;
    Attack _attack;
};

#endif // MAINWINDOW_H

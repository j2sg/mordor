#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void about();
    void readyOnXmppClient();
    void disconnectedOnXmppClient();
    void responseReceivedOnXmppClient(const Message& response);
private:
    void createWidgets();
    void createCentralWidget();
    void createActions();
    void createMenus();
    void createToolBar();
    void createStatusBar();
    void createConnections();
    void setConnected(bool connected);
    bool verifyExit();

    CentralWidget *_centralWidget;
    QAction *_connectToCCAction;
    QAction *_disconnectFromCCAction;
    QAction *_exitAction;
    QAction *_aboutAction;
    QMenu *_applicationMenu;
    QMenu *_attackMenu;
    QMenu *_helpMenu;
    QToolBar *_applicationToolBar;
    QToolBar *_attackToolBar;
    QLabel *_ccLabel;

    XmppClient *_xmppClient;
    bool _connected;
};

#endif // MAINWINDOW_H

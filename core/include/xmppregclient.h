#ifndef XMPPREGCLIENT_H
#define XMPPREGCLIENT_H

#include "core_global.h"
#include <QObject>
#include <QTcpSocket>

class CORE_EXPORT XmppRegClient : public QObject
{
    Q_OBJECT
public:
    XmppRegClient(const QString& server, QObject *parent = 0);
signals:
    void success(const QString& server, const QString& username, const QString& password);
    void failure(const QString& server, const QString& username, const QString& password);
public slots:
    void sendRegistrationRequest(const QString& username, const QString& password);
private slots:
    void connectedOnSocket();
    void disconnectedOnSocket();
    void readyReadOnSocket();
    void errorOnSocket(QAbstractSocket::SocketError error);
private:
    void createConnections();

    QString _server;
    QTcpSocket *_socket;
    static const int _port = 5222;
};

#endif // XMPPREGCLIENT_H

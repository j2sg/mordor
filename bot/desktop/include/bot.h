#ifndef BOT_H
#define BOT_H

#include <qxmpp/QXmppClient.h>

class Bot : public QXmppClient
{
    Q_OBJECT
public:
    static Bot *instance();
private:
    Bot(QObject *parent = 0);
    ~Bot() {}
};

#endif // BOT_H

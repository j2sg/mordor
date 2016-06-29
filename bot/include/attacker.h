#ifndef ATTACKER_H
#define ATTACKER_H

#include <QObject>
#include <QString>

#define RPS_BY_DEFAULT 5

class QNetworkAccessManager;
class QNetworkReply;

class Attacker : public QObject
{
    Q_OBJECT
public:
    Attacker(ushort requestPerSecond = RPS_BY_DEFAULT);
    void setTarget(const QString &target);
signals:
    void done();
public slots:
    void attack();
private slots:
    void sendHttpGetRequestToTarget();
private:
    QString _target;
    ushort _requetsPerSecond;
    QNetworkAccessManager *_networkAccessManager;
};

#endif // ATTACKER_H

#include "attacker.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTimer>

Attacker::Attacker(ushort requestPerSecond) : _requetsPerSecond(requestPerSecond)
{
    _networkAccessManager = new QNetworkAccessManager(this);

    createConnections();
}

void Attacker::setTarget(const QString &target)
{
    _target = target;
}

void Attacker::attack()
{
    QTimer::singleShot(static_cast<int>(1000.0 / _requetsPerSecond), this, SLOT(sendHttpGetRequestToTarget()));
}

void Attacker::sendHttpGetRequestToTarget()
{
    _networkAccessManager -> get(QNetworkRequest(QUrl(_target)));

    emit done();
}

void Attacker::finishedOnNetworkAccessManager(QNetworkReply *reply)
{
    reply -> deleteLater();
}

void Attacker::createConnections()
{
    connect(_networkAccessManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(finishedOnNetworkAccessManager(QNetworkReply*)));
}

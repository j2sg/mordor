#ifndef BOTNETMODEL_H
#define BOTNETMODEL_H

#include <QAbstractTableModel>
#include <QMap>
#include <QString>

typedef enum ColumnBotEnum
{
    ColumnBotId,
    ColumnBotIP,
    ColumnBotOS,
    ColumnBotStatus,
    ColumnBotCount
} ColumnBot;

typedef enum ColumnAttackEnum
{
    ColumnAttackId,
    ColumnAttackUptime,
    ColumnAttackBots
} ColumnAttack;

class Bot;

class BotnetModel : public QAbstractTableModel
{
public:
    BotnetModel(QMap<QString, Bot *> *bots, QObject *parent = 0);
    ~BotnetModel();
    void setBots(QMap<QString, Bot *> *bots);
    QMap<QString, Bot *> *bots();
    bool insertBot(Bot *bot);
    bool modifyBot(const QString& id);
    bool removeBot(const QString& id);
    int rowCount(const QModelIndex& parent) const;
    int columnCount(const QModelIndex& parent) const;
    QVariant data(const QModelIndex& index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
private:
    QString botAt(int offset) const;

    QMap<QString, Bot *> *_bots;
};

#endif // BOTNETMODEL_H

#ifndef BOTNETMODEL_H
#define BOTNETMODEL_H

#include <QAbstractTableModel>
#include <QList>

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
    BotnetModel(QList<Bot *> *bots, QObject *parent = 0);
    ~BotnetModel();
    void setBots(QList<Bot *> *bots);
    QList<Bot *> *bots();
    bool insertBot(int k, Bot *bot);
    bool modifyBot(int k);
    bool removeBot(int k);
    int rowCount(const QModelIndex& parent) const;
    int columnCount(const QModelIndex& parent) const;
    QVariant data(const QModelIndex& index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
private:
    QList<Bot *> *_bots;
};

#endif // BOTNETMODEL_H

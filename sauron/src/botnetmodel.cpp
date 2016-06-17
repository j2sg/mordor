#include "botnetmodel.h"
#include "bot.h"
#include "types.h"
#include <QColor>

BotnetModel::BotnetModel(QList<Bot *> *bots, QObject *parent)
    : QAbstractTableModel(parent), _bots(bots) {}

BotnetModel::~BotnetModel()
{
    if(_bots) {
        foreach(Bot *bot, *_bots)
            delete bot;

        delete _bots;
    }
}

void BotnetModel::setBots(QList<Bot *> *bots)
{
    beginResetModel();

    if(_bots) {
        foreach(Bot *bot, *_bots)
            delete bot;

        delete _bots;
    }

    _bots = bots;

    endResetModel();
}

QList<Bot *> *BotnetModel::bots()
{
    return _bots;
}

bool BotnetModel::insertBot(int k, Bot *bot)
{
    if(k < 0  || k > _bots -> size())
        return false;

    beginResetModel();

    _bots -> insert(k, bot);

    endResetModel();

    return true;
}

bool BotnetModel::modifyBot(int k)
{
    if(k < 0  || k > _bots -> size())
        return false;

    beginResetModel();
    endResetModel();

    return true;
}

bool BotnetModel::removeBot(int k)
{
    if(k < 0  || k > _bots -> size())
        return false;

    beginResetModel();

    delete _bots -> at(k);
    _bots -> removeAt(k);

    endResetModel();

    return true;
}

int BotnetModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);

    return _bots -> size();
}

int BotnetModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);

    return ColumnBotCount;
}

QVariant BotnetModel::data(const QModelIndex& index, int role) const
{
    if(index.isValid()) {
        if(role == Qt::TextAlignmentRole) {
            switch(index.column()) {
            case ColumnBotId:
            case ColumnBotStatus:
                return int(Qt::AlignCenter);
            default:
                return int(Qt::AlignLeft | Qt::AlignVCenter);
            }
        } else if(role == Qt::DisplayRole) {
            Bot *bot = _bots -> at(index.row());

            switch(index.column()) {
            case ColumnBotId:
                return bot -> id();
            case ColumnBotIP:
                return bot -> ip();
            case ColumnBotOS:
                return bot -> os();
            case ColumnBotStatus:
                return bot -> state() == WaitingForCommand ? tr("Esperando") : tr("Ataque");
            }
        } else if(role == Qt::ForegroundRole) {
            Bot *bot = _bots -> at(index.row());

            return bot -> state() != Attack ? QColor(Qt::black) : QColor(Qt::red);
        }
    }

    return QVariant();
}

QVariant BotnetModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole) {
        if(orientation == Qt::Horizontal) {
            switch(section) {
            case ColumnBotId:
                return tr("ID");
            case ColumnBotIP:
                return tr("IP");
            case ColumnBotOS:
                return tr("SO");
            case ColumnBotStatus:
                return tr("Estado");
            }
        }
    }

    return QVariant();
}
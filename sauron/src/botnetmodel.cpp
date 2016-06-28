#include "botnetmodel.h"
#include "bot.h"
#include <QColor>

BotnetModel::BotnetModel(QMap<QString, Bot *> *bots, QObject *parent)
    : QAbstractTableModel(parent), _bots(bots) {}

BotnetModel::~BotnetModel()
{
    if(_bots) {
        foreach(Bot *bot, *_bots)
            delete bot;

        delete _bots;
    }
}

void BotnetModel::setBots(QMap<QString, Bot *> *bots)
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

QMap<QString, Bot *> *BotnetModel::bots()
{
    return _bots;
}

bool BotnetModel::insertBot(const QString& roomId, Bot *bot)
{
    if(_bots -> contains(roomId))
        return false;

    beginResetModel();

    _bots -> insert(roomId, bot);

    endResetModel();

    return true;
}

bool BotnetModel::modifyBot(const QString& roomId)
{
    if(!_bots -> contains(roomId))
        return false;

    beginResetModel();
    endResetModel();

    return true;
}

bool BotnetModel::removeBot(const QString& roomId)
{
    if(!_bots -> contains(roomId))
        return false;

    beginResetModel();

    delete _bots -> value(roomId);
    _bots -> remove(roomId);

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
            Bot *bot = _bots -> value(botAt(index.row()));

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
            Bot *bot = _bots -> value(botAt(index.row()));

            return bot -> state() != AttackInProgress ? QColor(Qt::black) : QColor(Qt::red);
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

QString BotnetModel::botAt(int offset) const
{
    return (_bots -> begin() + offset).key();
}

/**
 *  This file is part of Mordor.
 *
 *  Copyright (c) 2016 Juan Jose Salazar Garcia jjslzgc@gmail.com
 *
 *  Mordor is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Mordor is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Mordor.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/

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
            case ColumnBotIP:
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

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

class Bot;

class BotnetModel : public QAbstractTableModel
{
public:
    BotnetModel(QMap<QString, Bot *> *bots, QObject *parent = 0);
    ~BotnetModel();
    void setBots(QMap<QString, Bot *> *bots);
    QMap<QString, Bot *> *bots();
    bool insertBot(const QString& roomId, Bot *bot);
    bool modifyBot(const QString& roomId);
    bool removeBot(const QString& roomId);
    int rowCount(const QModelIndex& parent) const;
    int columnCount(const QModelIndex& parent) const;
    QVariant data(const QModelIndex& index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
private:
    QString botAt(int offset) const;

    QMap<QString, Bot *> *_bots;
};

#endif // BOTNETMODEL_H

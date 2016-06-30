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

#include "centralwidget.h"
#include "botnetmodel.h"
#include "bot.h"
#include <QTableView>
#include <QHeaderView>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QTime>

CentralWidget::CentralWidget(QWidget *parent) : QWidget(parent)
{
    createWidgets();
    createConnections();
}

CentralWidget::~CentralWidget()
{
    delete _botnetModel;
}

Bot *CentralWidget::bot(const QString roomId)
{
    return _botnetModel -> bots() -> value(roomId);
}

void CentralWidget::writeEvent(const QString& event)
{
    _eventsTextEdit -> append(QString("[%1] %2").arg(QTime::currentTime().toString()).arg(event));
}

void CentralWidget::insertBot(const QString& roomId, Bot *bot)
{
    _botnetModel -> insertBot(roomId, bot);
}

void CentralWidget::modifyBot(const QString& roomId)
{
    _botnetModel -> modifyBot(roomId);
}

void CentralWidget::removeBot(const QString& roomId)
{
    _botnetModel -> removeBot(roomId);
}

void CentralWidget::createWidgets()
{
    _botnetTableView = new QTableView;
    _botnetModel = new BotnetModel(new QMap<QString, Bot *>());
    _botnetTableView -> setModel(_botnetModel);
    _botnetTableView -> setAlternatingRowColors(true);
    _botnetTableView -> setShowGrid(false);
    _botnetTableView -> setSelectionMode(QAbstractItemView::NoSelection);
    _botnetTableView -> setFocusPolicy(Qt::NoFocus);
    _botnetTableView -> setColumnWidth(ColumnBotId, COLUMN_BOTNET_ID_WIDTH);
    _botnetTableView -> setColumnWidth(ColumnBotIP, COLUMN_BOTNET_IP_WIDTH);
    _botnetTableView -> setColumnWidth(ColumnBotOS, COLUMN_BOTNET_OS_WIDTH);
    _botnetTableView -> setColumnWidth(ColumnBotStatus, COLUMN_BOTNET_IP_STATE);
    _botnetTableView -> horizontalHeader() -> setSectionResizeMode(QHeaderView::Fixed);
    _botnetTableView -> horizontalHeader() -> setSectionResizeMode(ColumnBotOS, QHeaderView::Stretch);

    _eventsTextEdit = new QTextEdit;
    _eventsTextEdit -> setFixedHeight(EVENTS_HEIGHT);

    QVBoxLayout *mainLayout = new QVBoxLayout;

    mainLayout -> addWidget(_botnetTableView);
    mainLayout -> addWidget(_eventsTextEdit);

    setLayout(mainLayout);
}

void CentralWidget::createConnections()
{

}

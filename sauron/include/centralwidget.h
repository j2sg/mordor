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

#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>

#define COLUMN_BOTNET_ID_WIDTH 250
#define COLUMN_BOTNET_IP_WIDTH 150
#define COLUMN_BOTNET_OS_WIDTH 200
#define COLUMN_BOTNET_IP_STATE 100
#define EVENTS_HEIGHT 150

class QTableView;
class QTextEdit;
class BotnetModel;
class Bot;

class CentralWidget : public QWidget
{
    Q_OBJECT
public:
    CentralWidget(QWidget *parent = 0);
    ~CentralWidget();
    Bot *bot(const QString roomId);
    void writeEvent(const QString& event);
public slots:
    void insertBot(const QString& roomId, Bot *bot);
    void modifyBot(const QString& roomId);
    void removeBot(const QString& roomId);
private:
    void createWidgets();
    void createConnections();

    QTableView *_botnetTableView;
    BotnetModel *_botnetModel;
    QTextEdit *_eventsTextEdit;
};

#endif // CENTRALWIDGET_H

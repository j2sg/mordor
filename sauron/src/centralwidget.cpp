#include "centralwidget.h"
#include "botnetmodel.h"
#include "bot.h"
#include <QTableView>
#include <QTabWidget>
#include <QTextEdit>
#include <QVBoxLayout>

CentralWidget::CentralWidget(QWidget *parent) : QWidget(parent)
{
    createWidgets();
    createConnections();
}

CentralWidget::~CentralWidget()
{
    delete _botnetModel;
}

void CentralWidget::addBot(Bot *bot)
{
    if(!_botnetModel -> bots() -> contains(bot -> id()))
        _botnetModel -> insertBot(bot);
    else {
        Bot *botOnModel = _botnetModel -> bots() -> value(bot -> id());

        *botOnModel = *bot;

        _botnetModel -> modifyBot(bot -> id());
    }
}

void CentralWidget::removeBot(const QString& id)
{
    _botnetModel -> removeBot(id);
}

void CentralWidget::createWidgets()
{
    _botnetTableView = new QTableView;
    _botnetModel = new BotnetModel(new QMap<QString, Bot *>());
    _botnetTableView -> setModel(_botnetModel);

    _tabWidget = new QTabWidget;

    _attacksTableView = new QTableView;

    _eventsTextEdit = new QTextEdit;

    _tabWidget -> addTab(_attacksTableView, tr("Ataques"));
    _tabWidget -> addTab(_eventsTextEdit,tr("Eventos"));

    QVBoxLayout *mainLayout = new QVBoxLayout;

    mainLayout -> addWidget(_botnetTableView);
    mainLayout -> addWidget(_tabWidget);

    setLayout(mainLayout);
}

void CentralWidget::createConnections()
{

}

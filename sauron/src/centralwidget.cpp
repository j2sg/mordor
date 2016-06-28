#include "centralwidget.h"
#include "botnetmodel.h"
#include "bot.h"
#include <QTableView>
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

void CentralWidget::addBot(const QString& roomId, Bot *bot)
{
    if(!_botnetModel -> bots() -> contains(roomId))
        _botnetModel -> insertBot(roomId, bot);
    else {
        Bot *botOnModel = _botnetModel -> bots() -> value(roomId);

        *botOnModel = *bot;

        _botnetModel -> modifyBot(roomId);
    }
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

    _eventsTextEdit = new QTextEdit;

    QVBoxLayout *mainLayout = new QVBoxLayout;

    mainLayout -> addWidget(_botnetTableView);
    mainLayout -> addWidget(_eventsTextEdit);

    setLayout(mainLayout);
}

void CentralWidget::createConnections()
{

}

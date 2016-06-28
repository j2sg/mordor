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

Bot *CentralWidget::bot(const QString roomId)
{
    return _botnetModel -> bots() -> value(roomId);
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

    _eventsTextEdit = new QTextEdit;

    QVBoxLayout *mainLayout = new QVBoxLayout;

    mainLayout -> addWidget(_botnetTableView);
    mainLayout -> addWidget(_eventsTextEdit);

    setLayout(mainLayout);
}

void CentralWidget::createConnections()
{

}

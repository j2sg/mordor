#include "centralwidget.h"
#include "botnetmodel.h"
#include "bot.h"
#include <QTableView>
#include <QHeaderView>
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

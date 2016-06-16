#include "centralwidget.h"
#include <QTableView>
#include <QTabWidget>
#include <QTextEdit>
#include <QVBoxLayout>

CentralWidget::CentralWidget(QWidget *parent) : QWidget(parent)
{
    createWidgets();
    createConnections();
}

void CentralWidget::createWidgets()
{
    _botnetTableView = new QTableView;

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

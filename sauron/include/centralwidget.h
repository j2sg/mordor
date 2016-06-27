#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>

class QTableView;
class QTabWidget;
class QTextEdit;
class BotnetModel;
class Bot;

class CentralWidget : public QWidget
{
    Q_OBJECT
public:
    CentralWidget(QWidget *parent = 0);
    ~CentralWidget();
public slots:
    void addBot(Bot *bot);
    void removeBot(const QString& id);
private:
    void createWidgets();
    void createConnections();

    QTableView *_botnetTableView;
    BotnetModel *_botnetModel;
    QTabWidget *_tabWidget;
    QTableView *_attacksTableView;
    QTextEdit *_eventsTextEdit;
};

#endif // CENTRALWIDGET_H

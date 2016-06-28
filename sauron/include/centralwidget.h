#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>

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
public slots:
    void addBot(const QString& roomId, Bot *bot);
    void removeBot(const QString& roomId);
private:
    void createWidgets();
    void createConnections();

    QTableView *_botnetTableView;
    BotnetModel *_botnetModel;
    QTextEdit *_eventsTextEdit;
};

#endif // CENTRALWIDGET_H

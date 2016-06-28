#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>

#define COLUMN_BOTNET_ID_WIDTH 200
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

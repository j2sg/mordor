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
    Bot *bot(const QString roomId);
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

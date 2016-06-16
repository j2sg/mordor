#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>

class QTableView;
class QTabWidget;
class QTextEdit;

class CentralWidget : public QWidget
{
    Q_OBJECT
public:
    CentralWidget(QWidget *parent = 0);
private:
    void createWidgets();
    void createConnections();

    QTableView *_botnetTableView;
    QTabWidget *_tabWidget;
    QTableView *_attacksTableView;
    QTextEdit *_eventsTextEdit;
};

#endif // CENTRALWIDGET_H

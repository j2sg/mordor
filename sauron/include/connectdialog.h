#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QDialog>

class QLabel;
class QLineEdit;
class QPushButton;

class ConnectDialog : public QDialog
{
    Q_OBJECT
public:
    ConnectDialog(QWidget *parent = 0);
    void done(int result);
    QString domain() const;
    QString username() const;
    QString password() const;
private slots:
    void textChangedOnLineEdit();
private:
    void createWidgets();
    void createConnections();

    QLabel *_domainLabel;
    QLineEdit *_domainLineEdit;
    QLabel *_usernameLabel;
    QLineEdit *_usernameLineEdit;
    QLabel *_passwordLabel;
    QLineEdit *_passwordLineEdit;
    QPushButton *_connectButton;
    QPushButton *_cancelButton;

    QString _domain;
    QString _username;
    QString _password;
};

#endif // CONNECTDIALOG_H

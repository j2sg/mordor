#include "connectdialog.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

ConnectDialog::ConnectDialog(QWidget *parent) : QDialog(parent)
{
    createWidgets();
    createConnections();
    setWindowTitle(tr("Conectar a CC"));
    setFixedSize(sizeHint());
}

void ConnectDialog::done(int result)
{
    if(result) {
        _domain = _domainLineEdit -> text();
        _username = _usernameLineEdit -> text();
        _password = _passwordLineEdit -> text();
    }

    QDialog::done(result);
}

QString ConnectDialog::domain() const
{
    return _domain;
}

QString ConnectDialog::username() const
{
    return _username;
}

QString ConnectDialog::password() const
{
    return _password;
}

void ConnectDialog::textChangedOnLineEdit()
{
    _connectButton -> setEnabled(!_domainLineEdit -> text().isEmpty() &&
                                 !_usernameLineEdit -> text().isEmpty() &&
                                 !_passwordLineEdit -> text().isEmpty());
}

void ConnectDialog::createWidgets()
{
    _domainLabel = new QLabel(tr("&Servidor:"));
    _domainLineEdit = new QLineEdit;
    _domainLabel -> setBuddy(_domainLineEdit);

    _usernameLabel = new QLabel(tr("&Usuario:"));
    _usernameLineEdit = new QLineEdit;
    _usernameLabel -> setBuddy(_usernameLineEdit);

    _passwordLabel = new QLabel(tr("&Password:"));
    _passwordLineEdit = new QLineEdit;
    _passwordLineEdit -> setEchoMode(QLineEdit::Password);
    _passwordLabel -> setBuddy(_passwordLineEdit);

    _connectButton = new QPushButton(tr("&Conectar"));
    _connectButton -> setDefault(true);
    _connectButton -> setEnabled(false);

    _cancelButton = new QPushButton(tr("Cancel"));

    QGridLayout *topLayout = new QGridLayout;

    topLayout -> addWidget(_domainLabel, 0, 0, 1, 1);
    topLayout -> addWidget(_domainLineEdit, 0, 1, 1, 1);
    topLayout -> addWidget(_usernameLabel, 1, 0, 1, 1);
    topLayout -> addWidget(_usernameLineEdit, 1, 1, 1, 1);
    topLayout -> addWidget(_passwordLabel, 2, 0, 1, 1);
    topLayout -> addWidget(_passwordLineEdit, 2, 1, 1, 1);

    QHBoxLayout *bottomLayout = new QHBoxLayout;

    bottomLayout -> addWidget(_connectButton);
    bottomLayout -> addWidget(_cancelButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;

    mainLayout -> addLayout(topLayout);
    mainLayout -> addLayout(bottomLayout);

    setLayout(mainLayout);
}

void ConnectDialog::createConnections()
{
    connect(_domainLineEdit, SIGNAL(textChanged(QString)), this, SLOT(textChangedOnLineEdit()));
    connect(_usernameLineEdit, SIGNAL(textChanged(QString)), this, SLOT(textChangedOnLineEdit()));
    connect(_passwordLineEdit, SIGNAL(textChanged(QString)), this, SLOT(textChangedOnLineEdit()));
    connect(_connectButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(_cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

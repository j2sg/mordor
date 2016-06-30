/**
 *  This file is part of Mordor.
 *
 *  Copyright (c) 2016 Juan Jose Salazar Garcia jjslzgc@gmail.com
 *
 *  Mordor is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Mordor is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Mordor.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/

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

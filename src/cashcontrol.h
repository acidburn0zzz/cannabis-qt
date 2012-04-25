/*
    Cannabis-qt
    Copyright (C) 2012 Karasu

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CASHCONTROL_H
#define CASHCONTROL_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QDialogButtonBox>
#include <QGroupBox>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QTableView>
#include <QHeaderView>
#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSqlError>
#include <QMessageBox>
#include <QDateEdit>
#include <QPrintDialog>
#include <QTextDocument>
#include <QPrinter>

class CashControl : public QWidget
{
    Q_OBJECT
public:
    explicit CashControl(QWidget *parent = 0);

    QDialogButtonBox *buttonBox;

    void resizeTableViewToContents(void);

    // bool save(void);
    void clear(void);

protected:
    QDateEdit *dataInicial;
    QDateEdit *dataFinal;

    QTableView *tableView;

    QPushButton *printButton;

signals:
    
public slots:
    void onHelp();
    void onShow();
    void onPrint();

};

#endif // CASHCONTROL_H

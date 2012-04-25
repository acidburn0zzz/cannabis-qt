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

#ifndef MEMBERS_H
#define MEMBERS_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QDialogButtonBox>
#include <QGroupBox>
#include <QSqlTableModel>
#include <QTableView>
#include <QHeaderView>
#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSqlError>
#include <QMessageBox>
#include <QInputDialog>
#include <QSqlQuery>

class Members : public QWidget
{
    Q_OBJECT
public:
    explicit Members(QWidget *parent = 0);

    QDialogButtonBox *buttonBox;

    void resizeTableViewToContents(void);

    bool save(bool showMessage=true);

protected:
    QLineEdit *filterLineEdit;

    QTableView *tableView;

    bool isDirty;

    void setDirtyFlag(bool status);

    void createModel(QSqlTableModel *model);

signals:
    
public slots:
    void addNewMember();
    void deleteMember();
    void onFilter();
    void onClearFilter();

    void onApply();
    void onCancel();
    void onHelp();

    void onDataChanged(QModelIndex , QModelIndex );
};

#endif // MEMBERS_H

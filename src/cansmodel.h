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

#ifndef CANSMODEL_H
#define CANSMODEL_H

#include <QAbstractTableModel>
#include <QDate>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSqlRecord>
#include <QSqlQueryModel>
#include <QMap>

class CansModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    explicit CansModel(QObject *parent = 0);
    ~CansModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    QMap<int,int> *ids;

signals:

public slots:
};

#endif // CANSMODEL_H

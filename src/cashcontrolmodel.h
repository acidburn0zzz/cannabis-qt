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

#ifndef CASHCONTROLMODEL_H
#define CASHCONTROLMODEL_H

#include <QAbstractTableModel>
#include <QDate>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QMap>
#include <QList>
#include <QStringList>
#include <QSqlDatabase>

class CashControlModel : public QSqlTableModel
{
    Q_OBJECT
public:
    explicit CashControlModel(QObject *parent = 0, QSqlDatabase db = QSqlDatabase());
    ~CashControlModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    void setDates(QString dataInicial, QString dataFinal);

    QHash <int, QStringList> myData;

    void clear();

signals:
    
public slots:
    
};

#endif // CASHCONTROLMODEL_H

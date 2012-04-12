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

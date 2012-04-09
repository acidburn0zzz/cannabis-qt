#ifndef CASHCONTROLMODEL_H
#define CASHCONTROLMODEL_H

#include <QAbstractTableModel>
#include <QDate>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSqlRecord>
#include <QSqlTableModel>

class CashControlModel : public QSqlTableModel
{
    Q_OBJECT
public:
    explicit CashControlModel(QObject *parent = 0);
    ~CashControlModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    void setDates(QString dataInicialStr, QString dataFinalStr);

    QDate dataInicial;
    QDate dataFinal;

    QSqlQuery *query;

    int querySize;

signals:
    
public slots:
    
};

#endif // CASHCONTROLMODEL_H

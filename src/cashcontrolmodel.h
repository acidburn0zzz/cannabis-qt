#ifndef CASHCONTROLMODEL_H
#define CASHCONTROLMODEL_H

#include <QAbstractTableModel>
#include <QDate>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSqlRecord>

class CashControlModel : public QAbstractTableModel
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

    QSqlQuery *query1;
    QSqlQuery *query2;

    int query1Size;
    int query2Size;

signals:
    
public slots:
    
};

#endif // CASHCONTROLMODEL_H

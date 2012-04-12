#include "cansmodel.h"

CansModel::CansModel(QObject *parent) :
    QSqlTableModel(parent)
{
}

CansModel::~CansModel()
{
}

int CansModel::rowCount(const QModelIndex & /*parent*/) const
{
    QSqlQuery query;

    query.prepare("SELECT Id FROM pots");

    if (query.exec())
    {
        int rows = 0;

        while (query.next()) rows++;

        return rows;
    }
    else
    {
        return 0;
    }
}

 int CansModel::columnCount(const QModelIndex & /*parent*/) const
{
     return 2;
}

QVariant CansModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole && index.column() == 1)
    {
        QSqlQuery query;

        query.prepare("SELECT SUM(Grams) AS gramsgastats FROM cannabis WHERE cannabis.IdPot = :idpot");
        query.bindValue(":idpot", index.row()+1);

        if (query.exec())
        {
            return QString(query.value(0).toString());
        }
    }

    return QVariant();
}

/*
void CashControlModel::setDates(QString dataInicialStr, QString dataFinalStr)
{
    layoutAboutToBeChanged();

    layoutChanged();
}
*/

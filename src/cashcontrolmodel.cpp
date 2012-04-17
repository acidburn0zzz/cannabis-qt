#include "cashcontrolmodel.h"

CashControlModel::CashControlModel(QObject *parent) :
    QSqlTableModel(parent)
{
    queryRows = 0;
}

CashControlModel::~CashControlModel()
{
}

int CashControlModel::rowCount(const QModelIndex & /*parent*/) const
{
    return queryRows;
}

 int CashControlModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 5;
}

QVariant CashControlModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (queryRows > 0)
        {
            return myData[queryRows*index.row()+index.column()];
        }
    }

    return QVariant();
}

void CashControlModel::setDates(QString dataInicialStr, QString dataFinalStr)
{
    layoutAboutToBeChanged();

    QSqlQuery query;

    /*
    query.prepare("SELECT cannabis.Data,cannabis.Grams,cannabis.Preu,altres.Diners FROM cannabis LEFT OUTER JOIN altres ON "
                  "cannabis.Data=altres.Data AND cannabis.Data >= :mydatainicial AND cannabis.Data <= :mydatafinal UNION ALL "
                  "SELECT altres.Data, cannabis.Grams, cannabis.Preu, altres.Diners FROM altres LEFT OUTER JOIN cannabis ON "
                  "cannabis.Data=altres.Data AND cannabis.Data >= :mydatainicial AND cannabis.Data <= :mydatafinal AND "
                  "cannabis.data <> altres.Data ORDER BY cannabis.Data");
    */

    query.prepare("SELECT Data,Grams,Preu FROM cannabis WHERE Data >= :mydatainicial AND Data <= :mydatafinal ORDER BY Data");

    query.bindValue(":mydatainicial", QDate::fromString(dataInicialStr, "dd/MM/yyyy").toString("yyyyMMdd"));
    query.bindValue(":mydatafinal", QDate::fromString(dataFinalStr, "dd/MM/yyyy").toString("yyyyMMdd"));

    queryRows = 0;

    if (!query.exec())
    {
        qDebug() << "Can't execute query!";
        qDebug() << query.lastError().text();
        layoutChanged();
        return;
    }

    // SQLite does not tell how many rows the query has...

    while (query.next())
    {
        queryRows++;
    }

    query.first();

    myData.clear();

    while (query.next())
    {
        for (int y=0; y<queryRows; y++)
        {
            query.next();

            myData[queryRows*y] = QDate::fromString(query.value(0).toString(), "yyyyMMdd").toString("dd/MM/yyyy");

            for (int x=1; x<4; x++)
            {
                myData[queryRows*y+x] = query.value(x).toString();
            }

            myData[queryRows*y+4] = QString::number(myData[queryRows*y+2].toDouble() + myData[queryRows*y+3].toDouble());
        }
    }

    qDebug() << queryRows;

    layoutChanged();
}

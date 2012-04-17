#include "cashcontrolmodel.h"

CashControlModel::CashControlModel(QObject *parent) :
    QSqlTableModel(parent)
{
}

CashControlModel::~CashControlModel()
{
}

int CashControlModel::rowCount(const QModelIndex & /*parent*/) const
{
    return myData.size();
}

 int CashControlModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 5;
}

QVariant CashControlModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (index.isValid() && myData.size() > 0)
        {
            /*
            QStringList row = myData.at(index.row());

            if (index.column() < row.size())
            {
                return row.at(index.column());
            }
            */
        }
    }

    return QVariant();
}

void CashControlModel::setDates(QString dataInicialStr, QString dataFinalStr)
{
    /*
    qDebug() << dataInicialStr;

    QSqlQuery query1, query2;

    query1.prepare("SELECT Data,Grams,Preu FROM cannabis WHERE Data >= :mydatainicial AND Data <= :mydatafinal ORDER BY Data");

    query1.bindValue(":mydatainicial", QDate::fromString(dataInicialStr, "dd/MM/yyyy").toString("yyyyMMdd"));
    query1.bindValue(":mydatafinal", QDate::fromString(dataFinalStr, "dd/MM/yyyy").toString("yyyyMMdd"));

    if (!query1.exec())
    {
        qDebug() << "Can't execute query!";
        qDebug() << query1.lastError().text();
        return;
    }

    query2.prepare("SELECT Data,Diners FROM altres WHERE Data >= :mydatainicial AND Data <= :mydatafinal ORDER BY Data");

    query2.bindValue(":mydatainicial", QDate::fromString(dataInicialStr, "dd/MM/yyyy").toString("yyyyMMdd"));
    query2.bindValue(":mydatafinal", QDate::fromString(dataFinalStr, "dd/MM/yyyy").toString("yyyyMMdd"));

    if (!query2.exec())
    {
        qDebug() << "Can't execute query!";
        qDebug() << query2.lastError().text();
        return;
    }

    layoutAboutToBeChanged();

    myData.clear();

    bool next1=true, next2=true;

    while (next1 || next2)
    {
        qDebug() << "k2";

        next1 = query1.next();
        next2 = query2.next();

        if (next1)
        {
            if (myData.value(data, QStringList()))
            {

            QString data(query1.value(0).toString());

            slist << QDate::fromString(query1.value(0).toString(), "yyyyMMdd").toString("dd/MM/yyyy");
            slist << query1.value(1).toString();
            slist << query1.value(2).toString();

            myData[data] = slist;
        }

        if (next1 && !next2)
        {
            slist << QString("0");
            slist << QString("");
        }

        if (!next1 && next2)
        {
            slist << QDate::fromString(query2.value(0).toString(), "yyyyMMdd").toString("dd/MM/yyyy");
            slist << QString("");
            slist << QString("");
            slist << query2.value(1).toString();
        }

        if (next1 && next2)
        {
            slist << QDate::fromString(query1.value(0).toString(), "yyyyMMdd").toString("dd/MM/yyyy");
            slist << query1.value(1).toString();
            slist << query1.value(2).toString();
            slist << query2.value(1).toString();
        }

        if (!slist.empty())
        {
            qDebug() << slist;
            myData.append(slist);
        }
    }

    layoutChanged();
    */
}

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
            QStringList row = myData.value(index.row(), QStringList());

            if (index.column() < row.size())
            {
                return row.at(index.column());
            }
        }
    }

    return QVariant();
}

void CashControlModel::setDates(QString dataInicial, QString dataFinal)
{
    // convert dates from dd/MM/yyyy to yyyyMMdd

    dataInicial = QDate::fromString(dataInicial, "dd/MM/yyyy").toString("yyyyMMdd");
    dataFinal = QDate::fromString(dataFinal, "dd/MM/yyyy").toString("yyyyMMdd");

    QSqlQuery query;

    query.prepare("SELECT Data,Grams,Preu FROM cannabis WHERE Data >= :mydatainicial AND Data <= :mydatafinal ORDER BY Data");
    query.bindValue(":mydatainicial", dataInicial);
    query.bindValue(":mydatafinal", dataFinal);

    if (!query.exec())
    {
        qDebug() << "Can't execute query!";
        qDebug() << query.lastError().text();
        return;
    }

    QMap <QString, QStringList> myDataTmp;

    while (query.next())
    {
        QStringList slist;

        QString data(query.value(0).toString());

        slist << QDate::fromString(data, "yyyyMMdd").toString("dd/MM/yyyy");
        slist << query.value(1).toString();
        slist << query.value(2).toString();

        slist << "0";

        // el total serà el mateix (de moment)
        slist << query.value(2).toString();

        myDataTmp.insert(data, slist);
    }

    query.clear();
    query.prepare("SELECT Data,Diners FROM altres WHERE Data >= :mydatainicial AND Data <= :mydatafinal ORDER BY Data");
    query.bindValue(":mydatainicial", dataInicial);
    query.bindValue(":mydatafinal", dataFinal);

    if (!query.exec())
    {
        qDebug() << "Can't execute query!";
        qDebug() << query.lastError().text();
        return;
    }

    while (query.next())
    {
        QStringList slist;

        QString data(query.value(0).toString());

        slist = myDataTmp.value(data, QStringList());

        if (slist.isEmpty())
        {
            slist << QDate::fromString(data, "yyyyMMdd").toString("dd/MM/yyyy");
            slist << "0";
            slist << "0";
            slist << query.value(1).toString();
            slist << query.value(1).toString(); // el total serà el mateix :p
        }
        else
        {
            // Tenim els tres camps, hem de calcular la suma

            slist.removeLast(); // treiem el total, ara no és correcte
            slist.removeLast(); // treiem el zero que havíem afegit abans per omplir

            slist << query.value(1).toString();

            // calculem el total

            slist << QString::number(slist.at(2).toDouble() + slist.at(3).toDouble());
        }

        myDataTmp.insert(data, slist);
    }

    layoutAboutToBeChanged();

    myData.clear();

    int row = 0;

    foreach (QStringList slist, myDataTmp)
    {
        myData.insert(row++, slist);
    }

    layoutChanged();
}

void CashControlModel::clear()
{
    layoutAboutToBeChanged();

    myData.clear();

    layoutChanged();
}

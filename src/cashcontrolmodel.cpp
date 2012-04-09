#include "cashcontrolmodel.h"

CashControlModel::CashControlModel(QObject *parent) :
    QSqlTableModel(parent)
{
    query = NULL;
    querySize = 0;
}

CashControlModel::~CashControlModel()
{
    if (query != NULL)
    {
        delete query;
    }
}

int CashControlModel::rowCount(const QModelIndex & /*parent*/) const
{
    if (query != NULL)
    {
        return querySize;
    }
    else
    {
        return 0;
    }
}

 int CashControlModel::columnCount(const QModelIndex & /*parent*/) const
{
     return 5;
}

QVariant CashControlModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (query != NULL)
        {
            QDate tmpDate(dataInicial);
            tmpDate.addDays(index.row());
            QString tmpDateStr(tmpDate.toString("dd/MM/yyyy"));

            if (index.row() == 0 && index.column() == 0)
            {
                // first row, rewind.
                query->first();
            }

            int field;

            switch(index.column())
            {
                case 0:
                // mostra la data
                field = query->record().indexOf("cannabis.Data");
                return QString(query->value(field).toString());
                break;

                case 1:
                // Mostra els grams
                field = query->record().indexOf("cannabis.Grams");
                return QString(query->value(field).toString());
                break;

                case 2:
                // Mostra els ingressos per grams
                field = query->record().indexOf("cannabis.Preu");
                return QString(query->value(field).toString());
                break;

                case 3:
                // Mostra els ingressos per altres conceptes
                field = query->record().indexOf("altres.Diners");
                return QString(query->value(field).toString());
                break;

                case 4:
                // mostra el total d'ingressos
                int field1 = query->record().indexOf("cannabis.Preu");
                int field2 = query->record().indexOf("altres.Diners");
                int val = query->value(field1).toInt() + query->value(field2).toInt();

                query->next();

                return QString::number(val);
                break;

            }
        }
        else
        {
            return QString("xxx");
        }
    }
    return QVariant();
}

void CashControlModel::setDates(QString dataInicialStr, QString dataFinalStr)
{
    layoutAboutToBeChanged();

    dataInicial = QDate::fromString(dataInicialStr, "dd/MM/yyyy");
    dataFinal = QDate::fromString(dataFinalStr, "dd/MM/yyyy");

    if (query == NULL)
    {
        query = new QSqlQuery();
    }

    query->clear();
    query->prepare("SELECT cannabis.Data,cannabis.Grams,cannabis.Preu,altres.Diners FROM cannabis,altres "
                   "WHERE altres.Data >= :mydata AND cannabis.Data >= :mydata GROUP BY cannabis.Data");
    query->bindValue(":mydata", dataInicialStr);

    if (!query->exec())
    {
        qDebug() << "Can't execute query!";
        qDebug() << query->lastError().text();
    }
    else
    {
        qDebug() << "Query OK!";
    }

    qDebug() << dataInicialStr;
    qDebug() << query->lastQuery();

    querySize=0;

    while (query->next()) querySize++;
    query->first();

    qDebug() << querySize;

    layoutChanged();
}

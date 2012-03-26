#include "cashcontrolmodel.h"

CashControlModel::CashControlModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    query1 = NULL;
    query2 = NULL;

    query1Size = 0;
    query2Size = 0;
}

CashControlModel::~CashControlModel()
{
    if (query1 != NULL)
    {
        delete query1;
    }

    if (query2 != NULL)
    {
        delete query2;
    }
}

int CashControlModel::rowCount(const QModelIndex & /*parent*/) const
{
    return 1;
    /*
    if (query1Size > query2Size)
    {
        return query1Size;
    }
    else
    {
        return query2Size;
    }
    */
}

 int CashControlModel::columnCount(const QModelIndex & /*parent*/) const
{
     return 5;
}

QVariant CashControlModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (query1 != NULL)
        {
            QDate tmpDate(dataInicial);
            tmpDate.addDays(index.row());
            QString tmpDateStr(tmpDate.toString("dd/MM/yyyy"));

            if (index.row() == 0 && index.column() == 0)
            {
                // first row, rewind.
                query1->first();
                // query2->first();
            }

            int field;

            switch(index.column())
            {
                case 0:
                // mostra la data
                return tmpDateStr;
                break;

                case 1:
                // Mostra els grams
                field = query1->record().indexOf("Grams");
                return QString(query1->value(field).toString());
                break;

                case 2:
                // Mostra els ingressos per grams
                field = query1->record().indexOf("Preu");
                return QString(query1->value(field).toString());
                break;

                case 3:
                // Mostra els ingressos per altres conceptes
                return QString("");
                // return QString(query2->value(0).toString());
                break;

                case 4:
                // mostra el total d'ingressos
                // int iVal = query1->value(1).toInt() + query2->value(0).toInt();

                query1->next();
                // query2->next();

                return QString("");
                // return QString(iVal);
                break;

            }
        }
        else
        {
            return QString("ERROR!");
        }
    }
    return QVariant();
}

void CashControlModel::setDates(QString dataInicialStr, QString dataFinalStr)
{
    dataInicial = QDate::fromString(dataInicialStr, "dd/MM/yyyy");
    dataFinal = QDate::fromString(dataFinalStr, "dd/MM/yyyy");

    if (query1 == NULL)
    {
        query1 = new QSqlQuery();
    }

    if (query2 == NULL)
    {
        query2 = new QSqlQuery();
    }

    query1->clear();
    query1->prepare("SELECT Grams,Preu FROM cannabis WHERE Data=:mydata");
    query1->bindValue(":mydata", dataInicialStr);

    if (!query1->exec())
    {
        qDebug() << "Can't execute query!";
        qDebug() << query1->lastError().text();
    }

    qDebug() << dataInicialStr;
    qDebug() << query1->lastQuery();

    query1Size=0;

    while (query1->next()) query1Size++;
    query1->first();

    qDebug() << query1Size;

    query2->clear();
    query2->prepare("SELECT Diners FROM altres WHERE Data=':mydata'");
    query2->bindValue(":mydata", dataInicialStr);
    if (!query2->exec())
    {
        qDebug() << "Can't execute query!";
        qDebug() << query2->lastError().text();
    }

    query2Size=0;

    while (query2->next()) query2Size++;
    query2->first();

    qDebug() << query2Size;

    emit dataChanged(createIndex(0,0), createIndex(0,4));
}

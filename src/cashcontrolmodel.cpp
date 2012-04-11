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
                return QDate::fromString(query->value(field).toString(), "yyyyMMdd").toString("dd/MM/yyyy");
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

    if (query == NULL)
    {
        query = new QSqlQuery();
    }

    query->clear();
    query->prepare("SELECT cannabis.Data,cannabis.Grams,cannabis.Preu,altres.Diners FROM cannabis LEFT OUTER JOIN altres ON "
                   "cannabis.Data=altres.Data AND cannabis.Data >= :mydatainicial AND cannabis.Data <= :mydatafinal UNION ALL "
                   "SELECT altres.Data, cannabis.Grams, cannabis.Preu, altres.Diners FROM altres LEFT OUTER JOIN cannabis ON "
                   "cannabis.Data=altres.Data AND cannabis.Data >= :mydatainicial AND cannabis.Data <= :mydatafinal AND "
                   "cannabis.data <> altres.Data ORDER BY cannabis.Data");

    query->bindValue(":mydatainicial", QDate::fromString(dataInicialStr, "dd/MM/yyyy").toString("yyyyMMdd"));
    query->bindValue(":mydatafinal", QDate::fromString(dataFinalStr, "dd/MM/yyyy").toString("yyyyMMdd"));

    querySize=0;

    if (!query->exec())
    {
        qDebug() << "Can't execute query!";
        qDebug() << query->lastError().text();
        return;
    }

    while (query->next()) querySize++;
    query->first();

    qDebug() << querySize;

    layoutChanged();
}

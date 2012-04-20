#include "cansmodel.h"
#include "constants.h"

CansModel::CansModel(QObject *parent) :
    QSqlQueryModel(parent)
{
    ids = new QMap<int,int>;
}

CansModel::~CansModel()
{
}

int CansModel::rowCount(const QModelIndex & /*parent*/) const
{
    QSqlDatabase db = QSqlDatabase::database(DB_CONNECTION_NAME);

    QSqlQuery query(db);

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
    if (role == Qt::DisplayRole)
    {
        if (index.column() == 0)
        {
            int i = index.row();
            int value = QSqlQueryModel::data(index, role).toInt();

            ids->insert(i, value);

            return QSqlQueryModel::data(index, role);
        }
        else if (index.column() == 1)
        {
            QSqlDatabase db = QSqlDatabase::database(DB_CONNECTION_NAME);

            QSqlQuery query(db);

            query.prepare("SELECT SUM(Grams) AS gramsgastats FROM cannabis WHERE cannabis.IdPot = :idpot");
            query.bindValue(":idpot", ids->value(index.row(), 0));

            if (query.exec())
            {
                query.next();

                int gastats = query.value(0).toInt();

                query.clear();
                query.prepare("SELECT grams FROM pots WHERE Id = :idpot");
                query.bindValue(":idpot", ids->value(index.row(), 0));

                if (query.exec())
                {
                    query.next();

                    int grams = query.value(0).toInt();

                    int reals = grams - gastats;

                    return QString::number(reals);
                }
            }
            else
            {
                qDebug() << "CansModel::data Query not ok";
            }
        }
    }
    else
    {
        return QSqlQueryModel::data(index, role);
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

/*
    Cannabis-qt
    Copyright (C) 2012 Karasu

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "cashcontrolmodel.h"
#include "constants.h"

CashControlModel::CashControlModel(QObject *parent, QSqlDatabase db) :
    QSqlTableModel(parent, db)
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

    QSqlDatabase db = QSqlDatabase::database(DB_CONNECTION_NAME);

    QSqlQuery query(db);

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

        QString grams(query.value(1).toString());
        QString preu(query.value(2).toString());

        // comprovem que no hi hagi ja alguna entrada aquesta data
        QStringList oldslist(myDataTmp.value(data, QStringList()));

        if (!oldslist.isEmpty())
        {
            // recollim els valors que ja hi havien i els afegim als nous
            // per anar acumulant el què s'ha consumit a la mateixa data
            grams = QString::number(grams.toDouble() + oldslist.at(1).toDouble());
            preu = QString::number(preu.toDouble() + oldslist.at(2).toDouble());
        }

        slist << QDate::fromString(data, "yyyyMMdd").toString("dd/MM/yyyy");
        slist << grams;
        slist << preu;

        slist << "0";  // Diners

        // el total serà el mateix (de moment)
        slist << preu;

        // si ja existeix el sobreescriu, o sigui que no ens n'hem de preocupar
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

            // agafem el valor de diners antic (si no hi havia cap agafarà el zero que hem posat abans).
            QString oldDiners(slist.last());

            // treiem el zero que havíem afegit abans per omplir (o el valor antic si ja teníem info d'aquesta data).
            slist.removeLast();

            slist << QString::number(oldDiners.toDouble() + query.value(1).toDouble());

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

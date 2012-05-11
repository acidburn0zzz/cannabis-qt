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

#include "cans.h"
#include "cansmodel.h"
#include "constants.h"

Cans::Cans(QWidget *parent) :
    QWidget(parent)
{
    CansModel *model = new CansModel;
    createModel(model);

    tableView = new QTableView;
    tableView->setModel(model);
    tableView->setCornerButtonEnabled(false);
    tableView->resizeColumnsToContents();

    tableView->horizontalHeader()->setStretchLastSection(true);

    tableView->show();

    connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)),this, SLOT(onDataChanged(QModelIndex,QModelIndex)));

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Close);

    QPushButton *addPushButton = new QPushButton(tr("Afegir cànnabis a un pot"));
    addPushButton->setIcon(QIcon::fromTheme("contact-new", QIcon(":/icons/elementary/actions/22/contact-new")));
    connect(addPushButton, SIGNAL(pressed()), this, SLOT(addToCan()));

    QHBoxLayout *hbox2 = new QHBoxLayout;
    hbox2->addWidget(addPushButton);
    hbox2->addWidget(buttonBox);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(tableView);
    vbox->addLayout(hbox2);

    setLayout(vbox);

    setDirtyFlag(false);
}

void Cans::addToCan()
{
    QModelIndex currentIndex = tableView->currentIndex();

    if (currentIndex.isValid())
    {
        int row = currentIndex.row();

        QModelIndex potIndex(tableView->indexAt(QPoint(0, row * tableView->rowHeight(row))));

        int idpot = potIndex.data().toInt();

        bool ok;

        int gramsToAdd = QInputDialog::getInt(this, tr("Afegeix al pot nº %1").arg(idpot),
                                              QString(tr("Grams:")), 0, -2147483647, 2147483647, 1, &ok);

        if (ok)
        {
            QSqlDatabase db = QSqlDatabase::database(DB_CONNECTION_NAME);
            QSqlQuery *query = new QSqlQuery(db);

            query->prepare("SELECT grams FROM pots WHERE Id=:idpot");
            query->bindValue(":idpot", idpot);

            if (query->exec())
            {
                query->next();

                int gramsOriginal = query->value(0).toInt();

                query->clear();

                query->prepare("UPDATE pots SET Grams = :mygrams WHERE Id = :mypot");
                query->bindValue(":mypot", potIndex.data().toInt());
                query->bindValue(":mygrams", gramsToAdd+gramsOriginal);

                if (!query->exec())
                {
                    qDebug() << "Can't execute query!";
                    qDebug() << query->lastError().text();
                }
                else
                {
                    tableView->setModel(NULL);

                    CansModel *model = new CansModel;
                    createModel(model);

                    tableView->setModel(model);
                }
            }
            else
            {
                qDebug() << "Can't execute query!";
                qDebug() << query->lastError().text();
            }
        }
    }
    else
    {
        QMessageBox::warning(this, tr("Pots"), tr("Si us plau, marqui a la llista el pot al què vol afegir producte"));
    }
}

void Cans::createModel(QSqlQueryModel *model)
{
    QSqlDatabase db = QSqlDatabase::database(DB_CONNECTION_NAME);

    model->setQuery("SELECT Id,Grams FROM Pots", db);

    model->setHeaderData(0, Qt::Horizontal, tr("Número de pot"));
    model->setHeaderData(1, Qt::Horizontal, tr("Grams"));
}

void Cans::onHelp()
{
    QMessageBox *msgBox = new QMessageBox(this);

    msgBox->setStyleSheet("QLabel { font: 12px; min-height: 30px; max-height: 60px; }");

    msgBox->setText(tr("blah blah blah"));

    msgBox->exec();
}

void Cans::addNewCan()
{
    /*
    QSqlTableModel *model = (QSqlTableModel *)tableView->model();

    // insert a row at the end
    int row = model->rowCount();
    if (model->insertRow(row) == false)
    {
        qDebug() << model->lastError().text();
    }

    setDirtyFlag(true);
    */
}

void Cans::deleteCan()
{
}

void Cans::onFilter()
{
    if (isDirty)
    {
        QMessageBox msgBox(this);

        msgBox.setText("Abans de poder fer una cerca, s'han de guardar els canvis. "
                       "Estàs segur de voler guardar-los ara?");
        msgBox.setInformativeText("Està segur ?");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);

        if (msgBox.exec() == QMessageBox::No)
        {
            return;
        }
    }

    QSqlTableModel *model = (QSqlTableModel *)tableView->model();

    if (model->submitAll())
    {
        model->database().commit();
        setDirtyFlag(false);
    }
    else
    {
        model->database().rollback();
        model->revertAll();
        qDebug() << model->lastError().text();
        // QMessageBox::warning(this, tr("Customers"),
        // tr("Can't save your changes: %1").arg(model->lastError().text()));
    }

    QString where("");

    if (!filterLineEdit->text().isEmpty())
    {
        where = QString("Numero = '%1'").arg(filterLineEdit->text());
    }

    model->setFilter(where);

    model->select();

    if (model->rowCount() <= 0)
    {
        QMessageBox::warning(this, tr("Pots"), tr("Ho sento, no puc trobar cap pot amb aquest número!"));
    }
}

void Cans::onDataChanged(QModelIndex, QModelIndex)
{
    setDirtyFlag(true);
}

void Cans::resizeTableViewToContents()
{
    if (tableView != NULL)
    {
        tableView->resizeColumnsToContents();
    }
}

void Cans::setDirtyFlag(bool status)
{
    isDirty = status;
}

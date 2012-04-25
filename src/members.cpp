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

#include "members.h"
#include "mydateeditdelegate.h"
#include "mycheckboxdelegate.h"
#include "constants.h"

Members::Members(QWidget *parent) :
    QWidget(parent)
{
    /*
    setStyleSheet("QRadioButton { font: bold 18px; padding-left:60px; min-height: 30px; max-height: 60px; }"
                  "QRadioButton::indicator { width: 40px; height: 40px; }"
                  "QLabel { font: bold 18px; min-height: 30px; max-height: 60px; }");
    */


    QPushButton *clearFilterButton = new QPushButton(tr("Neteja el filtre cerca"));
    connect(clearFilterButton, SIGNAL(pressed()), this, SLOT(onClearFilter()));

    QPushButton *filterButton = new QPushButton(tr("Cerca!"));
    connect(filterButton, SIGNAL(pressed()), this, SLOT(onFilter()));

    filterLineEdit = new QLineEdit;
    connect(filterLineEdit, SIGNAL(returnPressed()), this, SLOT(onFilter()));

    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addWidget(filterLineEdit);
    hbox->addWidget(filterButton);
    hbox->addWidget(clearFilterButton);

    QSqlDatabase db = QSqlDatabase::database(DB_CONNECTION_NAME);

    QSqlTableModel *model = new QSqlTableModel(NULL, db);
    createModel(model);

    tableView = new QTableView;
    tableView->setModel(model);
    tableView->setCornerButtonEnabled(false);
    tableView->resizeColumnsToContents();
    tableView->horizontalHeader()->setStretchLastSection(true);

    tableView->setItemDelegateForColumn(1, new MyDateEditDelegate);
    tableView->setColumnWidth(1, 100);

    tableView->setItemDelegateForColumn(11, new MyCheckBoxDelegate);

    tableView->setEditTriggers(QAbstractItemView::AllEditTriggers);

    tableView->show();

    connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)),this, SLOT(onDataChanged(QModelIndex,QModelIndex)));

//    QGroupBox *groupBox = new QGroupBox;
//    groupBox->setLayout(layout);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Apply | QDialogButtonBox::Ok | QDialogButtonBox::Cancel | QDialogButtonBox::Help);
    // connect(buttonBox, SIGNAL(accepted()), this, SLOT(onSave()));
    QPushButton *applyButton = buttonBox->button(QDialogButtonBox::Apply);
    connect(applyButton, SIGNAL(clicked()), this, SLOT(onApply()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(onCancel()));
    connect(buttonBox, SIGNAL(helpRequested()), this, SLOT(onHelp()));

    QPushButton *addNewCustomerPushButton = new QPushButton(tr("Nou soci"));
    connect(addNewCustomerPushButton, SIGNAL(pressed()), this, SLOT(addNewMember()));

    QPushButton *deleteCustomerPushButton = new QPushButton(tr("Esborrar soci"));
    connect(deleteCustomerPushButton, SIGNAL(pressed()), this, SLOT(deleteMember()));

    QHBoxLayout *hbox2 = new QHBoxLayout;
    hbox2->addWidget(addNewCustomerPushButton);
    hbox2->addWidget(deleteCustomerPushButton);
    hbox2->addWidget(buttonBox);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addLayout(hbox);
    vbox->addWidget(tableView);
    vbox->addLayout(hbox2);

    setLayout(vbox);

    setDirtyFlag(false);
}

void Members::createModel(QSqlTableModel *model)
{
    if (model != NULL)
    {
        model->setTable("Socis");
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        model->select();

        // model->removeColumn(0); // don't show the ID

        model->setHeaderData(0, Qt::Horizontal, tr("Codi soci"));
        model->setHeaderData(1, Qt::Horizontal, tr("Data Alta"));
        model->setHeaderData(2, Qt::Horizontal, tr("DNI"));
        model->setHeaderData(3, Qt::Horizontal, tr("Nom"));
        model->setHeaderData(4, Qt::Horizontal, tr("Primer Cognom"));
        model->setHeaderData(5, Qt::Horizontal, tr("Segon Cognom"));
        model->setHeaderData(6, Qt::Horizontal, tr("Adreça"));
        model->setHeaderData(7, Qt::Horizontal, tr("Telèfon"));
        model->setHeaderData(8, Qt::Horizontal, tr("Codi Postal"));
        model->setHeaderData(9, Qt::Horizontal, tr("Població"));
        model->setHeaderData(10, Qt::Horizontal, tr("E-mail"));
        model->setHeaderData(11, Qt::Horizontal, tr("Pagat"));
    }
}

void Members::onHelp()
{
    QMessageBox *msgBox = new QMessageBox(this);

    msgBox->setStyleSheet("QLabel { font: 12px; min-height: 30px; max-height: 60px; }");

    msgBox->setText(tr("blah blah blah"));

    msgBox->exec();
}

void Members::addNewMember()
{
    QSqlTableModel *model = (QSqlTableModel *)tableView->model();

    // insert a row at the end
    int row = model->rowCount();

    if (model->insertRow(row) == false)
    {
        qDebug() << model->lastError().text();
    }

    // Ens assegurem que es veurà
    tableView->scrollToBottom();

    setDirtyFlag(true);
}

// Això hauria d'estar dins del model (que hauriem de crear derivant la classe de QSqlTableModel)
// De moment ho deixo així perquè amb la xapussa de destruir el model i crear-ne un de nou funciona de pm
void Members::deleteMember()
{
    save(false);

    bool ok;
    int num_soci = QInputDialog::getInt(this, tr("Número de soci"), tr("Número:"), 0, 0, 2147483647, 1, &ok);

    if (ok)
    {
        QSqlDatabase db = QSqlDatabase::database(DB_CONNECTION_NAME);

        QSqlQuery *query = new QSqlQuery(db);

        query->prepare("SELECT Codi,Nom,Cognom1,Cognom2 FROM socis WHERE Codi = :mycode");
        query->bindValue(":mycode", num_soci);

        if (!query->exec())
        {
            qDebug() << "Can't execute query!";
            qDebug() << query->lastError().text();
        }

        int querySize=0;

        while (query->next()) querySize++;

        if (querySize > 0)
        {
            QMessageBox msgBox(this);

            msgBox.setText(tr("Aquesta acció eliminarà el soci número %1 !").arg(num_soci));
            msgBox.setInformativeText(tr("Està segur ?"));
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            msgBox.setDefaultButton(QMessageBox::No);

            if (msgBox.exec() == QMessageBox::Yes)
            {
                // QSqlTableModel *model = (QSqlTableModel *)tableView->model();
                //qDebug() << QString(row);
                // model->removeRow(row);

                query->clear();
                query->prepare("DELETE FROM socis WHERE Codi = :mycode");
                query->bindValue(":mycode", num_soci);

                if (!query->exec())
                {
                    qDebug() << "Can't execute query!";
                    qDebug() << query->lastError().text();
                }

                tableView->setModel(NULL);

                QSqlDatabase db = QSqlDatabase::database(DB_CONNECTION_NAME);

                QSqlTableModel *model = new QSqlTableModel(NULL, db);
                createModel(model);

                tableView->setModel(model);

            }
        }
        else
        {
            QMessageBox::warning(this, "Cannabis-qt",
                                 QString("Ho sento, no trobo el soci nº %1. Comprova que realment existeix.").arg(num_soci));
        }
    }

    /*



    QModelIndex index = tableView->currentIndex();

    if (index.isValid())
    {
        int row = index.row();

        QSqlTableModel *model = (QSqlTableModel *)tableView->model();

        QMessageBox msgBox(this);

        msgBox.setText("Aquesta acció eliminarà el soci! "
        "(els seus consums quedaran registrats, però no podrà accedir-hi)");
        msgBox.setInformativeText("Està segur ?");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);

        if (msgBox.exec() == QMessageBox::Yes)
        {
            qDebug() << QString(row);
            // model->removeRow(row);
            setDirtyFlag(true);
        }
    }
    else
    {
        QMessageBox::warning(this, tr("Socis"), tr("Si us plau, marqui a la llista el soci que vol esborrar"));
    }
    */
}

void Members::onFilter()
{
    /*
    if (isDirty)
    {
        QMessageBox msgBox(this);

        msgBox.setText("Abans de poder fer una cerca, s'han de guardar els canvis. "
                       "Estàs segur de voler guardar-los ara?");
        msgBox.setInformativeText("Estàs segur ?");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);

        if (msgBox.exec() == QMessageBox::No)
        {
            return;
        }
    }
    */

    save(false);

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
        qDebug() << QString("Members::onFilter(): %1").arg(model->lastError().text());
        // QMessageBox::warning(this, tr("Customers"),
        // tr("Can't save your changes: %1").arg(model->lastError().text()));
    }

    QString where("");

    if (!filterLineEdit->text().isEmpty())
    {
        where = QString("Codi = '%1'").arg(filterLineEdit->text());
    }

    model->setFilter(where);

    model->select();

    if (model->rowCount() <= 0 && !filterLineEdit->text().isEmpty())
    {
        // Try with Name

        where = QString("Nom = '%1'").arg(filterLineEdit->text());

        model->setFilter(where);

        model->select();

        if (model->rowCount() <= 0)
        {
            QMessageBox::warning(this, tr("Socis"), tr("Ho sento, no puc trobar cap soci amb aquest codi o amb aquest nom!"));
            onClearFilter();
        }
    }
}

void Members::onClearFilter()
{
    filterLineEdit->setText("");

    QSqlTableModel *model = (QSqlTableModel *)tableView->model();
    model->setFilter("");
    model->select();
}

void Members::onCancel()
{ 
    QSqlTableModel *model = (QSqlTableModel *)tableView->model();

    if (model != NULL)
    {
        model->database().rollback();

        model->revertAll();

        setDirtyFlag(false);

        // qDebug() << model->lastError().text();
    }
}

void Members::onDataChanged(QModelIndex, QModelIndex)
{
    setDirtyFlag(true);
}

bool Members::save(bool showMessage)
{
    bool result = false;

    if (tableView != NULL)
    {
        QSqlTableModel *model = (QSqlTableModel *)tableView->model();
        model->database().transaction();

        if (model->submitAll())
        {
            model->database().commit();

            // QMessageBox::information(this, tr("Socis"), tr("S'han guardat tots els canvis"));

            result = true;
        }
        else
        {
            model->database().rollback();

            model->revertAll();

            qDebug() << model->lastError().text();
            QMessageBox::warning(this, tr("Socis"), tr("No puc guardar els canvis: %1").arg(model->lastError().text()));
        }
    }

    if (result && isDirty)
    {
        resizeTableViewToContents();
        if (showMessage)
        {
            QMessageBox::information(this, tr("Socis"), tr("S'han guardat tots els canvis"));
        }
        setDirtyFlag(false);
    }

    return result;
}

void Members::resizeTableViewToContents()
{
    if (tableView != NULL)
    {
        tableView->resizeColumnsToContents();
        tableView->setColumnWidth(1, 100);
    }
}

void Members::onApply()
{
    save();
}

void Members::setDirtyFlag(bool status)
{
    isDirty = status;

    QPushButton *applyButton = buttonBox->button(QDialogButtonBox::Apply);

    applyButton->setEnabled(status);
}

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

#include "cannabis.h"
#include "mydateeditdelegate.h"
#include "constants.h"

Cannabis::Cannabis(QWidget *parent) :
    QWidget(parent)
{
    /*
    setStyleSheet("QRadioButton { font: bold 18px; padding-left:60px; min-height: 30px; max-height: 60px; }"
                  "QRadioButton::indicator { width: 40px; height: 40px; }"
                  "QLabel { font: bold 18px; min-height: 30px; max-height: 60px; }");
    */

    // name cif address phone email

    QPushButton *clearFilterButton = new QPushButton;
    clearFilterButton->setIcon(QIcon::fromTheme("edit-clear-symbolic", QIcon(":/icons/16x16/edit-clear-symbolic")));
    connect(clearFilterButton, SIGNAL(pressed()), this, SLOT(onClearFilter()));

    QPushButton *filterButton = new QPushButton(tr("Cerca!"));
    connect(filterButton, SIGNAL(pressed()), this, SLOT(onFilter()));

    filterLineEdit = new QLineEdit;
    connect(filterLineEdit, SIGNAL(returnPressed()), this, SLOT(onFilter()));

    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addWidget(filterLineEdit);
    hbox->addWidget(clearFilterButton);
    hbox->addWidget(filterButton);

    QSqlDatabase db = QSqlDatabase::database(DB_CONNECTION_NAME);

    QSqlRelationalTableModel *model = new QSqlRelationalTableModel(NULL, db);

    model->setTable("Cannabis");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    model->setRelation(1, QSqlRelation("Socis", "Codi", "Codi"));
    model->setRelation(3, QSqlRelation("Pots", "Id", "Id"));

    model->select();

    // model->removeColumn(0); // don't show the ID

    model->setHeaderData(0, Qt::Horizontal, tr("Codi"));
    model->setHeaderData(1, Qt::Horizontal, tr("Soci"));
    model->setHeaderData(2, Qt::Horizontal, tr("Data"));
    model->setHeaderData(3, Qt::Horizontal, tr("Pot"));
    model->setHeaderData(4, Qt::Horizontal, tr("Grams"));
    model->setHeaderData(5, Qt::Horizontal, tr("Preu"));

    tableView = new QTableView;
    tableView->setModel(model);
    tableView->setCornerButtonEnabled(false);

    // tableView->resizeColumnsToContents();
    tableView->setItemDelegate(new QSqlRelationalDelegate(tableView));
    tableView->horizontalHeader()->setStretchLastSection(true);

    tableView->setColumnWidth(0,0);

    tableView->setItemDelegateForColumn(2, new MyDateEditDelegate);
    tableView->setColumnWidth(2, 100);

    tableView->setEditTriggers(QAbstractItemView::AllEditTriggers);

    tableView->show();

    connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)),this, SLOT(onDataChanged(QModelIndex,QModelIndex)));

    // buttonBox = new QDialogButtonBox(QDialogButtonBox::Apply | QDialogButtonBox::Ok | QDialogButtonBox::Cancel | QDialogButtonBox::Help);
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Apply | QDialogButtonBox::Close | QDialogButtonBox::Cancel);
    // connect(buttonBox, SIGNAL(accepted()), this, SLOT(onSave()));
    QPushButton *applyButton = buttonBox->button(QDialogButtonBox::Apply);
    connect(applyButton, SIGNAL(clicked()), this, SLOT(onApply()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(onCancel()));
    // connect(buttonBox, SIGNAL(helpRequested()), this, SLOT(onHelp()));

    QPushButton *addNewCustomerPushButton = new QPushButton(tr("Nou consum"));
    connect(addNewCustomerPushButton, SIGNAL(pressed()), this, SLOT(addNewOrder()));

    QPushButton *deleteCustomerPushButton = new QPushButton(tr("Esborrar consum"));
    connect(deleteCustomerPushButton, SIGNAL(pressed()), this, SLOT(deleteOrder()));

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

    QSettings settings;

    maxPerDay = settings.value("Cannabis/max", 100).toInt();
}

void Cannabis::onHelp()
{
    QMessageBox *msgBox = new QMessageBox(this);

    msgBox->setStyleSheet("QLabel { font: 12px; min-height: 30px; max-height: 60px; }");

    msgBox->setText(tr("blah blah blah"));

    msgBox->exec();
}

void Cannabis::addNewOrder()
{
    QSqlRelationalTableModel *model = (QSqlRelationalTableModel *)tableView->model();

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

void Cannabis::deleteOrder()
{
    // Does not work! : "QSqlQuery::value not positioned on a valid record"
    // Ara sí que funciona ¿?

    QModelIndex index = tableView->currentIndex();

    if (index.isValid())
    {
        int row = index.row();

        QSqlRelationalTableModel *model = (QSqlRelationalTableModel *)tableView->model();

        QMessageBox msgBox(this);

        msgBox.setText(tr("Aquesta acció eliminarà la informació sobre el consum del soci!"));
        msgBox.setInformativeText(tr("Està segur ?"));
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);

        // execute message box. method exec() return the button value of clicked button
        if (msgBox.exec() == QMessageBox::Yes)
        {
            model->removeRow(row);
            setDirtyFlag(true);
        }
    }
    else
    {
        QMessageBox::warning(this, tr("Socis"), tr("Si us plau, marqui a la llista el consum que vol esborrar"));
    }
}

void Cannabis::onFilter()
{
    /*
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
    */

    save(false);

    QSqlRelationalTableModel *model = (QSqlRelationalTableModel *)tableView->model();

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
        where = QString("Codi = '%1'").arg(filterLineEdit->text());
    }

    model->setFilter(where);

    model->select();

    if (model->rowCount() <= 0 && !filterLineEdit->text().isEmpty())
    {
        // Try with date

        QDate data(QDate::fromString(filterLineEdit->text(), "dd/MM/yyyy"));

        where = QString("Data = '%1'").arg(data.toString("yyyyMMdd"));

        model->setFilter(where);

        model->select();

        if (model->rowCount() <= 0)
        {
            QMessageBox::warning(this, tr("Cànnabis"), tr("Ho sento, no puc trobar cap consum d'un soci amb aquest codi o un consum amb aquesta data!"));
        }
    }
}

void Cannabis::onClearFilter()
{
    filterLineEdit->setText("");

    QSqlRelationalTableModel *model = (QSqlRelationalTableModel *)tableView->model();
    model->setFilter("");
    model->select();
}

void Cannabis::onCancel()
{ 
    QSqlRelationalTableModel *model = (QSqlRelationalTableModel *)tableView->model();

    if (model != NULL)
    {
        model->database().rollback();

        model->revertAll();

        setDirtyFlag(false);

        // qDebug() << model->lastError().text();
    }
}

void Cannabis::onDataChanged(QModelIndex, QModelIndex)
{
    setDirtyFlag(true);
}

void Cannabis::onApply()
{
    save();
}

bool Cannabis::save(bool showMessage)
{
    bool result = false;

    if (tableView != NULL)
    {
        QSqlRelationalTableModel *model = (QSqlRelationalTableModel *)tableView->model();

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
        // resizeTableViewToContents();
        if (showMessage)
        {
            QMessageBox::information(this, tr("Cànnabis"), tr("S'han guardat tots els canvis"));
        }

        setDirtyFlag(false);
    }

    return result;
}

void Cannabis::resizeTableViewToContents()
{
    if (tableView != NULL)
    {
        tableView->resizeColumnsToContents();
        tableView->setColumnWidth(2, 100);
        tableView->horizontalHeader()->setStretchLastSection(true);
    }
}

void Cannabis::setDirtyFlag(bool status)
{
    isDirty = status;

    QPushButton *applyButton = buttonBox->button(QDialogButtonBox::Apply);

    applyButton->setEnabled(status);
}

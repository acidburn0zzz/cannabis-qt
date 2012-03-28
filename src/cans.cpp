#include "cans.h"

Cans::Cans(QWidget *parent) :
    QWidget(parent)
{
    /*
    setStyleSheet("QRadioButton { font: bold 18px; padding-left:60px; min-height: 30px; max-height: 60px; }"
                  "QRadioButton::indicator { width: 40px; height: 40px; }"
                  "QLabel { font: bold 18px; min-height: 30px; max-height: 60px; }");
    */

    // name cif address phone email

    // QPushButton *clearFilterButton = new QPushButton(tr(""));
    // mconnect(clearFilterButton, SIGNAL(pressed()), this, SLOT(onClearFilter()));

    QPushButton *filterButton = new QPushButton(tr("Cerca!"));
    connect(filterButton, SIGNAL(pressed()), this, SLOT(onFilter()));

    filterLineEdit = new QLineEdit;
    connect(filterLineEdit, SIGNAL(returnPressed()), this, SLOT(onFilter()));

    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addWidget(filterLineEdit);
    hbox->addWidget(filterButton);

    // CREATE TABLE "Pots" ( "Id" INTEGER PRIMARY KEY AUTOINCREMENT, "Numero" INTEGER NOT NULL, "Grams" INTEGER NOT NULL);

    QSqlTableModel *model = new QSqlTableModel;
    model->setTable("Pots");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    model->select();

    model->removeColumn(0); // don't show the ID
//    model->setHeaderData(0, Qt::Horizontal, tr("Codi"));
    model->setHeaderData(0, Qt::Horizontal, tr("Número de pot"));
    model->setHeaderData(1, Qt::Horizontal, tr("Grams"));


    tableView = new QTableView;
    tableView->setModel(model);
    tableView->setCornerButtonEnabled(false);
    tableView->resizeColumnsToContents();

    tableView->horizontalHeader()->setStretchLastSection(true);

    // tableView->setItemDelegateForColumn(0, new MyDateEdit);

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

    QPushButton *addNewCustomerPushButton = new QPushButton(tr("Nou pot"));
    connect(addNewCustomerPushButton, SIGNAL(pressed()), this, SLOT(addNewCan()));

    QPushButton *deleteCustomerPushButton = new QPushButton(tr("Esborrar pot"));
    connect(deleteCustomerPushButton, SIGNAL(pressed()), this, SLOT(deleteCan()));

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

void Cans::onHelp()
{
    QMessageBox *msgBox = new QMessageBox(this);

    msgBox->setStyleSheet("QLabel { font: 12px; min-height: 30px; max-height: 60px; }");

    msgBox->setText(tr("blah blah blah"));

    msgBox->exec();
}

void Cans::addNewCan()
{
    QSqlTableModel *model = (QSqlTableModel *)tableView->model();

    // insert a row at the end
    int row = model->rowCount();
    if (model->insertRow(row) == false)
    {
        qDebug() << model->lastError().text();
    }

    setDirtyFlag(true);
}

void Cans::deleteCan()
{

    // int i = tableView->selectedIndexes()
    // QModelIndex index = tableView->currentIndex();

    QMessageBox::warning(this, tr("Pots"), tr("TODO"));
    return;





    // Does not work : "QSqlQuery::value not positioned on a valid record"


    QModelIndex index = tableView->currentIndex();

    if (index.isValid())
    {
        int row = index.row();

        QSqlTableModel *model = (QSqlTableModel *)tableView->model();

        QMessageBox msgBox;

        msgBox.setText("Aquesta acció eliminarà el pot."
        "(els seus consums quedaran registrats, però no podrà accedir-hi)");
        msgBox.setInformativeText("Està segur ?");
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
        QMessageBox::warning(this, tr("Pots"), tr("Si us plau, marqui a la llista el pot que vol esborrar"));
    }
}

void Cans::onFilter()
{
    if (isDirty)
    {
        QMessageBox msgBox;

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
        where = "Numero = '" + filterLineEdit->text() + "'";
    }

    model->setFilter(where);

    model->select();

    if (model->rowCount() <= 0)
    {
        QMessageBox::warning(this, tr("Pots"), tr("Ho sento, no puc trobar cap pot amb aquest número!"));
    }
}

void Cans::onCancel()
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

void Cans::onDataChanged(QModelIndex, QModelIndex)
{
    setDirtyFlag(true);
}

bool Cans::save()
{
    bool result = false;

    if (tableView != NULL)
    {
        QSqlTableModel *model = (QSqlTableModel *)tableView->model();
        model->database().transaction();

        if (model->submitAll())
        {
            model->database().commit();

            // QMessageBox::information(this, tr("Pots"), tr("S'han guardat tots els canvis"));

            result = true;
        }
        else
        {
            model->database().rollback();

            model->revertAll();

            qDebug() << model->lastError().text();
            QMessageBox::warning(this, tr("Altres"), tr("No puc guardar els canvis: %1").arg(model->lastError().text()));
        }
    }

    if (result && isDirty)
    {
        resizeTableViewToContents();

        QMessageBox::information(this, tr("Pots"), tr("S'han guardat tots els canvis"));
        setDirtyFlag(false);
    }

    return result;
}

void Cans::resizeTableViewToContents()
{
    if (tableView != NULL)
    {
        tableView->resizeColumnsToContents();
    }
}

void Cans::onApply()
{
    save();
}

void Cans::setDirtyFlag(bool status)
{
    isDirty = status;

    QPushButton *applyButton = buttonBox->button(QDialogButtonBox::Apply);

    applyButton->setEnabled(status);
}

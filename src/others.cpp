#include "others.h"
#include "mydateeditdelegate.h"

Others::Others(QWidget *parent) :
    QWidget(parent)
{
    /*
    setStyleSheet("QRadioButton { font: bold 18px; padding-left:60px; min-height: 30px; max-height: 60px; }"
                  "QRadioButton::indicator { width: 40px; height: 40px; }"
                  "QLabel { font: bold 18px; min-height: 30px; max-height: 60px; }");
    */

    // name cif address phone email

    QPushButton *clearFilterButton = new QPushButton(tr("Neteja el filtre de cerca"));
    connect(clearFilterButton, SIGNAL(pressed()), this, SLOT(onClearFilter()));

    QPushButton *filterButton = new QPushButton(tr("Cerca!"));
    connect(filterButton, SIGNAL(pressed()), this, SLOT(onFilter()));

    filterLineEdit = new QLineEdit;
    connect(filterLineEdit, SIGNAL(returnPressed()), this, SLOT(onFilter()));

    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addWidget(filterLineEdit);
    hbox->addWidget(filterButton);
    hbox->addWidget(clearFilterButton);

    // CREATE TABLE "Altres" ( "Id" INTEGER PRIMARY KEY AUTOINCREMENT, "Data" TEXT, "Diners" REAL);

    QSqlTableModel *model = new QSqlTableModel;
    model->setTable("Altres");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    model->select();

    // model->removeColumn(0); // don't show the ID
    model->setHeaderData(0, Qt::Horizontal, tr("Codi consum"));
    model->setHeaderData(1, Qt::Horizontal, tr("Data"));
    model->setHeaderData(2, Qt::Horizontal, tr("Diners"));

    tableView = new QTableView;
    tableView->setModel(model);
    tableView->setCornerButtonEnabled(false);
    tableView->resizeColumnsToContents();

    tableView->horizontalHeader()->setStretchLastSection(true);

    tableView->setItemDelegateForColumn(1, new MyDateEditDelegate);
    tableView->setColumnWidth(1, 100);

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
}

void Others::onHelp()
{
    QMessageBox *msgBox = new QMessageBox(this);

    msgBox->setStyleSheet("QLabel { font: 12px; min-height: 30px; max-height: 60px; }");

    msgBox->setText(tr("blah blah blah"));

    msgBox->exec();
}

void Others::addNewOrder()
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

void Others::deleteOrder()
{
    // Does not work! : "QSqlQuery::value not positioned on a valid record"
    // Ara sí que funciona ¿?

    QModelIndex index = tableView->currentIndex();

    if (index.isValid())
    {
        int row = index.row();

        QSqlTableModel *model = (QSqlTableModel *)tableView->model();

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
        QMessageBox::warning(this, tr("Altres"), tr("Si us plau, marqui a la llista el consum que vol esborrar"));
    }
}

void Others::onFilter()
{
    if (isDirty)
    {
        QMessageBox msgBox(this);

        msgBox.setText(tr("Abans de poder fer una cerca, s'han de guardar els canvis. "
                       "Estàs segur de voler guardar-los ara?"));
        msgBox.setInformativeText(tr("Està segur ?"));
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
        where = QString("Id = '%1").arg(filterLineEdit->text());
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
            QMessageBox::warning(this, tr("Altres"), tr("Ho sento, no puc trobar cap consum d'un soci amb aquest codi o un consum amb aquesta data!"));
        }
    }
}

void Others::onClearFilter()
{
    filterLineEdit->setText("");

    QSqlTableModel *model = (QSqlTableModel *)tableView->model();
    model->setFilter("");
    model->select();
}


void Others::onCancel()
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

void Others::onDataChanged(QModelIndex, QModelIndex)
{
    setDirtyFlag(true);
}

bool Others::save()
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
            QMessageBox::warning(this, tr("Altres"), tr("No puc guardar els canvis: %1").arg(model->lastError().text()));
        }
    }

    if (result && isDirty)
    {
        resizeTableViewToContents();
        QMessageBox::information(this, tr("Altres"), tr("S'han guardat tots els canvis"));
        setDirtyFlag(false);
    }

    return result;
}

void Others::resizeTableViewToContents()
{
    if (tableView != NULL)
    {
        tableView->resizeColumnsToContents();
        tableView->setColumnWidth(1, 100);
    }
}

void Others::onApply()
{
    save();
}

void Others::setDirtyFlag(bool status)
{
    isDirty = status;

    QPushButton *applyButton = buttonBox->button(QDialogButtonBox::Apply);

    applyButton->setEnabled(status);
}

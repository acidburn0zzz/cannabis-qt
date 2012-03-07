#include "members.h"

Members::Members(QWidget *parent) :
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

    QPushButton *filterButton = new QPushButton(tr("Filter!"));
    connect(filterButton, SIGNAL(pressed()), this, SLOT(onFilter()));

    filterLineEdit = new QLineEdit;
    connect(filterLineEdit, SIGNAL(returnPressed()), this, SLOT(onFilter()));

    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addWidget(filterLineEdit);
    hbox->addWidget(filterButton);

    QSqlTableModel *model = new QSqlTableModel;
    model->setTable("Socis");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    // model->removeColumn(0); // don't show the ID

    model->setHeaderData(0, Qt::Horizontal, tr("Codi"));
    model->setHeaderData(1, Qt::Horizontal, tr("DNI"));
    model->setHeaderData(2, Qt::Horizontal, tr("Nom"));
    model->setHeaderData(3, Qt::Horizontal, tr("Primer Cognom"));
    model->setHeaderData(4, Qt::Horizontal, tr("Segon Cognom"));
    model->setHeaderData(5, Qt::Horizontal, tr("Adreça"));
    model->setHeaderData(6, Qt::Horizontal, tr("Telèfon"));
    model->setHeaderData(7, Qt::Horizontal, tr("Codi Postal"));
    model->setHeaderData(8, Qt::Horizontal, tr("Població"));
    model->setHeaderData(9, Qt::Horizontal, tr("E-mail"));

    tableView = new QTableView;
    tableView->setModel(model);
    tableView->setCornerButtonEnabled(false);
    tableView->resizeColumnsToContents();
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->show();

//    QGroupBox *groupBox = new QGroupBox;
//    groupBox->setLayout(layout);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel | QDialogButtonBox::Help);
    // connect(buttonBox, SIGNAL(accepted()), this, SLOT(onSave()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(onCancel()));
    connect(buttonBox, SIGNAL(helpRequested()), this, SLOT(onHelp()));

    QPushButton *addNewCustomerPushButton = new QPushButton(tr("Nou soci"));
    connect(addNewCustomerPushButton, SIGNAL(pressed()), this, SLOT(addNewCustomer()));

    QPushButton *deleteCustomerPushButton = new QPushButton(tr("Esborrar soci"));
    connect(deleteCustomerPushButton, SIGNAL(pressed()), this, SLOT(deleteCustomer()));

    QHBoxLayout *hbox2 = new QHBoxLayout;
    hbox2->addWidget(addNewCustomerPushButton);
    hbox2->addWidget(deleteCustomerPushButton);
    hbox2->addWidget(buttonBox);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addLayout(hbox);
    vbox->addWidget(tableView);
    vbox->addLayout(hbox2);

    setLayout(vbox);
}

void Customers::onHelp()
{
    QMessageBox *msgBox = new QMessageBox(this);

    msgBox->setStyleSheet("QLabel { font: 12px; min-height: 30px; max-height: 60px; }");

    msgBox->setText(tr("blah blah blah"));

    msgBox->exec();

}

void Customers::addNewCustomer()
{
    QSqlTableModel *model = (QSqlTableModel *)tableView->model();

    // insert a row at the end
    int row = model->rowCount();
    if (model->insertRow(row) == false)
    {
        qDebug() << model->lastError().text();
    }
}

void Customers::deleteCustomer()
{

    // int i = tableView->selectedIndexes()
    // QModelIndex index = tableView->currentIndex();

    QMessageBox::warning(this, tr("Socis"), tr("TODO"));
    return;





    // Does not work : "QSqlQuery::value not positioned on a valid record"


    QModelIndex index = tableView->currentIndex();

    if (index.isValid())
    {
        int row = index.row();

        QSqlTableModel *model = (QSqlTableModel *)tableView->model();

        QMessageBox msgBox;

        msgBox.setText("Aquesta acció eliminarà el soci! "
        "(els seus consums quedaran registrats, però no podrà accedir-hi)");
        msgBox.setInformativeText("Està segur ?");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);

        // execute message box. method exec() return the button value of clicked button
        if (msgBox.exec() == QMessageBox::Yes)
        {
            model->removeRow(row);
        }
    }
    else
    {
        QMessageBox::warning(this, tr("Socis"), tr("Si us plau, marqui a la llista el soci que vol esborrarl"));
    }
}

void Customers::onFilter()
{
    QSqlTableModel *model = (QSqlTableModel *)tableView->model();

    if (model->submitAll())
    {
        model->database().commit();
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
        where = "Codi = '" + filterLineEdit->text() + "'";
    }

    model->setFilter(where);

    model->select();

    if (model->rowCount() <= 0 && !filterLineEdit->text().isEmpty())
    {
        // Try with Name

        where = "Name = '" + filterLineEdit->text() + "'";

        model->setFilter(where);

        model->select();

        if (model->rowCount() <= 0)
        {
            QMessageBox::warning(this, tr("Customers"), tr("Sorry, can't find any record with this name or CIF!"));
        }
    }
}

void Customers::onCancel()
{
    QSqlTableModel *model = (QSqlTableModel *)tableView->model();

    if (model != NULL)
    {
        model->database().rollback();

        model->revertAll();

        // qDebug() << model->lastError().text();
    }
}

bool Customers::save()
{
    bool result = false;

    if (tableView != NULL)
    {
        QSqlTableModel *model = (QSqlTableModel *)tableView->model();
        model->database().transaction();

        if (model->submitAll())
        {
            model->database().commit();
            QMessageBox::information(this, tr("Customers"), tr("All changes have been saved"));
            result = true;
        }
        else
        {
            model->database().rollback();

            model->revertAll();

            qDebug() << model->lastError().text();
            QMessageBox::warning(this, tr("Customers"), tr("Can't save your changes: %1").arg(model->lastError().text()));
        }
    }

    return result;
}

void Customers::resizeTableViewToContents()
{
    if (tableView != NULL)
    {
        tableView->resizeColumnsToContents();
    }
}

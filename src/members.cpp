#include "members.h"
#include "mydateedit.h"

Members::Members(QWidget *parent) :
    QWidget(parent)
{
    /*
    setStyleSheet("QRadioButton { font: bold 18px; padding-left:60px; min-height: 30px; max-height: 60px; }"
                  "QRadioButton::indicator { width: 40px; height: 40px; }"
                  "QLabel { font: bold 18px; min-height: 30px; max-height: 60px; }");
    */


    // QPushButton *clearFilterButton = new QPushButton(tr(""));
    // mconnect(clearFilterButton, SIGNAL(pressed()), this, SLOT(onClearFilter()));

    QPushButton *filterButton = new QPushButton(tr("Cerca!"));
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

    tableView = new QTableView;
    tableView->setModel(model);
    tableView->setCornerButtonEnabled(false);
    tableView->resizeColumnsToContents();
    tableView->horizontalHeader()->setStretchLastSection(true);

    tableView->setItemDelegateForColumn(1, new MyDateEdit);
    tableView->setItemDelegateForColumn(11, new QItemDelegate);

    tableView->show();

    connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)),this, SLOT(onDataChanged(QModelIndex,QModelIndex)));

//    QGroupBox *groupBox = new QGroupBox;
//    groupBox->setLayout(layout);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel | QDialogButtonBox::Help);
    // connect(buttonBox, SIGNAL(accepted()), this, SLOT(onSave()));
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

    isDirty = false;
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

    isDirty = true;
}

void Members::deleteMember()
{

    // int i = tableView->selectedIndexes()
    // QModelIndex index = tableView->currentIndex();

    QMessageBox::warning(this, tr("Members"), tr("Encara per fer!"));
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
            isDirty = true;
        }
    }
    else
    {
        QMessageBox::warning(this, tr("Socis"), tr("Si us plau, marqui a la llista el soci que vol esborrar"));
    }
}

void Members::onFilter()
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
        isDirty = false;
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
            QMessageBox::warning(this, tr("Socis"), tr("Ho sento, no puc trobar cap soci amb aquest codi o amb aquest nom!"));
        }
    }
}

void Members::onCancel()
{ 
    QSqlTableModel *model = (QSqlTableModel *)tableView->model();

    if (model != NULL)
    {
        model->database().rollback();

        model->revertAll();

        isDirty = false;

        // qDebug() << model->lastError().text();
    }
}

void Members::onDataChanged(QModelIndex, QModelIndex)
{
    isDirty = true;
}

bool Members::save()
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
        QMessageBox::information(this, tr("Socis"), tr("S'han guardat tots els canvis"));
        isDirty = false;
    }

    return result;
}

void Members::resizeTableViewToContents()
{
    if (tableView != NULL)
    {
        tableView->resizeColumnsToContents();
    }
}

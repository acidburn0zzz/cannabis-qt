#include "cashcontrol.h"
#include "cashcontrolmodel.h"

CashControl::CashControl(QWidget *parent) :
    QWidget(parent)
{
    QLabel *dataInicialLabel = new QLabel(tr("Data inicial:"));
    dataInicialLabel->setAlignment(Qt::AlignRight);

    QDate currentDate(QDate::currentDate());

    dataInicial = new QDateEdit(currentDate.addYears(-1));
    dataInicial->setDisplayFormat("dd/MM/yyyy");
    dataInicial->setCalendarPopup(true);

    QLabel *dataFinalLabel = new QLabel(tr("Data final:"));
    dataFinalLabel->setAlignment(Qt::AlignRight);

    dataFinal = new QDateEdit(currentDate);
    dataFinal->setDisplayFormat("dd/MM/yyyy");
    dataFinal->setCalendarPopup(true);

    QPushButton *showButton = new QPushButton(tr("Mostra els moviments!"));
    connect(showButton, SIGNAL(pressed()), this, SLOT(onShow()));

    QHBoxLayout *hbox1 = new QHBoxLayout;
    hbox1->addWidget(dataInicialLabel);
    hbox1->addWidget(dataInicial);

    QHBoxLayout *hbox2 = new QHBoxLayout;
    hbox2->addWidget(dataFinalLabel);
    hbox2->addWidget(dataFinal);

    CashControlModel *model = new CashControlModel();

    model->setHeaderData(0, Qt::Horizontal, tr("Data"));
    model->setHeaderData(1, Qt::Horizontal, tr("Grams"));
    model->setHeaderData(2, Qt::Horizontal, tr("Ingressos (cànnabis)"));
    model->setHeaderData(3, Qt::Horizontal, tr("Ingressos (altres)"));
    model->setHeaderData(4, Qt::Horizontal, tr("Ingressos (total)"));

    tableView = new QTableView;
    tableView->setModel(model);
    tableView->setCornerButtonEnabled(false);
    tableView->resizeColumnsToContents();
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->show();

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Help);
    connect(buttonBox, SIGNAL(helpRequested()), this, SLOT(onHelp()));

    QPushButton *printButton = new QPushButton(tr("Imprimeix"));
    connect(printButton, SIGNAL(pressed()), this, SLOT(onPrint()));

    QHBoxLayout *hbox4 = new QHBoxLayout;
    hbox4->addWidget(printButton);
    hbox4->addWidget(buttonBox);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addLayout(hbox1);
    vbox->addLayout(hbox2);
    vbox->addWidget(showButton);
    vbox->addWidget(tableView);
    vbox->addLayout(hbox4);

    setLayout(vbox);
}

void CashControl::onHelp()
{
    QMessageBox *msgBox = new QMessageBox(this);

    msgBox->setStyleSheet("QLabel { font: 12px; min-height: 30px; max-height: 60px; }");

    msgBox->setText(tr("blah blah blah"));

    msgBox->exec();
}

void CashControl::resizeTableViewToContents()
{
    if (tableView != NULL)
    {
        tableView->resizeColumnsToContents();
    }
}

void CashControl::onShow()
{
    CashControlModel *model = static_cast<CashControlModel *>(tableView->model());

    model->setDates(dataInicial->date().toString("dd/MM/yyyy"), dataFinal->date().toString("dd/MM/yyyy"));


    tableView->resizeColumnsToContents();
    tableView->horizontalHeader()->setStretchLastSection(true);
}

void CashControl::clear()
{
    CashControlModel *model = static_cast<CashControlModel *>(tableView->model());

    model->clear();
}

void CashControl::onPrint()
{
}

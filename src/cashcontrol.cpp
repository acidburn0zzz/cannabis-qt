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

    printButton = new QPushButton(tr("Imprimeix"));
    connect(printButton, SIGNAL(pressed()), this, SLOT(onPrint()));
    printButton->setEnabled(false);

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

    if (printButton)
    {
        printButton->setEnabled(model->rowCount() > 0);
    }
}

void CashControl::clear()
{
    CashControlModel *model = static_cast<CashControlModel *>(tableView->model());

    model->clear();
}

void CashControl::onPrint()
{
    QString strStream;
    QTextStream text(&strStream);

    CashControlModel *model = static_cast<CashControlModel *>(tableView->model());

    const int rowCount = model->rowCount();
    const int columnCount = model->columnCount();

    if (rowCount <= 0)
    {
        return;
    }

    QString strTitle(tr("Cannabis-qt"));

    text <<  "<html>\n"
        "<head>\n"
        "<meta Content=\"Text/html; charset=UTF8\">\n"
        <<  QString("<title>%1</title>\n").arg(strTitle)
        <<  "</head>\n"
        <<  "<body bgcolor=#ffffff link=#5000A0>\n";

    text << QString("<h1>%1</h1>\n").arg(strTitle);
    text << QString(tr("<h2>Del %1 al %2</h2><br/>\n")).arg(dataInicial->date().toString("dd/MM/yyyy"), dataFinal->date().toString("dd/MM/yyyy"));

    text << "<table border=1 cellspacing=0 cellpadding=2>\n";

    // draw headers
    text << "<tr bgcolor=#f0f0f0>";

    for (int column = 0; column < columnCount; column++)
    {
        if (!tableView->isColumnHidden(column))
        {
            text << QString("<th>%1</th>").arg(model->headerData(column, Qt::Horizontal).toString());
        }
    }

    text << "</tr>\n";

    // draw data table
    for (int row = 0; row < rowCount; row++)
    {
        text << "<tr>";
        for (int column = 0; column < columnCount; column++)
        {
            if (!tableView->isColumnHidden(column))
            {
                QString data = model->data(model->index(row, column)).toString().simplified();
                text << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        text << "</tr>\n";
    }

    text <<  "</table>\n";

    text << "</body>\n</html>\n";

    QTextDocument *document = new QTextDocument();

    document->setHtml(strStream);

    QPrinter printer;

    QPrintDialog *dialog = new QPrintDialog(&printer, this);

    if (dialog->exec() == QDialog::Accepted)
    {
        document->print(&printer);
    }

    delete document;
}

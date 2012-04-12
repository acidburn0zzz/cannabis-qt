#define PROGRAM_VERSION "0.1alfa"

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QTextCodec *utf8Codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForTr(utf8Codec);
    QTextCodec::setCodecForCStrings(utf8Codec);
    QTextCodec::setCodecForLocale(utf8Codec);

    QString appDataDir (QDesktopServices::storageLocation(QDesktopServices::DataLocation));
    if (!QDir(appDataDir).exists())
    {
        // It doesn't exists, we have to create it.
        QDir().mkpath(appDataDir);
    }

    qDebug() << "Application data will be stored in : " + appDataDir;

    // Open our database
    if (!dbManager.openDB())
    {
        qDebug() << "Error: can't create/open database.";
        QMessageBox::critical(this, tr("Cannabis-qt"),
                              tr("Error crític: No puc obrir la base de dades."
                              "Si us plau, posi's en contacte amb el seu distribuidor "
                              "per a obtenir ajuda"));
        qApp->quit();
    }

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    createCentralWidgets();

    setWindowTitle(tr("Cannabis-qt  ") + QString(PROGRAM_VERSION));

    setCentralWidget(chooseOptionWidget);

    resize( QSize(860, 500).expandedTo(minimumSizeHint()) );

    setMinimumSize(600, 400);
}

MainWindow::~MainWindow()
{
    /*
    qDebug() << "Closing database";
    dbManager.closeDB();
    qDebug() << "Database closed";
    */
}

void MainWindow::setMyCentralWidget(QWidget *widget)
{
    centralWidget()->setParent( NULL );
    setCentralWidget(widget);
}

void MainWindow::createActions()
{
    aboutAct = new QAction(tr("&Sobre el programa"), this);
    aboutAct->setStatusTip(tr("Mostra informació sobre el programa"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("Sobre les &Qt"), this);
    aboutQtAct->setStatusTip(tr("Mostra informació sobre Qt"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    manageMembersAct = new QAction(tr("Gestiona els &socis"), this);
    manageMembersAct->setStatusTip(tr("Afegeix o edita la informació dels teus clients"));
    connect( manageMembersAct, SIGNAL( triggered() ), this, SLOT( onManageMembers()));

    manageCannabisAct = new QAction(tr("Consum de &cànnabis"), this);
    manageCannabisAct->setStatusTip(tr("Afegeix o edita la informació del cànnabis que demanen els socis"));
    connect( manageCannabisAct, SIGNAL( triggered() ), this, SLOT( onManageCannabis()));

    manageCansAct = new QAction(tr("Control dels pots de cànnabis"), this);
    manageCansAct->setStatusTip(tr("Afegeix o edita la informació dels pots contenidors de cànnabis"));
    connect(manageCansAct, SIGNAL(triggered()), this, SLOT(onManageCans()));

    otherBenefitsAct = new QAction(tr("&Altres consums"), this);
    otherBenefitsAct->setStatusTip(tr("Afegeix o edita la informació de les donacions"));
    connect( otherBenefitsAct, SIGNAL( triggered() ), this, SLOT( onManageOthers()));

    cashControlAct = new QAction(tr("Control de &caixa"), this);
    cashControlAct->setStatusTip(tr("Mostra un resum de l'estat de caixa."));
    connect( cashControlAct, SIGNAL( triggered() ), this, SLOT( onCashControl()));

    exportDatabaseAct = new QAction(tr("&Guarda com..."), this);
    exportDatabaseAct->setStatusTip(tr("Guarda les dades del programa en un fitxer"));
    connect(exportDatabaseAct, SIGNAL(triggered()), this, SLOT(onExportDB()));

    quitAct = new QAction(tr("&Sortir"), this);
    quitAct->setShortcuts(QKeySequence::Quit);
    quitAct->setStatusTip(tr("Surt de l'aplicació"));
    connect(quitAct, SIGNAL(triggered()), this, SLOT(onQuit()));
}

void MainWindow::onExportDB()
{
    QString dstFile = QFileDialog::getSaveFileName(this, tr("Cannabis-qt - Export your database"));

    QSqlDatabase db = QSqlDatabase::database();

    QFile::copy(db.databaseName(), dstFile);
}

void MainWindow::createMenus()
{
    dataMenu = menuBar()->addMenu(tr("&Dades"));
    dataMenu->addAction(exportDatabaseAct);
    dataMenu->addSeparator();
    dataMenu->addAction(quitAct);

    actionsMenu = menuBar()->addMenu(tr("&Accions"));
    actionsMenu->addAction(manageMembersAct);
    actionsMenu->addAction(manageCannabisAct);
    actionsMenu->addAction(manageCansAct);
    actionsMenu->addAction(otherBenefitsAct);
    // actionsMenu->addAction(cashControlAct);

    helpMenu = menuBar()->addMenu(tr("&Ajuda"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}

void MainWindow::createToolBars()
{
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Llest"));
}

void MainWindow::createCentralWidgets()
{
    // Main menu
    chooseOptionWidget = new ChooseOption();
    connect( chooseOptionWidget->membersButton, SIGNAL(pressed()), this, SLOT(onManageMembers()));
    connect( chooseOptionWidget->cannabisButton, SIGNAL(pressed()), this, SLOT(onManageCannabis()));
    connect( chooseOptionWidget->cansButton, SIGNAL(pressed()), this, SLOT(onManageCans()));
    connect( chooseOptionWidget->othersButton, SIGNAL(pressed()), this, SLOT(onManageOthers()));
    connect( chooseOptionWidget->cashButton, SIGNAL(pressed()), this, SLOT(onCashControl()));
    connect( chooseOptionWidget->quitButton, SIGNAL(pressed()), this, SLOT(onQuit()));

    membersWidget = new Members();
    connect(membersWidget->buttonBox, SIGNAL(accepted()), this, SLOT(onSaveMembers()));
    connect(membersWidget->buttonBox, SIGNAL(rejected()), this, SLOT(onMainMenu()));

    cannabisWidget = new Cannabis();
    connect(cannabisWidget->buttonBox, SIGNAL(accepted()), this, SLOT(onSaveCannabis()));
    connect(cannabisWidget->buttonBox, SIGNAL(rejected()), this, SLOT(onMainMenu()));

    cansWidget = new Cans();
    connect(cansWidget->buttonBox, SIGNAL(accepted()), this, SLOT(onSaveCans()));
    connect(cansWidget->buttonBox, SIGNAL(rejected()), this, SLOT(onMainMenu()));

    othersWidget = new Others();
    connect(othersWidget->buttonBox, SIGNAL(accepted()), this, SLOT(onSaveOthers()));
    connect(othersWidget->buttonBox, SIGNAL(rejected()), this, SLOT(onMainMenu()));

    cashControlWidget = new CashControl();
    connect(cashControlWidget->buttonBox, SIGNAL(accepted()), this, SLOT(onSaveCashControl()));
    connect(cashControlWidget->buttonBox, SIGNAL(rejected()), this, SLOT(onMainMenu()));
}

void MainWindow::print()
{
    /*
    #ifndef QT_NO_PRINTDIALOG
    QTextDocument *document = textEdit->document();
    QPrinter printer;

    QPrintDialog *dlg = new QPrintDialog(&printer, this);
    if (dlg->exec() != QDialog::Accepted)
     return;

    document->print(&printer);

    statusBar()->showMessage(tr("Ready"), 2000);
    #endif
    */
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("Sobre Cannabis-qt"),
             tr("The <b>Cannabis-qt</b> programa per gestionar "
                "un club social de cànnabis.<br><br>"
                "Versió ") + QString(PROGRAM_VERSION));
}

// ---------------------------------------------------------------------------------------------------------

void MainWindow::onQuit()
{
    QMessageBox msgBox;

    msgBox.setText("Està segur ?");

    msgBox.setIcon(QMessageBox::Information);

    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);

    // execute message box. method exec() return the button value of clicked button
    if (msgBox.exec() == QMessageBox::Yes)
    {
        qApp->quit();
    }
}

void MainWindow::onMainMenu()
{
    setMyCentralWidget(chooseOptionWidget);
}

void MainWindow::onManageMembers()
{
    setMyCentralWidget(membersWidget);
}

void MainWindow::onSaveMembers()
{
    if (membersWidget->save())
    {
        onMainMenu();
    }
}

void MainWindow::onManageCannabis()
{
    setMyCentralWidget(cannabisWidget);
}

void MainWindow::onSaveCannabis()
{
    if (cannabisWidget->save())
    {
        onMainMenu();
    }
}

void MainWindow::onManageCans()
{
    setMyCentralWidget(cansWidget);
}

void MainWindow::onSaveCans()
{
    if (cansWidget->save())
    {
        onMainMenu();
    }
}

void MainWindow::onManageOthers()
{
    setMyCentralWidget(othersWidget);
}

void MainWindow::onSaveOthers()
{
    if (othersWidget->save())
    {
        onMainMenu();
    }
}

void MainWindow::onCashControl()
{
    setMyCentralWidget(cashControlWidget);
}

void MainWindow::onSaveCashControl()
{
    onMainMenu();
}

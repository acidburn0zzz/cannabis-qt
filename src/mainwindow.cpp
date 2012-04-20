#define PROGRAM_VERSION "0.3alfa"

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

    qDebug() << QString("Application data will be stored in : %1").arg(appDataDir);

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

    setWindowTitle(tr("Cannabis-qt %1").arg(PROGRAM_VERSION));

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
    actions["about"] = new QAction(tr("&Sobre el programa"), this);
    actions["about"]->setStatusTip(tr("Mostra informació sobre el programa"));
    connect(actions["about"], SIGNAL(triggered()), this, SLOT(about()));

    actions["aboutQt"] = new QAction(tr("Sobre les &Qt"), this);
    actions["aboutQt"]->setStatusTip(tr("Mostra informació sobre Qt"));
    connect(actions["aboutQt"], SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    actions["manageMembers"] = new QAction(tr("Gestiona els &socis"), this);
    actions["manageMembers"]->setStatusTip(tr("Afegeix o edita la informació dels teus clients"));
    connect(actions["manageMembers"], SIGNAL( triggered() ), this, SLOT( onManageMembers()));

    actions["manageCannabis"] = new QAction(tr("Consum de &cànnabis"), this);
    actions["manageCannabis"]->setStatusTip(tr("Afegeix o edita la informació del cànnabis que demanen els socis"));
    connect(actions["manageCannabis"], SIGNAL( triggered() ), this, SLOT( onManageCannabis()));

    actions["manageCans"] = new QAction(tr("Control dels pots de cànnabis"), this);
    actions["manageCans"]->setStatusTip(tr("Afegeix o edita la informació dels pots contenidors de cànnabis"));
    connect(actions["manageCans"], SIGNAL(triggered()), this, SLOT(onManageCans()));

    actions["otherBenefits"] = new QAction(tr("&Altres consums"), this);
    actions["otherBenefits"]->setStatusTip(tr("Afegeix o edita la informació de les donacions"));
    connect(actions["otherBenefits"], SIGNAL( triggered() ), this, SLOT( onManageOthers()));

    actions["cashControl"] = new QAction(tr("Control de &caixa"), this);
    actions["cashControl"]->setStatusTip(tr("Mostra un resum de l'estat de caixa."));
    connect(actions["cashControl"], SIGNAL( triggered() ), this, SLOT( onCashControl()));

    actions["importDatabase"] = new QAction(tr("&Carrega..."), this);
    actions["importDatabase"]->setStatusTip(tr("Importa les dades d'un fitxer SQLITE"));
    connect(actions["importDatabase"], SIGNAL(triggered()), this, SLOT(onImportDB()));

    actions["exportDatabase"] = new QAction(tr("&Guarda com..."), this);
    actions["exportDatabase"]->setStatusTip(tr("Guarda les dades del programa en un fitxer SQLITE"));
    connect(actions["exportDatabase"], SIGNAL(triggered()), this, SLOT(onExportDB()));

    actions["quit"] = new QAction(tr("&Sortir"), this);
    actions["quit"]->setShortcuts(QKeySequence::Quit);
    actions["quit"]->setStatusTip(tr("Surt de l'aplicació"));
    connect(actions["quit"], SIGNAL(triggered()), this, SLOT(onQuit()));
}

void MainWindow::createMenus()
{
    dataMenu = menuBar()->addMenu(tr("&Dades"));
    dataMenu->addAction(actions["importDatabase"]);
    dataMenu->addAction(actions["exportDatabase"]);
    dataMenu->addSeparator();
    dataMenu->addAction(actions["quit"]);

    actionsMenu = menuBar()->addMenu(tr("&Accions"));
    actionsMenu->addAction(actions["manageMembers"]);
    actionsMenu->addAction(actions["manageCannabis"]);
    actionsMenu->addAction(actions["manageCans"]);
    actionsMenu->addAction(actions["otherBenefits"]);
    actionsMenu->addAction(actions["cashControl"]);

    helpMenu = menuBar()->addMenu(tr("&Ajuda"));
    helpMenu->addAction(actions["about"]);
    helpMenu->addAction(actions["aboutQt"]);
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
        tr("<b>Cannabis-qt</b> és un senzill programa de gestió d'un local social "
           "on es pugui dispensar cànnabis mitjançant un control estricte.<br/><br/>"
           "El programa està fet amb les llibreríes QT : <a href='http://qt.nokia.com'>qt.nokia.com</a><br/><br/>"
           "La web del programa : <a href='http://karasu.github.com/cannabis-qt'>karasu.github.com/cannabis-qt</a><br/><br/>"
           "El programa permet:<br/><br/>"
           "\t- Gestionar els socis<br/>"
           "\t- Gestionar els pots de cànnabis<br/>"
           "\t- Gestionar el consum dels socis (ja sigui del consum propi de cànnabis o d'altres col·laboracions amb l'associació<br/>"
           "\t- Controlar els ingressos de l'associació i imprimir informes per portar al gestor<br/>"
           "\t- Importació i exportació de les dades (SQLITE)<br/><br/>"
           "Versió %1<br/>"
           "Fet per Karasu.").arg(PROGRAM_VERSION));
}

// ---------------------------------------------------------------------------------------------------------

void MainWindow::onQuit()
{
    QMessageBox msgBox(this);

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
    // No hem de guardar res, però esborrem les dades per no confondre a l'usuari quan torni
    // a entrar a aquest widget

    cashControlWidget->clear();

    onMainMenu();
}

void MainWindow::onExportDB()
{
    QString dstFile = QFileDialog::getSaveFileName(this, tr("Cannabis-qt - Export your database"));

    QSqlDatabase db = QSqlDatabase::database();

    QFile::copy(db.databaseName(), dstFile);
}

void MainWindow::onImportDB()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Cannabis-qt - Import your database"));

    qDebug() << filePath;

    QSqlDatabase db = QSqlDatabase::database();

    // save changes before replacing our database
    db.commit();
    db.close();
    QString connectionName = QSqlDatabase::database().connectionName();
    db.removeDatabase(connectionName);
    // QSqlDatabase::removeDatabase(connectionName);

    // open our new database
    if (!dbManager.openDB(filePath))
    {
        qDebug() << QString("Error: can't open database.").arg(filePath);
        QMessageBox::critical(this, tr("Cannabis-qt"),
                              tr("Error crític: No puc obrir la base de dades %1.").arg(filePath));
    }
}

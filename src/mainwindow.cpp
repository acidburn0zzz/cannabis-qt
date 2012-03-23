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

    // Init our db (just for checking)
    if (!db.openDB())
    {
        qDebug() << "Error: can't create/open database.";
        QMessageBox::critical(this, tr("Cannabis-qt Application"),
                              tr("Critical error: Can't open database. Please get in touch with your dealer for further help."));
        qApp->quit();
    }

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    createCentralWidgets();

    setWindowTitle(tr("Cannabis-qt"));

    setCentralWidget(chooseOptionWidget);

    resize( QSize(700, 500).expandedTo(minimumSizeHint()) );

    setMinimumSize(600, 400);
}

MainWindow::~MainWindow()
{
    db.closeDB();
}

void MainWindow::setMyCentralWidget(QWidget *widget)
{
    centralWidget()->setParent( NULL );
    setCentralWidget(widget);
}

void MainWindow::createActions()
{
    aboutAct = new QAction(tr("&Sobre el progama"), this);
    aboutAct->setStatusTip(tr("Mostra informació sobre el programa"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("Sobre les &Qt"), this);
    aboutQtAct->setStatusTip(tr("Mostra informació sobre Qt"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    manageMembersAct = new QAction(tr("Gestiona els &socis"), this);
    manageMembersAct->setStatusTip(tr("Afegeix o edita la informació dels teus clients"));
    connect( manageMembersAct, SIGNAL( triggered() ), this, SLOT( onManageMembers()));

    manageCannabisAct = new QAction(tr("Consum de &cannabis"), this);
    manageCannabisAct->setStatusTip(tr("Afegeix o edita la informació del cannabis que demanen els socis"));
    connect( manageCannabisAct, SIGNAL( triggered() ), this, SLOT( onManageCannabis()));

    otherBenefitsAct = new QAction(tr("&Altres consums"), this);
    otherBenefitsAct->setStatusTip(tr("Afegeix o edita la informació de les donacions"));
    connect( otherBenefitsAct, SIGNAL( triggered() ), this, SLOT( onManageOthers()));

    cashControlAct = new QAction(tr("Control de &caixa"), this);
    cashControlAct->setStatusTip(tr("Mostra un resum de l'estat de caixa."));
    connect( cashControlAct, SIGNAL( triggered() ), this, SLOT( onCashControl()));

    quitAct = new QAction(tr("&Sortir"), this);
    quitAct->setShortcuts(QKeySequence::Quit);
    quitAct->setStatusTip(tr("Surt de l'aplicació"));
    connect(quitAct, SIGNAL(triggered()), this, SLOT(onQuit()));
}

void MainWindow::createMenus()
{
    actionsMenu = menuBar()->addMenu(tr("&Accions"));
    actionsMenu->addAction(manageMembersAct);
    actionsMenu->addAction(manageCannabisAct);
    actionsMenu->addAction(otherBenefitsAct);
    actionsMenu->addAction(cashControlAct);
    actionsMenu->addSeparator();
    actionsMenu->addAction(quitAct);

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
    connect( chooseOptionWidget->othersButton, SIGNAL(pressed()), this, SLOT(onManageOthers()));
    connect( chooseOptionWidget->cashButton, SIGNAL(pressed()), this, SLOT(onCashControl()));
    connect( chooseOptionWidget->quitButton, SIGNAL(pressed()), this, SLOT(onQuit()));

    membersWidget = new Members();
    connect(membersWidget->buttonBox, SIGNAL(accepted()), this, SLOT(onSaveMembers()));
    connect(membersWidget->buttonBox, SIGNAL(rejected()), this, SLOT(onMainMenu()));

    cannabisWidget = new Cannabis();
    connect(cannabisWidget->buttonBox, SIGNAL(accepted()), this, SLOT(onSaveCannabis()));
    connect(cannabisWidget->buttonBox, SIGNAL(rejected()), this, SLOT(onMainMenu()));

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
                "un club social de cannabis. "
                "Creat per Sandra Castells."));
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
    if (cashControlWidget->save())
    {
        onMainMenu();
    }
}

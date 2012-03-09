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

    setMyStyleSheet();

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

void MainWindow::setMyStyleSheet()
{
/*
    setStyleSheet("QRadioButton { font: bold 18px; }"
                  //"QRadioButton::indicator { width: 40px; height: 40px; }"
                  "QLabel { font: bold 14px; padding-left:42px; }");
*/
    setStyleSheet("QPushButton {"
            "color: white;"
            "background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #44d, stop: 0.1 #99e, stop: 0.49 #77c, stop: 0.5 #66b, stop: 1 #77c);"
            "border-width: 1px;"
            "border-color: #339;"
            "border-style: solid;"
            "border-radius: 7;"
            "padding: 3px;"
            "font-size: 18px;"
            "padding-left: 5px;"
            "padding-right: 5px;"
            "min-width: 50px;"
            // "max-width: 10px;"
            "min-height: 30px;"
            "max-height: 60px; }"
        "QGroupBox { border: 2px solid gray; border-radius: 6px; }");
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

    manageCannabisAct = new QAction(tr("Gestiona el &cannabis"), this);
    manageCannabisAct->setStatusTip(tr("Afegeix o edita la informació del cannabis que demanen els socis"));
    connect( manageMembersAct, SIGNAL( triggered() ), this, SLOT( onManageCannabis()));

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

    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);

    // execute message box. method exec() return the button value of clicked button
    if (msgBox.exec() == QMessageBox::Ok)
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
{}

void MainWindow::onCashControl()
{
    setMyCentralWidget(cashControlWidget);
}

void MainWindow::onSaveCashControl()
{}

/*
    Cannabis-qt
    Copyright (C) 2012 Karasu

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "mainwindow.h"
#include "about.h"
#include "constants.h"

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
        // It doesn't exist, we have to create it.
        if (!QDir().mkpath(appDataDir))
        {
            // Can't create directory, try to use application one (this may work in windows)
            appDataDir = QCoreApplication::applicationFilePath();
        }
    }

    qDebug() << QString("Application data will be stored in : %1").arg(appDataDir);

    // Open our database
    if (dbManager.openDB())
    {
        qDebug() << tr("Error: can't create/open database in %1").arg(appDataDir);
        QMessageBox::critical(this, tr("Cannabis-qt"),
                              tr("Error crític: No puc obrir la base de dades.\n"
                                 "Si us plau, posi's en contacte amb el seu distribuidor "
                                 "per a obtenir ajuda\n\n"
                                 "Directori de dades: %1").arg(appDataDir));
        qApp->quit();
        qFatal("Can't create/open database file!");
    }

    qApp->setAttribute(Qt::AA_DontShowIconsInMenus, false);

    createActions();
    createMenus();
    createToolBar();
    createStatusBar();
    createCentralWidgets();

    setWindowTitle(tr("Cannabis-qt %1").arg(PROGRAM_VERSION));

    setCentralWidget(chooseOptionWidget);

    QSettings settings;

    QSize size(settings.value("MainWindow/size", QSize(850, 500)).toSize());
    resize( size.expandedTo(minimumSizeHint()) );

    move(settings.value("MainWindow/pos", QPoint(200, 200)).toPoint());

    setMinimumSize(600,400);

    // QIcon::setThemeName("Faenza-Cupertino");
    // QIcon::setThemeName("Faenza");

    if (!QIcon::hasThemeIcon("document-open"))
    {
        qDebug() << "If there is no default working icon theme then we should "
        "use an icon theme that we provide via a .qrc file\n"
        "This case happens under Windows and Mac OS X "
        "but not under GNOME or KDE";
        QIcon::setThemeName("elementary");
    }

    qDebug() << tr("Using '%1' icon theme").arg(QIcon::themeName());
}

MainWindow::~MainWindow()
{
    QSettings settings;

    settings.setValue("MainWindow/size", size());
    settings.setValue("MainWindow/pos", pos());
}

void MainWindow::setMyCentralWidget(QWidget *widget)
{
    if (centralWidget() != 0)
    {
        centralWidget()->setParent(NULL);
    }

    setCentralWidget(widget);
}

void MainWindow::createActions()
{
    actions["about"] = new QAction(tr("&Sobre el programa"), this);
    actions["about"]->setStatusTip(tr("Mostra informació sobre el programa"));
    actions["about"]->setIcon(QIcon::fromTheme("help-about", QIcon(":/icons/elementary/actions/16/help-about")));
    actions["about"]->setIconVisibleInMenu(true);
    connect(actions["about"], SIGNAL(triggered()), this, SLOT(about()));

    actions["aboutQt"] = new QAction(tr("Sobre les &Qt"), this);
    actions["aboutQt"]->setStatusTip(tr("Mostra informació sobre Qt"));
    actions["aboutQt"]->setIcon(QIcon(":/icons/qtlogo"));
    actions["aboutQt"]->setIconVisibleInMenu(true);
    connect(actions["aboutQt"], SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    actions["manageMembers"] = new QAction(tr("Gestiona els &socis"), this);
    actions["manageMembers"]->setStatusTip(tr("Afegeix o edita la informació dels teus clients"));
    actions["manageMembers"]->setIcon(QIcon::fromTheme("notification-message-im", QIcon(":/icons/elementary/notifications/48/notification-message-im")));
    actions["manageMembers"]->setIconVisibleInMenu(true);
    connect(actions["manageMembers"], SIGNAL( triggered() ), this, SLOT( onMembers()));

    actions["manageCannabis"] = new QAction(tr("Consum de &cànnabis"), this);
    actions["manageCannabis"]->setStatusTip(tr("Afegeix o edita la informació del cànnabis que demanen els socis"));
    actions["manageCannabis"]->setIcon(QIcon(":/icons/leaf-icon"));
    actions["manageCannabis"]->setIconVisibleInMenu(true);
    connect(actions["manageCannabis"], SIGNAL( triggered() ), this, SLOT( onCannabis()));

    actions["manageCans"] = new QAction(tr("Control dels pots de cànnabis"), this);
    actions["manageCans"]->setStatusTip(tr("Afegeix o edita la informació dels pots contenidors de cànnabis"));
    actions["manageCans"]->setIcon(QIcon(":/icons/container"));
    actions["manageCans"]->setIconVisibleInMenu(true);
    connect(actions["manageCans"], SIGNAL(triggered()), this, SLOT(onCans()));

    actions["otherBenefits"] = new QAction(tr("&Altres consums"), this);
    actions["otherBenefits"]->setStatusTip(tr("Afegeix o edita la informació de les donacions"));
    actions["otherBenefits"]->setIcon(QIcon(":/icons/others"));
    actions["otherBenefits"]->setIconVisibleInMenu(true);
    connect(actions["otherBenefits"], SIGNAL( triggered() ), this, SLOT( onOthers()));

    actions["cashControl"] = new QAction(tr("Control de &caixa"), this);
    actions["cashControl"]->setStatusTip(tr("Mostra un resum de l'estat de caixa."));
    actions["cashControl"]->setIcon(QIcon(":/icons/cashbox"));
    actions["cashControl"]->setIconVisibleInMenu(true);
    connect(actions["cashControl"], SIGNAL( triggered() ), this, SLOT( onCashControl()));

    actions["importDatabase"] = new QAction(tr("&Carrega..."), this);
    actions["importDatabase"]->setStatusTip(tr("Importa les dades d'un fitxer SQLITE"));
    actions["importDatabase"]->setIcon(QIcon::fromTheme("document-open", QIcon(":/icons/elementary/actions/16/document-open")));
    actions["importDatabase"]->setIconVisibleInMenu(true);
    connect(actions["importDatabase"], SIGNAL(triggered()), this, SLOT(onImportDB()));

    actions["exportDatabase"] = new QAction(tr("&Guarda com..."), this);
    actions["exportDatabase"]->setStatusTip(tr("Guarda les dades del programa en un fitxer SQLITE"));
    actions["exportDatabase"]->setIcon(QIcon::fromTheme("document-save-as", QIcon(":/icons/elementary/actions/16/document-save-as")));
    actions["exportDatabase"]->setIconVisibleInMenu(true);
    connect(actions["exportDatabase"], SIGNAL(triggered()), this, SLOT(onExportDB()));

    actions["quit"] = new QAction(tr("&Sortir"), this);
    actions["quit"]->setShortcuts(QKeySequence::Quit);
    actions["quit"]->setStatusTip(tr("Surt de l'aplicació"));
    actions["quit"]->setIcon(QIcon::fromTheme("application-exit", QIcon(":/icons/elementary/actions/16/application-exit")));
    actions["quit"]->setIconVisibleInMenu(true);

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

void MainWindow::createToolBar()
{
    toolbar = addToolBar("Cannabis-qt");
    toolbar->addAction(actions["importDatabase"]);
    toolbar->addAction(actions["exportDatabase"]);
    toolbar->addSeparator();
    toolbar->addAction(actions["manageMembers"]);
    toolbar->addAction(actions["manageCannabis"]);
    toolbar->addAction(actions["manageCans"]);
    toolbar->addAction(actions["otherBenefits"]);
    toolbar->addAction(actions["cashControl"]);
    toolbar->addSeparator();
    // toolbar->addAction(actions["about"]);
    // toolbar->addAction(actions["aboutQt"]);
    // toolbar->addSeparator();
    toolbar->addAction(actions["quit"]);

    // menuButton = new QPushButton(tr("Menú"));
    // toolbar->addSeparator();
    // toolbar->addWidget(menuButton);
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Llest"));
}

void MainWindow::createCentralWidgets()
{
    // Main menu
    chooseOptionWidget = new ChooseOption();
    connect(chooseOptionWidget->buttons["members"], SIGNAL(pressed()), this, SLOT(onMembers()));
    connect(chooseOptionWidget->buttons["cannabis"], SIGNAL(pressed()), this, SLOT(onCannabis()));
    connect(chooseOptionWidget->buttons["cans"], SIGNAL(pressed()), this, SLOT(onCans()));
    connect(chooseOptionWidget->buttons["others"], SIGNAL(pressed()), this, SLOT(onOthers()));
    connect(chooseOptionWidget->buttons["cash"], SIGNAL(pressed()), this, SLOT(onCashControl()));
    connect(chooseOptionWidget->buttons["quit"], SIGNAL(pressed()), this, SLOT(onQuit()));

    membersWidget = new Members();
    connect(membersWidget->buttonBox, SIGNAL(rejected()), this, SLOT(onMainMenu()));

    cannabisWidget = new Cannabis();
    connect(cannabisWidget->buttonBox, SIGNAL(rejected()), this, SLOT(onMainMenu()));

    cansWidget = new Cans();
    connect(cansWidget->buttonBox, SIGNAL(rejected()), this, SLOT(onMainMenu()));

    othersWidget = new Others();
    connect(othersWidget->buttonBox, SIGNAL(rejected()), this, SLOT(onMainMenu()));

    cashControlWidget = new CashControl();
    connect(cashControlWidget->buttonBox, SIGNAL(rejected()), this, SLOT(onMainMenu()));
}

void MainWindow::destroyCentralWidgets()
{
    setMyCentralWidget(NULL);

    delete chooseOptionWidget;
    chooseOptionWidget = NULL;

    delete membersWidget;
    membersWidget = NULL;

    delete cannabisWidget;
    cannabisWidget = NULL;

    delete cansWidget;
    cansWidget = NULL;

    delete othersWidget;
    othersWidget = NULL;

    delete cashControlWidget;
    cashControlWidget = NULL;
}

void MainWindow::about()
{
    About about(this);

    about.exec();
}

// ---------------------------------------------------------------------------------------------------------

void MainWindow::onQuit()
{
    QMessageBox msgBox(this);

    msgBox.setText(tr("Està segur ?"));

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

void MainWindow::onMembers()
{
    setMyCentralWidget(membersWidget);
}

void MainWindow::onCannabis()
{
    setMyCentralWidget(cannabisWidget);
}

void MainWindow::onCans()
{
    setMyCentralWidget(cansWidget);
}

void MainWindow::onOthers()
{
    setMyCentralWidget(othersWidget);
}

void MainWindow::onCashControl()
{
    setMyCentralWidget(cashControlWidget);
}

// ---------------------------------------------------------------------------------------------------------

void MainWindow::onExportDB()
{
    QString dstFile = QFileDialog::getSaveFileName(this, tr("Cannabis-qt - Export your database"));

    if (!dstFile.isEmpty())
    {
        QSqlDatabase db = QSqlDatabase::database();

        QFile::copy(db.databaseName(), dstFile);
    }
}

void MainWindow::onImportDB()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Cannabis-qt - Import your database"));

    if (!filePath.isEmpty())
    {
        qDebug() << filePath;

        destroyCentralWidgets();

        QSqlDatabase::database().close();
        QString connectionName = QSqlDatabase::database().connectionName();
        QSqlDatabase::removeDatabase(connectionName);

        // open our new database
        if (!dbManager.openDB(filePath))
        {
            qDebug() << QString("Error: can't open database.").arg(filePath);
            QMessageBox::critical(this, tr("Cannabis-qt"),
                                  tr("Error crític: No puc obrir la base de dades %1.").arg(filePath));
        }

        createCentralWidgets();

        setMyCentralWidget(chooseOptionWidget);
    }
}

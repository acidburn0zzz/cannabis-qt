#include "mainwindow.h"
#include "ui_mainwindow.h"

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

    //    ui->setupUi(this);

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

    setWindowTitle(tr("Sandra-qt"));

    // setCentralWidget(chooseOptionWidget);

    resize( QSize(600, 400).expandedTo(minimumSizeHint()) );

    setMinimumSize(600, 400);
}

MainWindow::~MainWindow()
{
//    delete ui;
}

void MainWindow::setMyStyleSheet()
{}

void MainWindow::createActions()
{}

void MainWindow::createMenus()
{}

void MainWindow::createToolBars()
{}

void MainWindow::createStatusBar()
{}

void MainWindow::createCentralWidgets()
{}

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
    QMessageBox::about(this, tr("About Sandra-qt"),
             tr("The <b>Sandra-qt</b> program demonstrates how to "
                "use Qt's dock widgets. You can enter your own text, "
                "click a customer to add a customer name and "
                "address, and click standard paragraphs to add them."));
}



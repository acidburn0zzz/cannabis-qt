#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QTextCodec>
#include <QDebug>

#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QScrollArea>

#include <QDesktopServices>

#include "databasemanager.h"

#include "chooseoption.h"
#include "members.h"
#include "cannabis.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    DatabaseManager db;

private slots:
    void print();
    void about();

private:
     void createActions();
     void createMenus();
     void createToolBars();
     void createStatusBar();
     void createCentralWidgets();

     void setMyCentralWidget(QWidget *widget);

     QMenu *actionsMenu;
     QMenu *helpMenu;

     QAction *aboutAct;
     QAction *aboutQtAct;
     QAction *quitAct;
     QAction *manageMembersAct;
     QAction *manageCannabisAct;
     QAction *otherBenefitsAct;
     QAction *cashControlAct;

     ChooseOption *chooseOptionWidget;
     Members *membersWidget;
     Cannabis *cannabisWidget;

public slots:
     void onQuit();

     void onManageMembers();
     void onSaveMembers();

     void onManageCannabis();
     void onSaveCannabis();

     void onOtherBenefits();
     void onSaveOtherBenefits();

     void onCashControl();
     void onSaveCashControl();

     void onMainMenu();

};

#endif // MAINWINDOW_H

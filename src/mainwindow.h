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
#include <QFileDialog>
#include <QMap>
#include <QSettings>

#include <QtSvg>

#include "databasemanager.h"

#include "chooseoption.h"
#include "members.h"
#include "cannabis.h"
#include "others.h"
#include "cashcontrol.h"
#include "cans.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    DatabaseManager dbManager;

private slots:
    void about();

private:
     void createActions();
     void createMenus();
     void createToolBars();
     void createStatusBar();
     void createCentralWidgets();
     void destroyCentralWidgets();

     void setMyCentralWidget(QWidget *widget);

     QMenu *actionsMenu;
     QMenu *dataMenu;
     QMenu *helpMenu;

     QMap <QString, QAction *> actions;

     ChooseOption *chooseOptionWidget;
     Members *membersWidget;
     Cannabis *cannabisWidget;
     Cans *cansWidget;
     Others *othersWidget;
     CashControl *cashControlWidget;

public slots:
     void onQuit();

     void onManageMembers();
     void onSaveMembers();

     void onManageCannabis();
     void onSaveCannabis();

     void onManageCans();
     void onSaveCans();

     void onManageOthers();
     void onSaveOthers();

     void onCashControl();
     void onSaveCashControl();

     void onMainMenu();

     void onImportDB();
     void onExportDB();

};

#endif // MAINWINDOW_H

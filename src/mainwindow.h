#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

private:
    // Ui::MainWindow *ui;

private slots:
    void print();
    void about();

private:
     void createActions();
     void createMenus();
     void createToolBars();
     void createStatusBar();
     void createCentralWidgets();

     void setMyStyleSheet(void);

     QMenu *fileMenu;
     QMenu *editMenu;
     QMenu *viewMenu;
     QMenu *helpMenu;
};

#endif // MAINWINDOW_H

#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setOrganizationDomain("sandra");
    a.setOrganizationName("sandra");
    a.setApplicationName("cannabis-qt");

    MainWindow w;
    w.show();
    
    return a.exec();
}

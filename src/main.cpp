#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setOrganizationDomain("Sandra");
    a.setOrganizationName("Sandra");
    a.setApplicationName("Cannabis-qt");

    MainWindow w;
    w.show();
    
    return a.exec();
}

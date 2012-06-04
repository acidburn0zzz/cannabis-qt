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

#include <QtGui/QApplication>
#include "mainwindow.h"

void myMessageOutput(QtMsgType type, const char *msg)
{
    switch (type) {
    case QtDebugMsg:
        fprintf(stdout, "Debug: %s\n", msg);
        break;
    case QtWarningMsg:
        fprintf(stdout, "Warning: %s\n", msg);
        break;
    case QtCriticalMsg:
        fprintf(stdout, "Critical: %s\n", msg);
        break;
    case QtFatalMsg:
        fprintf(stdout, "Fatal: %s\n", msg);
        abort();
    }
}

int main(int argc, char *argv[])
{
    qInstallMsgHandler(myMessageOutput);

    QApplication a(argc, argv);

    a.setOrganizationDomain("sandra");
    a.setOrganizationName("sandra");
    a.setApplicationName("cannabis-qt");

    a.setWindowIcon(QIcon(":/icons/cannabis-qt"));

    MainWindow w;
    w.show();
    
    return a.exec();
}

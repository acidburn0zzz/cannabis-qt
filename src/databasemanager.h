#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include <QFile>
#include <QTextStream>
#include <QDir>

#include <QMessageBox>
#include <QDebug>

#include <QDesktopServices>

class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseManager(QObject *parent = 0);
    ~DatabaseManager();

    bool createDB(void);
    bool openDB(QString filePath="");
    void closeDB();

signals:

public slots:

};

#endif // DATABASEMANAGER_H

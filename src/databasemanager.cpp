#include "databasemanager.h"

DatabaseManager::DatabaseManager(QObject *parent) :
    QObject(parent)
{
}

DatabaseManager::~DatabaseManager()
{
    closeDB();
}

bool DatabaseManager::openDB()
{
    if (!QSqlDatabase::contains())
    {
        // Find QSLite driver
        db = QSqlDatabase::addDatabase("QSQLITE");

        // Set database file name and path
        QString path(QDesktopServices::storageLocation(QDesktopServices::DataLocation));
        path.append(QDir::separator()).append("cannabis-qt.sqlite3");
        path = QDir::toNativeSeparators(path);
        db.setDatabaseName(path);

        qDebug() << "Database file : " + path;

        QFile dbFile(db.databaseName());

        if (!dbFile.exists())
        {
            qDebug() << "database does not exist. I'll try to create it.";

            if (!createDB())
            {
                return false;
            }
        }
        else
        {
            qDebug() << "OK, database already exists.";
        }

        // Open databasee

        if (!db.open())
        {
            qDebug() << db.lastError().text();
            return false;
        }
    }
    else
    {
        db = QSqlDatabase::database();
    }

    return true;
}

bool DatabaseManager::createDB()
{
    if (!db.open())
    {
        qDebug() << db.lastError().text();
        return false;
    }

    QFile sqlFile(":/cannabis-qt.sql");

    if (sqlFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString sql = "";
        QTextStream in(&sqlFile);
        QSqlQuery qry;

        // qry.prepare(in.readAll());

        while (!in.atEnd())
        {
           QString line = in.readLine();
           sql += line;

           if (line.contains(';'))
           {
               qDebug() << sql;

               if (!qry.exec(sql))
               {
                   qDebug() << qry.lastError().text();
                   db.close();
                   return false;
               }

               sql = "";
           }
        }

        sqlFile.close();

        db.close();

        return true;
    }
    else
    {
        return false;
    }
}

void DatabaseManager::closeDB()
{
    if (db.isOpen())
    {
        db.close();
    }
}

#include "databasemanager.h"

DatabaseManager::DatabaseManager(QObject *parent) :
    QObject(parent)
{
}

DatabaseManager::~DatabaseManager()
{
    //closeDB();

    QSqlDatabase db = QSqlDatabase::database();
    QString connectionName = db.connectionName();
    db.close();
    QSqlDatabase::removeDatabase(connectionName);
}

bool DatabaseManager::openDB()
{
    if (!QSqlDatabase::contains())
    {
        // Find QSLite driver
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

        // Set database file name and path
        QString path(QDesktopServices::storageLocation(QDesktopServices::DataLocation));
        path.append(QDir::separator()).append("cannabis-qt.sqlite3");
        path = QDir::toNativeSeparators(path);
        db.setDatabaseName(path);

        qDebug() << "Database file : " + path;

        QFile dbFile(db.databaseName());

        if (!dbFile.exists() || dbFile.size() <= 0)
        {
            qDebug() << "database does not exist or is corrputed. I'll try to create it.";

            if (!createDB())
            {
                qDebug() << "ERROR: Can't create a new database!";
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
            qDebug() << "ERROR: Can't open database!";
            qDebug() << db.lastError().text();
            return false;
        }
    }

    return true;
}

bool DatabaseManager::createDB()
{
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

           if (line.startsWith('#'))
           {
               qDebug() << line;
           }
           else
           {
               sql += line;

               if (line.contains(';'))
               {
                   qDebug() << sql;

                   if (!qry.exec(sql))
                   {
                       qDebug() << qry.lastError().text();
                       return false;
                   }

                   sql = "";
               }
           }
        }

        sqlFile.close();
        return true;
    }
    else
    {
        return false;
    }
}

void DatabaseManager::closeDB()
{
    QSqlDatabase.
    QSqlDatabase::database().close();
    QString connectionName = QSqlDatabase::database().connectionName();
    QSqlDatabase::removeDatabase(connectionName);
}


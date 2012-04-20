#include "databasemanager.h"
#include "constants.h"

DatabaseManager::DatabaseManager(QObject *parent) :
    QObject(parent)
{
}

DatabaseManager::~DatabaseManager()
{
    closeDB();
}

bool DatabaseManager::openDB(QString filePath)
{
    if (!QSqlDatabase::contains())
    {
        // Find QSLite driver
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", DB_CONNECTION_NAME);

        if (filePath.isEmpty())
        {
            // Set database file name and path
            filePath = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
            filePath.append(QDir::separator()).append("cannabis-qt.sqlite3");
        }

        filePath = QDir::toNativeSeparators(filePath);
        db.setDatabaseName(filePath);

        qDebug() << QString("Database file : %1").arg(filePath);

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
    QSqlDatabase db = QSqlDatabase::database(DB_CONNECTION_NAME);

    // Db does not exist, or is corrupted. Open a new one and fill it.
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
        QSqlQuery qry(db);

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
                       sqlFile.close();
                       db.close();
                       return false;
                   }

                   sql = "";
               }
           }
        }

        sqlFile.close();
        db.close();

        return true;
    }
    else
    {
        db.close();
        return false;
    }
}

void DatabaseManager::closeDB()
{
    qDebug() << "Closing database";
    QSqlDatabase::database().close();
    QString connectionName = QSqlDatabase::database().connectionName();
    QSqlDatabase::removeDatabase(connectionName);
    qDebug() << "Database closed";
}


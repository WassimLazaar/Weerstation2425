#include "mainwindow.h"

#include <QApplication>
#include <QtSql>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*
    //accessing the database:
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("");
    db.setDatabaseName("weerstation");
    db.open();

    QSqlQuery query;
    if (query.exec("select ID, TEMPERATURE, HUMIDITY, PRESSURE, TIMESTAMP from tbldata ;"))
    {
        while(query.next())
        {
            qInfo() << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() << query.value(3).toString() << query.value(4).toString();
        }
    }
    else
    {
        qInfo()<<"test failed";
    }

    db.close();
*/

    MainWindow w;
    w.show();
    return a.exec();
}

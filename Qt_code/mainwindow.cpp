#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // open databse:
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("");
    db.setDatabaseName("weerstation");
    //db.open();

    // display latest measurement:
    /*model = new QSqlTableModel(this);
    model->setTable("tbldata");
    model->setFilter("TIMESTAMP=(SELECT MAX(TIMESTAMP)FROM tbldata)");
    model->select();

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();*/
}

MainWindow::~MainWindow()
{
    // close database:
    //db.close();

    delete ui;
}

// button for showing all data
void MainWindow::on_ButtonAll_clicked()
{
    db.open();
    model = new QSqlTableModel(this);
    model->setTable("tbldata");
    model->select();

    //set column names:
    model->setHeaderData(1,Qt::Horizontal,"TEMPERATUUR");
    model->setHeaderData(2,Qt::Horizontal,"LUCHTVOCHTIGHEID");
    model->setHeaderData(3,Qt::Horizontal,"LUCHTDRUK");
    model->setHeaderData(4,Qt::Horizontal,"TIJDSTIP");

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    db.close();
}

// button for showing latest data
void MainWindow::on_ButtonLatest_clicked()
{
    db.open();
    model = new QSqlTableModel(this);
    model->setTable("tbldata");
    model->setFilter("TIMESTAMP=(SELECT MAX(TIMESTAMP)FROM tbldata)");
    model->select();

    //set column names:
    model->setHeaderData(1,Qt::Horizontal,"TEMPERATUUR");
    model->setHeaderData(2,Qt::Horizontal,"LUCHTVOCHTIGHEID");
    model->setHeaderData(3,Qt::Horizontal,"LUCHTDRUK");
    model->setHeaderData(4,Qt::Horizontal,"TIJDSTIP");

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    db.close();
}


void MainWindow::on_ButtonGraphView_clicked()
{
    GraphView graphview;
    graphview.exec();
}


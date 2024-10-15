#include "graphview.h"
#include "ui_graphview.h"

GraphView::GraphView(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::GraphView)
{
    ui->setupUi(this);


    //setup database
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("");
    db.setDatabaseName("weerstation");


    // creating a series for data:
    QLineSeries *tempSeries = new QLineSeries();
    QLineSeries *humSeries = new QLineSeries();
    QLineSeries *presSeries = new QLineSeries();


    // getting values from database and adding to series:
    db.open();

    QDateTime time;
    QSqlQuery query;
    query.exec("select TIMESTAMP, TEMPERATURE, HUMIDITY, PRESSURE from tbldata ;");
    while (query.next())
    {
        time = query.value(0).toDateTime();
        tempSeries->append(time.toMSecsSinceEpoch(),query.value(1).toFloat());
        humSeries->append(time.toMSecsSinceEpoch(),query.value(2).toFloat());
        presSeries->append(time.toMSecsSinceEpoch(),query.value(3).toFloat());
    }

    db.close();


    // displaying chart:
    QDateTimeAxis *axisx = new QDateTimeAxis;
    axisx->setFormat("dd.MM.yyyy hh:mm:ss");
    QValueAxis *axisTemp = new QValueAxis;
    QValueAxis *axisHum = new QValueAxis;
    QValueAxis *axisPres = new QValueAxis;

    QChart *chart = new QChart();
    chart->addSeries(tempSeries);
    chart->addSeries(humSeries);
    chart->addSeries((presSeries));
    //chart->legend()->hide();

    chart->addAxis(axisx,Qt::AlignBottom);
    tempSeries->attachAxis(axisx);
    humSeries->attachAxis(axisx);
    presSeries->attachAxis(axisx);

    chart->addAxis(axisTemp,Qt::AlignLeft);
    chart->addAxis(axisHum,Qt::AlignLeft);
    chart->addAxis(axisPres,Qt::AlignLeft);
    tempSeries->attachAxis(axisTemp);
    humSeries->attachAxis(axisHum);
    presSeries->attachAxis(axisPres);

    QChartView *chartview = new QChartView(chart);
    chartview->setParent(ui->horizontalFrame);
}

GraphView::~GraphView()
{
    delete ui;
}

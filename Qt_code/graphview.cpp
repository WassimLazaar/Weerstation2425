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


    // creating a line chart:
    QLineSeries *series = new QLineSeries();


    // getting values from database:
    db.open();

    QDateTime time;
    QSqlQuery query;
    query.exec("select ID, TEMPERATURE, HUMIDITY, PRESSURE, TIMESTAMP from tbldata ;");
    while (query.next())
    {
       /* time.setDate(query.value(4).toDateTime().date());
        time.setTime(query.value(4).toDateTime().time());*/
        time = query.value(4).toDateTime();
        qInfo() << time ;
        series->append(time.toMSecsSinceEpoch(),query.value(1).toFloat());
       // qInfo() << query.value(4).toString();
       // qInfo() << query.value(4).toDateTime();
        //qInfo() << query.value(4).toDateTime().date();
    }

    auto *axisx = new QDateTimeAxis;
    axisx->setFormat("dd.MM.yyyy hh:mm:ss");
    auto *axisy = new QValueAxis;

    db.close();

    /*series->append(0,0);
    series->append(1,8);
    series->append(2,4);
    series->append(7,2);*/

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->legend()->hide();
    //chart->createDefaultAxes();

    chart->addAxis(axisx,Qt::AlignBottom);
    series->attachAxis(axisx);

    chart->addAxis(axisy,Qt::AlignLeft);
    series->attachAxis(axisy);

    QChartView *chartview = new QChartView(chart);
    chartview->setParent(ui->horizontalFrame);
}

GraphView::~GraphView()
{
    delete ui;
}

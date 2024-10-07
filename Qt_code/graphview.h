#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <QDialog>
#include <QtCharts/QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtSql>
#include <QDateTime>
//#include <QAbstractAxis>

namespace Ui {
class GraphView;
}

class GraphView : public QDialog
{
    Q_OBJECT

public:
    explicit GraphView(QWidget *parent = nullptr);
    ~GraphView();

private:
    Ui::GraphView *ui;
    QSqlDatabase db;
};

#endif // GRAPHVIEW_H

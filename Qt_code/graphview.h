#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <QDialog>
#include <QtCharts/QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtSql>
#include <QDateTime>


namespace Ui {
class GraphView;
}

class GraphView : public QDialog
{
    Q_OBJECT

public:
    explicit GraphView(QWidget *parent = nullptr);
    ~GraphView();

protected:
   void keyPressEvent(QKeyEvent *event);


 private slots:
   void on_pushButton_clicked();

 private:
    Ui::GraphView *ui;
    QSqlDatabase db;
    QChart *chart;
};

#endif // GRAPHVIEW_H

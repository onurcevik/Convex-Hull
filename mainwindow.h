#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "QGraphicsLineItem"
#include <QPen>
#include <QBrush>
#include "mygraphicsview.h"
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QPen *pen;
    QBrush *brush;
    QVector<QPoint> pointsVector;
    QVector<QPoint> hull;
    QTimer *timer;

    QGraphicsLineItem *lineItem1,*lineItem2;

    int crossProduct(QPoint a, QPoint b, QPoint c);
    void drawCircle(QPoint point);
    QPoint leftMostPoint(QVector<QPoint> pointsVector);
signals:
    void updateLine(QPoint current,QPoint next, QPoint selected);
private slots:
    void addPoint(QPoint point);
    //void drawLine(QLine *line, QPoint start, QPoint finish);
    void drawLine(QPoint current,QPoint next, QPoint selected);
    void on_Start_clicked();
    void update();
};

#endif // MAINWINDOW_H

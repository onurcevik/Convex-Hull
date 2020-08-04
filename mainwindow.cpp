#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QGraphicsEllipseItem"
#include "QLine"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);

    ui->graphicsView->setScene(scene);
    //ui->graphicsView->scale(1, -1);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->show();
    ui->graphicsView->setFrameStyle(0);
    ui->graphicsView->setFixedSize(800,600);
    ui->graphicsView->setSceneRect(0,0,800,600);



    pen = new QPen();
    brush = new QBrush(Qt::red);
//    lineItem1=new QGraphicsLineItem();
//    lineItem2=new QGraphicsLineItem();
//    scene->addItem(lineItem1);
//    scene->addItem(lineItem2);

    timer = new QTimer(this);


    QObject::connect(ui->graphicsView, SIGNAL(mouseClicked(QPoint)),
                     this, SLOT(addPoint(QPoint)));
    QObject::connect(this, SIGNAL(updateLine(QPoint,QPoint,QPoint)),
                     this, SLOT(drawLine(QPoint,QPoint,QPoint)));
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(update()));
}

void MainWindow::drawCircle(QPoint point)
{
    //Add ellipse to the given QPoint
    pen->setColor(Qt::black);
    brush->setColor(Qt::black);
    QGraphicsEllipseItem *ellipseItem = scene->addEllipse(0,0,5,5,*pen,*brush);

    ellipseItem->setPos(point);

}

void MainWindow::drawLine(QPoint current,QPoint next, QPoint selected)
{
lineItem1=new QGraphicsLineItem(current.x(),current.y(),next.x(),next.y());
lineItem2=new QGraphicsLineItem(next.x(),next.y(),selected.x(),selected.y());
scene->addItem(lineItem1);
scene->addItem(lineItem2);



}

void MainWindow::addPoint(QPoint point)
{
    drawCircle(point);
    pointsVector.append(point);

}




MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::crossProduct(QPoint a, QPoint b)
{
    double value=a.x()*b.y()-a.y()*b.y();
    qDebug()<<"cp "<<value;
    if(value >0){
        return 1;
    }else if (value<0) {
       return -1;
    }else{
        return 0;
    }

}

int MainWindow::cp(QPoint a, QPoint b, QPoint c)
{

    int y1=a.y()-b.y();
    int y2= a.y()-c.y();
    int x1 = a.x() - b.x();
    int x2 = a.x() - c.x();
    int value= y2*x1 - y1*x2;
     qDebug()<<"cp "<<value;
     return value;

}

QPoint MainWindow::leftMostPoint(QVector<QPoint> pointsVector)
{
    QPoint leftmost=pointsVector.at(0);
    int i;
    for(i=0;i<pointsVector.size();i++){
        if(pointsVector.at(i).x()<=leftmost.x())
            leftmost=pointsVector.at(i);
    }
    return leftmost;
}

void MainWindow::on_Start_clicked()
{
    if(ui->comboBox->currentText()=="Jarvis March"){
        QPoint current = leftMostPoint(pointsVector);
        pen->setColor(Qt::red);
        brush->setColor(Qt::red);
        QGraphicsEllipseItem *ellipseItem = scene->addEllipse(current.x()-10,current.y()-10,20,20,*pen,*brush);

        QPoint next = pointsVector.at(1);
        int i;
        int cross;
        for(i=2;i<pointsVector.size();i++){
//            if(current==next)
//                continue;
            cross=cp(current,next,pointsVector.at(i));
            scene->removeItem(lineItem1);
            scene->removeItem(lineItem2);
            emit updateLine(current,next,pointsVector.at(i));
        }



    }

}

void MainWindow::update()
{
     qDebug() << "update() called";
}

#include "mygraphicsview.h"

MyGraphicsView::MyGraphicsView(QWidget *parent): QGraphicsView (parent){

}
void MyGraphicsView::mousePressEvent(QMouseEvent *ev)
{
    point = ev->pos();
    qDebug()<<point;
    QGraphicsView::mousePressEvent(ev);
    emit mouseClicked(point);
}

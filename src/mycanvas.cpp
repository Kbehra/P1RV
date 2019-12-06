/* Projet P1RV - sujet N°2 heightmaps - Kilian BEHRA & Alicia Maravat
 *
 *
 * mycanvas.cpp
 */

#include "mycanvas.h"

const int IdRole = Qt::UserRole;

MyCanvas::MyCanvas(QWidget *parent)
{
    QPicture picture;
    picture.load("/home/kiki/CLionProjects/P1RV/examples/Heightmap.jpeg");

    QImage myImage;
    QPainter painter;
    painter.begin(&myImage);
    painter.drawPicture(0,0, picture);
    painter.end();

    QPoint startPoint;


}

MyCanvas::MyCanvas()
{

}

void MyCanvas::paintEvent(QPaintEvent* e)
{
    //QPainter painter(this);
    //painter.drawLine(50,10,100,20);

}

//void MyCanvas::mousePressEvent(QGraphicsSceneEvent *e)
//{
//
//    startPoint = e ->scenePos().toPoint();
//    update();
//
//}

void MyCanvas::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    QPen pen;

    pen.setWidth(2);
    pen.setColor(QColor(Qt::darkGray));
    painter->setPen(pen);
    painter->drawRect(boundingRect().adjusted(5, 5, -5, -5));

    if(m_line.isNull()) return;
    pen.setWidth(10);
    pen.setColor(QColor(Qt::red));
    painter->setPen(pen);
    painter->drawLine(m_line);

}


QRectF MyCanvas::boundingRect() const{
    return QRectF(QPointF(0,0), QPointF(200, 200));
}

void MyCanvas::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    startPoint = event->scenePos().toPoint();
    qDebug() << "Pressed, start: " << startPoint;
    pressed = true;
    update();

    //QGraphicsItem::mousePressEvent(event);

}

void MyCanvas::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(pressed){
        QPoint endPoint = event->scenePos().toPoint();
        qDebug() << "Moving, start: " << startPoint << "  end: " << endPoint;
        m_line.setPoints(startPoint, endPoint);
        update();
    }
  //new QGraphicsItem::mousePressEvent(event);
}

void MyCanvas::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = false;
    QPoint endPoint = event->scenePos().toPoint();
    m_line.setPoints(startPoint, endPoint);
    qDebug() << "Release, start: " << startPoint << "  end: " << endPoint;
    update();
   // QGraphicsItem::mouseReleaseEvent(event);
}

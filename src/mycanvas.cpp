/* Projet P1RV - sujet N°2 heightmaps - Kilian BEHRA & Alicia Maravat
 *
 *
 * mycanvas.cpp
 */

#include "mycanvas.h"

const int IdRole = Qt::UserRole;

MyCanvas::MyCanvas(QWidget *parent)
{

}

MyCanvas::MyCanvas()
{

}

void MyCanvas::paintEvent(QPaintEvent* e)
{
    QPainter painter(this);
    painter.drawLine(50,10,100,20);

}

void MyCanvas::mousePressEvent(QMouseEvent *e)
{
    if (e->button()==Qt::LeftButton)
    {
        update();
    }
}

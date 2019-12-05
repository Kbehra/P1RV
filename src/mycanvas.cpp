/* Projet P1RV - sujet N°2 heightmaps - Kilian BEHRA & Alicia Maravat
 *
 *
 * mycanvas.cpp
 */

#include "mycanvas.h"

MyCanvas::MyCanvas(QWidget *parent)
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
/* Projet P1RV - sujet N°2 heightmaps - Kilian BEHRA & Alicia Maravat
 *
 *
 * mycanvas.cpp
 */

#include "mycanvas.h"

#include <iostream>
#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printdialog)
#include <QPrinter>
#include <QPrintDialog>
#endif
#endif

MyCanvas::MyCanvas(QWidget *parent, QString filename): QWidget(parent)
{
    setAttribute(Qt::WA_AcceptTouchEvents);
    setAttribute(Qt::WA_StaticContents);
    modified = false;

    myPenColors
            << QColor("green")
            << QColor("purple")
            << QColor("red")
            << QColor("blue")
            << QColor("yellow")

            << QColor("pink")
            << QColor("orange")
            << QColor("brown")
            << QColor("grey")
            << QColor("black");


}

bool MyCanvas::openImage(const QString &fileName)
{
    std::cout<<"image chargée"<<std::endl;
    std::cout<<fileName.toStdString()<<std::endl;
    QImage loadedImage;
    if (!loadedImage.load(fileName))
        return false;

    QSize newSize = loadedImage.size().expandedTo(parentWidget()->size());
    resizeImage(&loadedImage, newSize);
    image = loadedImage;
    modified = false;
    update();
    return true;
}

bool MyCanvas::saveImage(const QString &fileName, const char *fileFormat)
{
    QImage visibleImage = image;
    resizeImage(&visibleImage, size());

    if (visibleImage.save(fileName, fileFormat))
    {
        modified = false;
        return true;
    }
    else
    {
        return false;
    }
}
void MyCanvas::openImageGo()
{
    openImage(filename);
}

void MyCanvas::clearImage()
{
    image.fill(qRgb(255, 255, 255));
    modified = true;
    update();
}

void MyCanvas::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    const QRect rect = event->rect();
    painter.drawImage(rect.topLeft(), image, rect);
}

void MyCanvas::resizeEvent(QResizeEvent *event)
{
    if (width() > image.width() || height() > image.height())
    {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}

void MyCanvas::resizeImage(QImage *image, const QSize &newSize)
{
    if (image->size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}

void MyCanvas::print()
{

}

void MyCanvas::mousePressEvent(QMouseEvent *event)
{
    //std::cout<<"je suis la"<<std::endl;
    int X = event -> x ();
    int Y = event -> y ();
    if (event->button() == Qt::LeftButton)
    {
        QPainter painter(&image);
        painter.setPen(Qt::NoPen);
        painter.setBrush(myPenColors.at(2 % myPenColors.count()));
        painter.drawEllipse(QPointF(X, Y), 5, 5);
        painter.end();


    }
    update();
    // position globale du curseur



}

void MyCanvas::mouseReleaseEvent(QMouseEvent *event)
{

}

void MyCanvas::mouseMoveEvent(QMouseEvent *event)
{
    int X = event->pos().x();
    int Y = event->pos().y();
    QPainter painter(&image);
    painter.setPen(Qt::NoPen);
    painter.setBrush(myPenColors.at(2 % myPenColors.count()));
    painter.drawEllipse(QPointF(X, Y), 5, 5);
    painter.end();
    update();


    std::cout<<"moove"<<std::endl;

}

//bool MyCanvas::event(QEvent *event)
//{
//    //std::cout<<"je suis un evt"<<std::endl;
//    switch (event->type()) {
//        case QEvent::MouseButtonPress: {
//            //std::cout<<"je suis la"<<std::endl;
//
//        }
//            break;
//
//        case QEvent::MouseMove: {
//            //std::cout << "deplacement" << std::endl;
//        }
//            break;
//        case QEvent::TouchEnd:     {
//            QTouchEvent *touch = static_cast<QTouchEvent *>(event);
//            QList<QTouchEvent::TouchPoint> touchPoints = static_cast<QTouchEvent *>(event)->touchPoints();
//                    foreach (const QTouchEvent::TouchPoint &touchPoint, touchPoints) {
//                    switch (touchPoint.state()) {
//                        case Qt::TouchPointStationary:
//                        case Qt::TouchPointReleased:
//                            // don't do anything if this touch point hasn't moved or has been released
//                            continue;
//                        default:
//                        {
//                            QRectF rect = touchPoint.rect();
//                            if (rect.isEmpty()) {
//                                //qreal diameter = MaximumDiameter;
////                                if (touch->device()->capabilities() & QTouchDevice::Pressure)
////                                    diameter = MinimumDiameter + (MaximumDiameter - MinimumDiameter) * touchPoint.pressure();
//                                //rect.setSize(QSizeF(diameter, diameter));
//                            }
//
//                            QPainter painter(&image);
//                            painter.setPen(Qt::NoPen);
//                            painter.setBrush(myPenColors.at(touchPoint.id() % myPenColors.count()));
//                            painter.drawEllipse(rect);
//                            painter.end();
//
//                            modified = true;
//                            int rad = 2;
//                            update(rect.toRect().adjusted(-rad,-rad, +rad, +rad));
//                        }
//                            break;
//                    }
//                }
//            break;
//        }
//        default:
//            return QWidget::event(event);
//    }
//    return true;
//}

void MyCanvas::setFileName(QString filename)
{
    this->filename=filename;
    openImage(this->filename);
}
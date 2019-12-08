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
    my_pen = new QPen(QBrush(Qt::NoBrush),5.0,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
    my_pen->setBrush(Qt::red);
    chooseColor = new QColorDialog(this);

    connect(parent, SIGNAL(changeCapStyle(bool)), this, SLOT(changePenCap(bool)));
    connect(this, SIGNAL(setFullWindow(bool)), parent, SLOT(toggleFullWindow(bool)));
}

bool MyCanvas::openImage(const QString &fileName)
{
    std::cout<<"image chargée"<<std::endl;
    std::cout<<fileName.toStdString()<<std::endl;
    QImage loadedImage;
    if (!loadedImage.load(fileName))
        return false;
    QSize newSize = loadedImage.size();
    resizeImage(&loadedImage, newSize);
    int w = loadedImage.size().width();
    int h = loadedImage.size().height();

    if(parentWidget()->size().width()>w)
    {
        int ratio = parentWidget()->size().width()/w;
        image = loadedImage.scaled(loadedImage.size().width()*ratio,
                loadedImage.size().height()*ratio,Qt::KeepAspectRatio);
    }
    else
    {
        image = loadedImage;

    }

    //QSize newSize = loadedImage.size().expandedTo(parentWidget()->size());


    //image = loadedImage.scaled(loadedImage.size().width()*2,   loadedImage.size().height()*2,Qt::KeepAspectRatio);
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

    QImage newImage(newSize, QImage::Format_RGB32); //TODO : utiliser scaled de QImage?
    newImage.fill(qRgb(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}

void MyCanvas::print()
{

}

void MyCanvas::changeBrushColor()
{
    chooseColor->open();
}
void MyCanvas::changePenWidth(double width)
{
    my_pen->setWidth(float (width));
}
void MyCanvas::changePenCap(bool cap_style)
{
    if(cap_style){
        my_pen->setCapStyle(Qt::RoundCap);
    } else {
        my_pen->setCapStyle(Qt::SquareCap);
    }
}

void MyCanvas::keyPressEvent(QKeyEvent *keyEvent) {
    switch (keyEvent->key()) {
        case Qt::Key_Escape:
            //TODO trouver autre chose que Close qui ferme le contexte OpenGL mais pas la fenetre
            close();
            break;
        case Qt::Key_F1: {
            emit setFullWindow(false);
            update();
        }
            break;
    }
}

void MyCanvas::mousePressEvent(QMouseEvent *event)
{
    // position globale du curseur
    int X = event -> x ();
    int Y = event -> y ();
    if (event->button() == Qt::LeftButton)
    {
        QPainter painter(&image);
        my_pen->setColor(chooseColor->selectedColor());
        painter.setPen(*my_pen);
        //painter.drawEllipse(QPointF(X, Y), 10, 10);
        painter.drawPoint(QPointF(X, Y));
        painter.end();
    }
    update();
}

void MyCanvas::mouseReleaseEvent(QMouseEvent *event)
{
    update();
}

void MyCanvas::mouseMoveEvent(QMouseEvent *event)
{
        int X = event->pos().x();
        int Y = event->pos().y();
        QPainter painter(&image);
        my_pen->setColor(chooseColor->selectedColor());
        painter.setPen(*my_pen);
        //painter.drawEllipse(QPointF(X, Y), 10, 10);
        painter.drawPoint(QPointF(X, Y));
        painter.end();
        update();
}

void MyCanvas::setFileName(QString filename)
{
    this->filename=filename;
    openImage(this->filename);
}

int MyCanvas::maybeSave()
{
    QMessageBox closeornot;
    closeornot.setText("Do you want to save your canvas ?");
    closeornot.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    closeornot.setDefaultButton(QMessageBox::Save);
    return closeornot.exec();
}

void MyCanvas::closeEvent(QCloseEvent *event)
{
    switch (maybeSave())
    {
        case QMessageBox::Save:
            // Save was clicked
            //saveImage(&image,);
            event->accept();
            break;
        case QMessageBox::Discard:
            // Don't Save was clicked
            event->accept();
            break;
        case QMessageBox::Cancel:
            // Cancel was clicked
            event->ignore();
            break;
        default:
            // should never be reached
            break;
    }
}
QImage MyCanvas::getImage() {
    return image;
}
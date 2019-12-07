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

    connect(this, SIGNAL(setFullWindow(bool)), parent, SLOT(toggleFullWindow(bool)));
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
    /*if (event->size().width()> image.width() || event->size().height()> image.height())
    {
        int newWidth = qMax(event->size().width() + 128, image.width());
        int newHeight = qMax(event->size().height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }*/
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
        painter.setPen(Qt::NoPen);
        painter.setBrush(myPenColors.at(2 % myPenColors.count()));
        painter.drawEllipse(QPointF(X, Y), 5, 5);
        painter.end();
    }
    update();
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
            //saveImage();
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
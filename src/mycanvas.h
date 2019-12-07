/* Projet P1RV - sujet N°2 heightmaps - Kilian BEHRA & Alicia Maravat
 *
 *
 * mycanvas.h
 */


#ifndef P1RV_MYCANVAS_H
#define P1RV_MYCANVAS_H

#include "interface.h"
#include "loadjpeg.h"
#include "createmap.h"
#include "material.h"

#include <GL/glu.h>
#include <QApplication>
#include <QWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QSlider>
#include <QComboBox>
#include <QLCDNumber>
#include <QGraphicsSceneEvent>
#include <QTimer>
#include <QResizeEvent>
#include <QColor>
#include <QImage>
#include <QPoint>

class MyCanvas : public QWidget
{
Q_OBJECT

public:
    MyCanvas(QWidget *parent = 0, QString filename="");
    bool openImage(const QString &fileName);
    bool saveImage(const QString &fileName, const char *fileFormat);
    bool isModified() const { return modified; }
    void setFileName(QString filename);
    void mousePressEvent (QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent (QMouseEvent *event);
    virtual void keyPressEvent( QKeyEvent *keyEvent ) override;

public
    slots:
    void openImageGo();
    void clearImage();
    void print();
    virtual void closeEvent(QCloseEvent *);

    signals:
    void setFullWindow(bool);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    //bool event(QEvent *event) override;

private:
    void resizeImage(QImage *image, const QSize &newSize);
    bool modified;
    QList<QColor> myPenColors;
    QImage image;
    QString filename;
    int maybeSave();
};

#endif //P1RV_MYCANVAS_H

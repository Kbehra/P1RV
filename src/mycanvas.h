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




class MyCanvas : public QWidget {
    Q_OBJECT
protected:
    void mousePressEvent(QMouseEvent* e);

public:
    explicit MyCanvas(QWidget *parent = 0);
    MyCanvas();

public slots :
    void paintEvent(QPaintEvent* e);

private slots:

private:



};


#endif //P1RV_MYCANVAS_H

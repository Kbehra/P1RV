/* Projet P1RV - sujet N°2 heightmaps - Kilian BEHRA & Alicia Maravat
 *
 *
 * mywindow.h
 */
#ifndef P1RV_MYWINDOW_H
#define P1RV_MYWINDOW_H

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

class MyWindow : public Interface {
    Q_OBJECT
public:
    explicit MyWindow(QWidget *parent = 0);

    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    virtual void keyPressEvent( QKeyEvent *keyEvent );

private:
    ImageJPEG monimage;
    CreateMap my_map;

    int choice_mat;
    bool shade_model;
    bool projection;
    float pas;

    //Tailles
    int window_width;
    int window_high;

    //Ortho
    float left;
    float right;
    float top;
    float bottom;

    //Perspective
    float focale;
    float near;
    float far;

public slots :
    void openFile();
    void openTex();
    void saveFile();
    void chooseParam();

};


#endif //P1RV_MYWINDOW_H

//
// Created by alicia on 04/12/2019.
//

#ifndef P1RV_MYWINDOW_H
#define P1RV_MYWINDOW_H

#include "interface.h"
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

private:

public slots :
    void openFile();
    void openTex();
    void saveFile();
    void chooseParam();

};


#endif //P1RV_MYWINDOW_H

//
// Created by alicia on 04/12/2019.
//

#ifndef P1RV_INTERFACE_H
#define P1RV_INTERFACE_H

#include <Qt>
#include <QtOpenGL/QtOpenGL>
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QFileDialog>
#include <QtOpenGL/QGLWidget>
#include <QtOpenGL/QGL>

class QWidget;

class Interface : public QGLWidget {
    Q_OBJECT
public:
    explicit Interface(int framesPerSecond = 0, QWidget *parent = 0, char *name = 0);

    virtual void initializeGL() = 0;
    virtual void resizeGL(int width, int height) = 0;
    virtual void paintGL() = 0; //afficher la scène OpenGL
    void toggleFullWindow();
    virtual void keyPressEvent( QKeyEvent *keyEvent );

public slots:
    virtual void timeOutSlot();

private:
    QTimer *t_Timer;
    bool b_Fullscreen;
    bool shade_model;

};

#endif //P1RV_INTERFACE_H

//
// Created by alicia on 04/12/2019.
//

#ifndef P1RV_INTERFACE_H
#define P1RV_INTERFACE_H

#include <QtOpenGL/QtOpenGL>
#include <QtOpenGL/QGLWidget>

class Interface {
    Q_OBJECT
public:
    //explicit myGLWidget(int framesPerSecond = 0, QWidget *parent = 0, char *name = 0);
    //virtual void initializeGL() = 0;
    //virtual void resizeGL(int width, int height) = 0;
    //virtual void paintGL() = 0;
    //virtual void keyPressEvent( QKeyEvent *keyEvent );

public slots:
    //virtual void timeOutSlot();

private:
    QTimer *t_Timer;

};

#endif //P1RV_INTERFACE_H

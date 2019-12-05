/* Projet P1RV - sujet N°2 heightmaps - Kilian BEHRA & Alicia Maravat
 *
 *
 * interface.cpp
 */
#include <iostream>
#include "interface.h"

Interface::Interface(int framesPerSecond, QWidget *parent, char *name) : QGLWidget(parent)
{

    setWindowTitle(QString::fromUtf8(name)); //permet de définir le nom de la fenêtre :param name
    b_Fullscreen = false ;
    if(framesPerSecond == 0)
    {
        t_Timer = NULL;
    }
    else
    {   //Controle du temps entre deux images rendus par OpenGL
        int seconde = 100000; // 1 seconde = 1000 ms
        int timerInterval = seconde / framesPerSecond;
        t_Timer = new QTimer(this);
        connect(t_Timer, SIGNAL(timeout()), this, SLOT(timeOutSlot()));
        t_Timer->start( timerInterval );
    }
}

void Interface::toggleFullWindow()
{
    if(b_Fullscreen)
    {
        showNormal();
        b_Fullscreen = false;
    }
    else
    {
        showFullScreen();
        b_Fullscreen = true;
    }
}

/* Evenement clavier*/
void Interface::keyPressEvent(QKeyEvent *keyEvent)
{
    switch(keyEvent->key())
    {
        case Qt::Key_Escape:
            close();
            break;
        case Qt::Key_F1:
            toggleFullWindow();
            break;
    }
}

//SLOT
void Interface::timeOutSlot()
{
    updateGL();
}